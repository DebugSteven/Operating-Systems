#ifndef TASK_H_HAIGH
#define TASK_H_HAIGH

struct Task
{
	int pid;
	int arrival_time;
	int CPU_burst;
    float CPU_remaining;
    float finish;
    float waiting;
    float turnaround;
    float response;
    int context;
};

#endif