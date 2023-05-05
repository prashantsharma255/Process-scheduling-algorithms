# Process Scheduling Algorithms 

I have implemented 6 process scheduling algorithms. 

- First Come First Served (FCFS) [Non-Preemptive]
- Shortest Job First (SJF) [Non-Preemptive]
- Shortest Remaining Time (SRT) [Preemptive]
- Round Robin (RR) [Preemptive]
- Highest Priority First (HPF) [Preemptive]
- Highest Priority First (HPF) [Non-Preemptive]

We run each algorithm for 100 quanta (time slices), labelled 0 to 99. While running, we generate a set of simulated processes. For each simulated process, we randomly generate:
• An arrival time: a float value from 0 through 99 (measured in quanta).
• An expected total run time: a float value from 0.1 through 10 quanta.
• A priority: integer 1, 2, 3, or 4 (1 is highest)

Tip: For debugging, you may want to use the same (pseudo) random numbers each
time. For this to happen, you should set the seed of the random number generator to a
value, such as 0. 

- We assume only one process queue. 
- We sort the simulated processes so that they enter the queue in arrival time order. Our process scheduler can do process switching only at the start of each time quantum. For this project, we only consider CPU time for each process (no I/O wait times).
- For RR, we use a time slice of 1 quantum.
- For HPF, we use 4 priority queues. Do separate runs for non-preemptive scheduling and for preemptive scheduling (considering them as two different algorithms). 
- For preemptive scheduling, use RR with a time slice of 1 quantum for each priority queue.
- For non-preemptive scheduling, use FCFS.

Each simulation run will last until the completion of the last process, even if it goes beyond 100 quanta. No process will get the CPU for the first time after time quantum 99.
- We run each algorithm 5 times to get averages for time parameters.
- Before each run, we clear the process queue and create a new set of simulated processes.
