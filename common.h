/*
 * ============================================================
 * Project : Hospital Patient Triage & Bed Allocator
 * File : common.h
 * Group : Group 6
 * Members : Muhammad Mahad Anwer 24F-3010 , Ayaan Amir 24F-0767
 * Date : 2026-05-08
 * ============================================================
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <semaphore.h>

#define MAX_PAT 100
#define MAX_BEDS 20
#define SHM_KEY 0xBEDF00D
#define FIFO_FILE "/tmp/discharge_fifo"


typedef struct
{
    int patient_id;
    char name[50];
    int age;
    int severity;
    int priority;
    int care_units;
    time_t arrival_time;

}PatientRecord;


typedef struct
{
    int partition_id;
    int start_unit;
    int size;
    int is_free;
    int patient_id;
    char bed_type[20];

}BedPartition;

#endif