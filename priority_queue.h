// sone0149@gmail.com
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdexcept>

namespace graph {

    class PriorityQueue {
    public:
        struct Node {
            int distance;
            int vertex;
            Node() : distance(0), vertex(-1) {} // Default constructor
            Node(int d, int v) : distance(d), vertex(v) {}
        };

    private:
        Node* heap;
        int size;
        int capacity;

        void heapify_up(int index);
        void heapify_down(int index);

    public:
        PriorityQueue(int max_size);
        ~PriorityQueue();
        void push(int vertex, int distance);
        Node pop();
        bool empty() const;
    };

}

#endif