all:
	gcc -Wall admissions.c -o admissions -pthread
	gcc -Wall patient_simulator.c -o patient_simulator -pthread
	gcc -Wall schedule.c -o schedule
	gcc -Wall memory_manager.c -o memory_manager

run:
	bash start_hospital.sh

test:
	bash stress_test.sh

memory-best:
	./memory_manager --strategy best

memory-first:
	./memory_manager --strategy first

memory-worst:
	./memory_manager --strategy worst

clean:
	rm -f admissions
	rm -f patient_simulator
	rm -f schedule
	rm -f memory_manager
	rm -f schedule_log.txt
	rm -f /tmp/discharge_fifo
dos2unix *.sh mkfile
chmod +x *.sh