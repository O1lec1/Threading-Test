#include <cstring>
#include <mutex>
#include <vector>
#include <iostream>
#include <condition_variable>
#include <chrono>
#include <thread>

struct BoundedBuffer {
    int* buffer;
    int capacity;
    int front;
    int rear;
    int count;

    std::mutex lock;

    std::condition_variable not_full;
    std::condition_variable not_empty;

    BoundedBuffer(int capacity) :
        capacity(capacity),
        front(0),
        rear(0),
        count(0)
    {
        buffer = new int[capacity];
        std::memset(buffer, 0, sizeof(*buffer));
    }

    ~BoundedBuffer(){
        delete[] buffer;
    }

    void deposit(int data){
        std::unique_lock<std::mutex> l(lock);

        // Blocks until the buffer is not full anymore.
        // Blocks the thread, "releases" the mutex until the condition is
        // woken up.
        // 1st parameter l is the lock that we must have acquired.
        // 2nd parameter is a predicate (that is a function that returns a
        // bool).
        not_full.wait(l, [&](){return count != capacity; });

        buffer[rear] = data;
        rear = (rear + 1) % capacity;
        ++count;

        // Matches a call to wait.
        not_empty.notify_one();
    }

    int fetch(){
        std::unique_lock<std::mutex> l(lock);

        // Blocks until the buffer is not empty anymore.
        not_empty.wait(l, [&](){return count != 0; });

        int result = buffer[front];
        front = (front + 1) % capacity;
        --count;

        not_full.notify_one();

        return result;
    }
};

void consumer(std::mutex &m, int id, BoundedBuffer& buffer){
    for(int i = 0; i < 10; ++i)
    {
        int value = buffer.fetch();
        // Braces are used to help scope the unique lock object.
        {
            // Just to facilitate writing
            std::unique_lock<std::mutex> l(m);
            std::cout << "Consumer " << id << " fetched " << value << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(25+rand()%10));
    }
}

void producer(std::mutex &m, int id, BoundedBuffer& buffer){
    for(int i = 0; i < 15; ++i)
    {
        int n = rand() % 1000;
        buffer.deposit(n);
        // Braces are used to help scope the unique lock object.
        {
            // Just to facilitate writing
            std::unique_lock<std::mutex> l(m);
            std::cout << "Producer " << id << " produced " << n << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100+rand()%10));
    }
}

int main2(){
    BoundedBuffer buffer(2);

    srand(time(NULL));

    // For writing on standard output purposes
    std::mutex m;

    // The thread constructor cannot take references, although we need to have
    // references to the mutex and to the buffer.
    // std::reference_wrapper wraps a reference inside a copyable assignable
    // object. std::ref is a helper function for reference_wrapper.
    std::vector<std::thread> threads;
    for (int i = 0; i < 3; i++)
    {
        threads.push_back(std::thread(consumer, std::ref(m), i, std::ref(buffer)));
    }

    for (int i = 0; i < 2; i++)
    {
        threads.push_back(std::thread(producer, std::ref(m), i, std::ref(buffer)));
    }

    for (auto &t : threads)
    {
        t.join();
    }
    return 0;
}
