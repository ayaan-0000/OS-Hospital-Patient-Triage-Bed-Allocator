#!/bin/bash
# ============================================================
# Project : Hospital Patient Triage & Bed Allocator
# Script : triage.sh
# ============================================================

if [ $# -ne 3 ]
then
    echo "Usage: ./triage.sh name age severity"
    exit
fi

name=$1
age=$2
sev=$3

if ! [[ $age =~ ^[0-9]+$ ]]
then
    echo "Wrong age"
    exit
fi

if ! [[ $sev =~ ^[0-9]+$ ]]
then
    echo "Wrong severity"
    exit
fi

if [ $sev -ge 9 ]
then
    pri=1
elif [ $sev -ge 7 ]
then
    pri=2
elif [ $sev -ge 5 ]
then
    pri=3
elif [ $sev -ge 3 ]
then
    pri=4
else
    pri=5
fi

id=$RANDOM
msg="$id $name $age $sev $pri"
echo $msg