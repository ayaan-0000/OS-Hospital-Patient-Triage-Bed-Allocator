#!/bin/bash
echo "Stopping Hospital"
pkill admissions
ipcrm -M 0xBEDF00D
rm -f /tmp/discharge_fifo
echo "All cleaned"