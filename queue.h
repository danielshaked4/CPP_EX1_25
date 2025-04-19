// sone0149@gmail.com
#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

namespace graph {

    class Queue {
    private:
        int* items;
        unsigned int front;
        unsigned int rear;
        unsigned int capacity;

    public:
        Queue(int max_size);
        ~Queue();
        void push(int item);
        int pop();
        bool empty() const;
    };

}

#endif