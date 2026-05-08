/*
 * Project : Hospital Patient Triage & Bed Allocator
 * File : admissions.c
 */
#include "common.h"
    PatientRecord line[100];
  int front = 0;
     int rear = 0;
   BedPartition* beds;
int shm_id;
pthread_mutex_t q_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t q_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t bed_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t bed_cond = PTHREAD_COND_INITIALIZER;
sem_t* icu_sem;
sem_t* iso_sem;


void addpatient(PatientRecord p)
{
    pthread_mutex_lock(&q_lock);
    line[rear] = p;
    rear++;
    pthread_cond_signal(&q_cond);
    pthread_mutex_unlock(&q_lock);
}

PatientRecord gettingpatient()
{
      PatientRecord p;
   pthread_mutex_lock(&q_lock);
 while (front == rear)
    {
        pthread_cond_wait(&q_cond, &q_lock);
    }

    p = line[front];
    front++;
    pthread_mutex_unlock(&q_lock);
    return p;
}


void makingbed()
{
int i;
    for (i = 0; i < 4; i++)
{
        beds[i].partition_id = i;
        beds[i].size = 3;
        beds[i].is_free = 1;
        strcpy(beds[i].bed_type, "ICU");
    }

    for (i = 4; i < 8; i++){
        beds[i].partition_id = i;
        beds[i].size = 2;
        beds[i].is_free = 1;
        strcpy(beds[i].bed_type, "ISOLATION");
    }

    for (i = 8; i < 20; i++){
        beds[i].partition_id = i;
        beds[i].size = 1;
        beds[i].is_free = 1;
        strcpy(beds[i].bed_type, "GENERAL");
    }
}


int bestfiting(PatientRecord p)
{
    int i;
    int pos = -1;
    int best = 999;
    for (i = 0; i < 20; i++){
        if (beds[i].is_free == 1)
     {
            if (beds[i].size >= p.care_units)
    {
                if (beds[i].size < best)
       {
                    best = beds[i].size;
                    pos = 
                   }
       }
    }
                }
    return pos;
}


void bedfree(int pid)
{
    int i;
    pthread_mutex_lock(&bed_lock);
    for (i = 0; i < 20; i++)
    {
        if (beds[i].patient_id == pid)
        {
            beds[i].is_free = 1;
            beds[i].patient_id = -1;

            printf("Bed %d is free now\n", i);
            pthread_cond_broadcast(&bed_cond);
        }
    }
    pthread_mutex_unlock(&bed_lock);
}


void child(int x)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
    {
    }
}


void* receptionist(void* arg)
{
    char data[200];
    while (1){
        if (fgets(data, sizeof(data), stdin) == NULL)
        {
            printf("Receptionist: No more patients arriving\n Desk closing\n");
            break;
        }

        if (strlen(data) <= 1){
            continue;
        }
        PatientRecord p;
        sscanf(data, "%d %s %d %d %d",&p.patient_id,
     p.name,&p.age,&p.severity,&p.priority);
        p.arrival_time = time(NULL);

        if (p.priority <= 2){
            p.care_units = 3;
        }
        else if (p.priority == 3){
            p.care_units = 2;
        }
        else{
            p.care_units = 1;
        }

        addpatient(p);
        printf("Receptionist got patient %s\n", p.name);
    }
    return NULL;
}


void* scheduler(void* arg)
{
    while (1)
    {
 PatientRecord p = gettingpatient();
 pthread_mutex_lock(&bed_lock);
        int bed = bestfiting(p);
        while (bed == -1)
        {
            printf("No bed free for %s waiting\n", p.name);
            pthread_cond_wait(&bed_cond, &bed_lock);
            bed = bestfiting(p);
        }
        beds[bed].is_free = 0;
        beds[bed].patient_id = p.patient_id;
        pthread_mutex_unlock(&bed_lock);
        pid_t id = fork();

        if (id == 0)
        {
    char pid_s[20];
          char pri_s[20];
        char bed_s[20];
sprintf(pid_s, "%d", p.patient_id);
       sprintf(pri_s, "%d", p.priority);
    sprintf(bed_s, "%d", bed);

            char* arr[] = {"./patient_simulator",
               pid_s,pri_s,bed_s,NULL};
 execv("./patient_simulator", arr);
   }
   printf("Patient %s got bed %d\n", p.name, bed);
  }
 return NULL;
}

void* nurse(void* arg){
  int fd;   
 int pid;
  mkfifo(FIFO_FILE, 0666);
  while (1)
    {
 fd = open(FIFO_FILE, O_RDONLY);
   while (read(fd, &pid, sizeof(int)) > 0){
        bedfree(pid);
  printf("Nurse cleaned patient %d\n", pid);
        }
     close(fd);
}
    return NULL;
}


int main()
{
   signal(SIGCHLD, child);
   shm_id = shmget(SHM_KEY, sizeof(BedPartition) * 20, 0666 | IPC_CREAT);
   beds = (BedPartition*)shmat(shm_id, NULL, 0);
   makingbed();
  icu_sem = sem_open("/sem_icu", O_CREAT, 0666, 4);
   iso_sem = sem_open("/sem_iso", O_CREAT, 0666, 4);
    pthread_t t1;
  pthread_t t2;
    pthread_t t3;
  pthread_create(&t1, NULL, receptionist, NULL);
    pthread_create(&t2, NULL, scheduler, NULL);
  pthread_create(&t3, NULL, nurse, NULL);
  printf("Hospital Started\n");
    pthread_join(t1, NULL);
  pthread_join(t2, NULL);
    pthread_join(t3, NULL);
  shmdt(beds);
    return 0;
}