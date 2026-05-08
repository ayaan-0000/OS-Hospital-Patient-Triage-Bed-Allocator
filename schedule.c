#include <stdio.h>
int main()
{
 int bt[5] = { 6,2,9,1,3 };
  int wt[5];
      int tat[5];
     int i;
    wt[0] = 0;

    for (i = 1; i < 5; i++){
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (i = 0; i < 5; i++){
        tat[i] = wt[i] + bt[i];
    }
    FILE* fp;
    fp = fopen("schedule_log.txt", "w");
    fprintf(fp, "FCFS Scheduling\n\n");
    for (i = 0; i < 5; i++)
    {
        fprintf(fp, "P%d WT=%d TAT=%d\n", i + 1, wt[i], tat[i]);
    }
    fclose(fp);
    printf("Schedule saved\n");
    return 0;
}