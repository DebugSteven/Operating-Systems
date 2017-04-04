//modified from Data Structures and Other Objects by Savitch and Main 


#include <cassert>
#include "queue.h"
#include "task.h"
    
    queue::queue()
    {
        count = 0;
        first = 0;
        last = CAPACITY - 1;
    }

    Task queue::front() const
    {
        assert(!empty( ));
	return data[first];
    }

    void queue::pop()
    {
        assert(!empty());
        first = next_index(first);
        --count;    
    }
    
    void queue::push(const Task& entry)
    {
        assert(size() < CAPACITY);
        last = next_index(last);
        data[last] = entry;
        ++count;
    }

    void queue::arrival_sort()
    {
        Task temp;
        for(int i = 0; i < count; i++)
        {
            for(int j = 0; j < (count-1); j++)
            {
                if(data[j+1].arrival_time < data[j].arrival_time)
                {
                    temp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = temp;
                }
            }
        }
    }

    void queue::CPU_sort()
    {
        Task temp;
        for(int i = 0; i < count; i++)
        {
            for(int j = 0; j < (count-1); j++)
            {
                if(data[j+1].CPU_burst < data[j].CPU_burst)
                {
                    temp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = temp;
                }
            }
        }

    }

    void queue::shorter_task()
    {
    
    }

