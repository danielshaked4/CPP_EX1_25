// sone0149@gmail.com
#include "priority_queue.h"

namespace graph {

    PriorityQueue::PriorityQueue(int max_size) : size(0), capacity(max_size) {
        heap = new Node[max_size];
    }

    PriorityQueue::~PriorityQueue() {
        delete[] heap;
    }

    void PriorityQueue::heapify_up(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].distance >= heap[parent].distance) break;
            Node temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;
            index = parent;
        }
    }

    void PriorityQueue::heapify_down(int index) {
        while (true) {
            int smallest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < size && heap[left].distance < heap[smallest].distance) {
                smallest = left;
            }
            if (right < size && heap[right].distance < heap[smallest].distance) {
                smallest = right;
            }
            if (smallest == index) break;

            Node temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;
            index = smallest;
        }
    }

    void PriorityQueue::push(int vertex, int distance) {
        if (size >= capacity) {
            throw std::overflow_error("Priority queue is full");
        }
        heap[size] = Node(distance, vertex);
        heapify_up(size);
        size++;
    }

    PriorityQueue::Node PriorityQueue::pop() {
        if (empty()) {
            throw std::runtime_error("Priority queue is empty");
        }

        Node result = heap[0];
        heap[0] = heap[size - 1];
        size--;

        if (size > 0) {
            heapify_down(0);
        }

        return result;
    }

    bool PriorityQueue::empty() const {
        return size == 0;
    }

}