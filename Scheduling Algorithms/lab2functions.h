// lab2functions.h

#ifndef LAB2FUNCTIONS_HAIGH_H
#define LAB2FUNCTIONS_HAIGH_H

#include <fstream>

int read_file(std::ifstream& inFile, queue& ready_queue);
void calculation(Task info[], int algorithm, int quantumsize, int length);
void FCFS(Task info[], int length, queue ready_queue);
void SRTF(Task info[], queue ready_queue);
void RR(int quantumsize, Task info[], int length, queue ready_queue);
void sort_pid(Task info[], int length);
Task check_lowest(Task& current, float& total_time, queue& ready_queue, bool context_switch);
bool operator==(const Task &lhs, const Task &rhs);

#endif
