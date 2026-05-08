/*
 * Project : Hospital Patient Triage & Bed Allocator
 * File : memory_manager.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20
int ward[SIZE];

typedef struct {
    int start;
    int size;

}FreeBlock;
FreeBlock free_list[20];
int free_count = 0;


void makeW()
{
    int i;
    for (i = 0; i < SIZE; i++)
 {
        ward[i] = 0;
    }
}


void showW()
{
     int i;
    printf("Ward:");
    for (i = 0; i < SIZE; i++)
  {
        printf("%d ", ward[i]);
        }
 printf("Ward");
}


void upfreelist()
{
  int i = 0;
    free_count = 0;
    while (i < SIZE)
    {
        if (ward[i] == 0)
     {
            int s = i;
            int c = 0;
            while (i < SIZE && ward[i] == 0)
        {
                c++;
                i++;
     }
               free_list[free_count].start = s;
         free_list[free_count].size = c;
            free_count++;
  }
        else
 {
            i++;
    }
 }
}


void sfreelist()
{
    int i;
    printf("Free List:");
    for (i = 0; i < free_count; i++)
    {
        printf("Block %d = Start : %d  Size : %d", i, free_list[i].start, free_list[i].size);
    }
}


int firstfit(int need)
{
    int i;
    for (i = 0; i < free_count; i++){
        if (free_list[i].size >= need)
        {
            return free_list[i].start;
        }
    }
    return -1;
}


int bestfit(int need)
{
    int i;
    int best = 999;
    int pos = -1;

    for (i = 0; i < free_count; i++)
      {
        if (free_list[i].size >= need)
  {
            if (free_list[i].size < best)
           {
                best = free_list[i].size;
                pos = free_list[i].start;
        }
      }
      }
    return pos;
}

int worstfit(int need)
{
   int i;
      int big = -1;
   int pos = -1;
    for (i = 0; i < free_count; i++)
     {
        if (free_list[i].size >= need)
         {
            if (free_list[i].size > big)
            {
      big = free_list[i].size;
            pos = free_list[i].start;
      }
           }
  }
    return pos;
}


void allomem(int start, int need, int pid)
     {
    int i;
    for (i = start; i < start + need; i++)
 {
      ward[i] = pid;
      }
    upfreelist();
}

void freemem(int pid){
 int i;
    for (i = 0; i < SIZE; i++)
    {
        if (ward[i] == pid)
     {
            ward[i] = 0;       }
 }
    upfreelist();
}


int main(int argc, char* argv[])
{
 char mode[20] = "best";
    if (argc == 3)
    {
        if (strcmp(argv[1], "--strategy") == 0){
            strcpy(mode, argv[2]);
        }
    }
    makeW();
    upfreelist();
    printf("Initial State");
    showW();
    sfreelist();
    int need = 5;
    int pos = -1;
    if (strcmp(mode, "best") == 0)
    {
        pos = bestfit(need);
       }
    else if (strcmp(mode, "first") == 0)
  {
         pos = firstfit(need);
    }
    else if (strcmp(mode, "worst") == 0) {
        pos = worstfit(need);
    }

    if (pos == -1)
    {
        printf("No Space Available");
    }
    else
    {
     allomem(pos, need, 1);
           printf("Memory Allocated Using %s Fit", mode);
        printf("Start Position : %d", pos);
    }
    showW();
      sfreelist();
      printf("Free Memory");
    freemem(1);
    showW();
       sfreelist();
    return 0;
}