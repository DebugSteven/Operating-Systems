// lab2functions.cpp
// implementation of algorithms beyond sorting

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "queue.h"
#include "task.h"
#include "lab2functions.h"

int read_file(std::ifstream& inFile, queue& ready_queue)
{
    if(!inFile.good())
    {
        std::cerr << "File not found\n";
        exit(EXIT_FAILURE);
    }
    
    Task temp;
    while(inFile >> temp.pid)
    {
        inFile >> temp.arrival_time;
        inFile >> temp.CPU_burst;
        temp.CPU_remaining = temp.CPU_burst;
        temp.finish = 0;
        temp.waiting = 0;
        temp.turnaround = 0;
        temp.response = 0;
        temp.context = 0;
        ready_queue.push(temp);
    }
    
    return EXIT_SUCCESS;
}

void calculation(Task info[], int algorithm, int quantumsize, int length)
{
       sort_pid(info, length);
    
        if(algorithm == 0)
        {
            std::cout << std::setfill('*') << std::setw(125) << " " <<  std::endl;
            std::cout << std::setfill('*') << std::setw(60) << " Scheduling algorithm : FCFS " << std::setfill('*') << std::setw(65) << " " << std::endl;
            std::cout << std::setfill('*') << std::setw(125) << " " << std::endl;
        }
    
        else if(algorithm == 1)
        {
            std::cout << std::setfill('*') << std::setw(125) << " " <<  std::endl;
            std::cout << std::setfill('*') << std::setw(60) << " Scheduling algorithm : SRTF " << std::setfill('*') << std::setw(65) << " " << std::endl;
            std::cout << std::setfill('*') << std::setw(125) << " " << std::endl;
        }
    
        else
        {
            std::cout << std::setfill('*') << std::setw(125) << " " <<  std::endl;
            std::cout << std::setfill('*') << std::setw(60) << " Scheduling algorithm : Round Robin " << std::setfill('*') << std::setw(65) << " " << std::endl;
            std::cout << std::setfill('*') << std::setw(40) << " ( No. of Task = " << length << " Quantum = " << quantumsize << " ) " << std::setfill('*') << std::setw(65) << " " << std::endl;
            std::cout << std::setfill('*') << std::setw(125) << " " << std::endl;
            
        }
    
    std::cout << "pid\t arrival\t CPUburst\t finish\t\t waiting\t turnaround\t response\t Context\t" << std::endl;
    for(int i = 0; i < length; i++)
    {
        std::cout << std::fixed << std::setprecision(1) << info[i].pid << "\t " << info[i].arrival_time << "\t\t " << info[i].CPU_burst << "\t\t " << info[i].finish << "\t\t " << info[i].waiting << "\t\t " << info[i].turnaround << "\t\t " << info[i].response << "\t\t " << info[i].context << std::endl;
    }
    
    float avg_CPUburst = 0, avg_wait = 0, avg_turnaround = 0, avg_response = 0;
    int num_of_context = 0;
    for(int j = 0; j < length; j++)
    {
        avg_CPUburst += info[j].CPU_burst;
        avg_wait += info[j].waiting;
        avg_turnaround += info[j].turnaround;
        avg_response += info[j].response;
        num_of_context += info[j].context;
    }
    std::cout << "Average CPU burst time = " << std::fixed << std::setprecision(3) << avg_CPUburst/length << " ms, Average waiting time = " <<avg_wait/length << " ms" << std::endl;
    std::cout << "Average turn around time = " << std::fixed << std::setprecision(3) << avg_turnaround/length << " ms, Average response time = " << avg_response/length << " ms" << std::endl;
    std::cout << "Total No. of Context Switching Performed = " << num_of_context << std::endl;
}

void FCFS(Task info[], int length, queue ready_queue)
{
    ready_queue.arrival_sort();
    
    float total_time = 0;
    Task temp;
    
    for(int i = 0; i < length; i++)
    {
        temp = ready_queue.front();
        ready_queue.pop();
        total_time += temp.CPU_burst;
        temp.finish = total_time;
        temp.waiting = temp.finish - temp.arrival_time - temp.CPU_burst;
        temp.turnaround = temp.waiting + temp.CPU_burst;
        temp.response = temp.waiting;
        info[i] = temp;
    }
}

void SRTF(Task info[], queue ready_queue)
{

    ready_queue.arrival_sort();
    
    float total_time = 0;
    int i = 0;
    bool context_switch = false;    //if the first task isn't the shortest task at time 0 there is no context switch
    Task temp,check;
    
    temp = ready_queue.front();
    ready_queue.pop();
    
    check = check_lowest(temp, total_time, ready_queue, context_switch);    //find the shortest task

    if(check.pid != temp.pid)
	{
		ready_queue.push(temp);
	}
	
    temp = check;
    int length = ready_queue.size();
    int start_pid = temp.pid;
    while(!ready_queue.empty() || temp.CPU_remaining != 0)
    {
        context_switch = true;  //context switch is true while a task still has CPU time left
        
        if(temp.response == 0 && temp.pid != start_pid)
            temp.response = total_time - temp.arrival_time;
        
        total_time += 0.5;
        temp.CPU_remaining += -0.5;
        
        //check to see if this is the right process to be running based on time and CPU burst
        if(!ready_queue.empty())
            check = check_lowest(temp, total_time, ready_queue, context_switch);
        
        if(check.pid != temp.pid && !ready_queue.empty())
        {
            ready_queue.push(temp);
        }
        
        if(!ready_queue.empty())
        {
            temp = check;
        }
        
        if(temp.CPU_remaining == 0)
        {
            context_switch = false;
            temp.finish = total_time;
            temp.waiting = temp.finish - temp.arrival_time - temp.CPU_burst;
            temp.turnaround = temp.finish - temp.arrival_time;
            info[i] = temp;
            i++;
            
            if(!ready_queue.empty())
            {
                temp = ready_queue.front();
                ready_queue.pop();
                
                check = check_lowest(temp, total_time, ready_queue, context_switch);
                if(temp.pid != check.pid)
                    ready_queue.push(temp);
                
                temp = check;
            }
        }
    }
}

Task check_lowest(Task& current, float& total_time, queue& ready_queue, bool context_switch)
{
    Task check, new_process;
    new_process = current;
    bool not_found = true;
    
    int length = ready_queue.size();
    for(int i = 0; i < length; i++)
    {
        check = ready_queue.front();
        ready_queue.pop();
        if(check.CPU_remaining != 0)
            ready_queue.push(check);
    }
    
    length = ready_queue.size();
    for(int j = 0; j < length; j++)
    {
        check = ready_queue.front();
        ready_queue.pop();
        
        if(check.arrival_time <= total_time)
        {
            if(check.CPU_remaining < new_process.CPU_remaining)
            {
                new_process = check;
                not_found = false;
            }
            
            else
            {
                ready_queue.push(check);
            }
        }
        
        else
        {
            ready_queue.push(check);
        }
    }
    
    if(not_found)
    {
        return current;
    }
    
    else if(context_switch)
    {
        total_time += 0.5;
        current.context++;
        return new_process;
    }
    
    else
    {
        return new_process;
    }
}

void RR(int quantumsize, Task info[], int length, queue ready_queue)
{
    ready_queue.arrival_sort();
    
    float total_time = 0;
    int i = 0;
    Task temp;
    
    while(!ready_queue.empty())
    {
        temp = ready_queue.front();
        ready_queue.pop();
    
        if(temp.context == 0)
        {
            temp.response = total_time - temp.arrival_time;
        }
    
        if(temp.CPU_remaining > quantumsize)
        {
            temp.CPU_remaining = temp.CPU_remaining - quantumsize;
            total_time += quantumsize + 0.5;
            temp.context++;
            ready_queue.push(temp);
        }
    
        else
        {
            total_time += temp.CPU_remaining;
            temp.finish = total_time;
            temp.waiting = temp.finish - temp.arrival_time - temp.CPU_burst;
            temp.turnaround = temp.finish - temp.arrival_time;
            info[i] = temp;
            i++;
        }
    }
}

void sort_pid(Task info[], int length)
{
    Task temp;
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < (length-1); j++)
        {
            if(info[j+1].pid < info[j].pid)
            {
                temp = info[j];
                info[j] = info[j+1];
                info[j+1] = temp;
            }
        }
    }
}

bool operator==(const Task &lhs, const Task &rhs)
{
    bool equal = true;
    
    if(lhs.pid != rhs.pid)
        equal = false;
    else if(lhs.arrival_time != rhs.arrival_time)
        equal = false;
    else if(lhs.CPU_burst != rhs.CPU_burst)
        equal = false;
    else if(lhs.CPU_remaining != rhs.CPU_remaining)
        equal = false;
    else if(lhs.finish != rhs.finish)
        equal = false;
    else if(lhs.waiting != rhs.waiting)
        equal = false;
    else if(lhs.turnaround != rhs.turnaround)
        equal = false;
    else if(lhs.response != rhs.response)
        equal = false;
    else if(lhs.context != rhs.context)
        equal = false;
    
    return equal;
}



