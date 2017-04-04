//modified from Data Structures and Other Objects by Savitch and Main

#ifndef QUEUE_H_HAIGH
#define QUEUE_H_HAIGH

#include "task.h"

class queue
    {
    public:

        static const int CAPACITY = 100;
        // CONSTRUCTOR
        queue();
		
        // MODIFICATION MEMBER FUNCTIONS
        void pop();
        void push(const Task& entry);
        void arrival_sort();
        void CPU_sort();
        void shorter_task();
		
        // CONSTANT MEMBER FUNCTIONS
        bool empty() const {return (count == 0);}
        Task front() const;
        int size() const {return count;}
    
	private:
        Task data[CAPACITY];     
        int first;         // Index of item at front of the queue
        int last;          // Index of item at rear of the queue
        int count;         // Total number of items in the queue
        int next_index(int i) const {return (i+1) % CAPACITY;}
    };
	
	#endif