#!/bin/bash
for i in {1..20}
do
    s=$(( (RANDOM % 10) + 1 ))
    ./triage.sh p$i 20 $s
    sleep 1
done