// sone0149@gmail.com
#include "queue.h"

namespace graph {

    Queue::Queue(int max_size) : front(0), rear(0), capacity(max_size) {
        items = new int[max_size];
    }

    Queue::~Queue() {
        delete[] items;
    }

    void Queue::push(int item) {
        if (rear >= capacity) {
            throw std::overflow_error("Queue is full");
        }
        items[rear++] = item;
    }

    int Queue::pop() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return items[front++];
    }

    bool Queue::empty() const {
        return front == rear;
    }

} // namespace graph