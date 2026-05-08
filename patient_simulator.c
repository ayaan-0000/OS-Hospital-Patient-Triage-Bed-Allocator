/*
 * ============================================================
 * Project : Hospital Patient Triage & Bed Allocator
 * File : patient_simulator.c
 * ============================================================
 */

#include "common.h"
int main(int argc , char *argv[])
{
    int pid;
    int pri;
    int bed;
    pid = atoi(argv[1]);
    pri = atoi(argv[2]);
    bed = atoi(argv[3]);
    printf("Patient %d arrived\n" , pid);
    printf("Patient %d treatment started at bed %d\n" , pid , bed);
    srand(time(NULL) + pid);
    int t;

    if(pri <= 2)
    {
        t = rand()%11 + 5;
    }
    else if(pri == 3)
    {
        t = rand()%8 + 3;
    }
    else
    {
        t = rand()%7 + 2;
    }

    sleep(t);
    printf("Patient %d discharged\n" , pid);
    int fd;
    fd = open(FIFO_FILE , O_WRONLY);
    write(fd , &pid , sizeof(int));
    close(fd);
    return 0;
}