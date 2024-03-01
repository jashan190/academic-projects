#ifndef DLL_DEQUE
#define DLL_DEQUE

#include <list>
#include <iostream>

template<class T>
class Deque {
public:
    Deque() {}

    void clear() {
        lst.clear();
    }

    bool isEmpty() const {
        return lst.empty();
    }

    // Access the front element
    T& front() {
        return lst.front();
    }

    // Access the rear element
    T& back() {
        return lst.back();
    }

    // Remove the front element
    T dequeueFront() {
        T el = lst.front();
        lst.pop_front();
        return el;
    }

    // Remove the rear element
    T dequeueBack() {
        T el = lst.back();
        lst.pop_back();
        return el;
    }

    // Insert at the front
    void enqueueFront(const T& el) {
        lst.push_front(el);
    }

    // Insert at the rear
    void enqueueBack(const T& el) {
        lst.push_back(el);
    }

private:
    std::list<T> lst;
};

#endif

int main() {
    // Example usage
    Deque<int> deque;
    deque.enqueueFront(10);
    deque.enqueueBack(20);
    deque.enqueueFront(30);

    std::cout << "Front element: " << deque.front() << std::endl;
    std::cout << "Rear element: " << deque.back() << std::endl;

    deque.dequeueFront();
    deque.dequeueBack();


    return 0;
}

