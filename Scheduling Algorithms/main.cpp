// main.cpp

#include "queue.h"
#include "task.h"
#include "lab2functions.h"
#include <fstream>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    queue ready_queue;
    Task info[100];
    int length;
    
    std::ifstream inFile(argv[1]);
    int algorithm = atoi(argv[2]);
    int quantumsize;    // if the 3rd argument for RR is forgotten it will be set to 4ms
    
    if(algorithm == 2)
    {
        if(argc < 4)
            quantumsize = 4;
        
        else
            quantumsize = atoi(argv[3]);
    }
    
    read_file(inFile, ready_queue);
    length = ready_queue.size();
    
    //pick algorithm based on argument 2
    if(algorithm == 0)
        FCFS(info, length, ready_queue);
        
    else if(algorithm == 1)
        SRTF(info, ready_queue);
    
    else
        RR(quantumsize, info, length, ready_queue);
    
    calculation(info, algorithm, quantumsize, length);

    return 0;
}
