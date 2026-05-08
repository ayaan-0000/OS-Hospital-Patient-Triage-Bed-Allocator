#!/bin/bash
echo "========================="
echo "Hospital System Starting"
echo "========================="
mkfifo /tmp/discharge_fifo
gcc -Wall -pthread admissions.c -o admissions
gcc -Wall -pthread patient_simulator.c -o patient_simulator
./admissions