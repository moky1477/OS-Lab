#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

const int BUFFER_SIZE = 5;

queue<int> buffer;
mutex mtx;
condition_variable producer_cv, consumer_cv;

void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        unique_lock<mutex> lock(mtx);

        // Wait if the buffer is full
        producer_cv.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });

        int item = rand() % 100;
        buffer.push(item);
        cout << "Producer " << id << " produced: " << item << " (Buffer size: " << buffer.size() << ")" << endl;

        // Notify consumer that an item is produced
        consumer_cv.notify_one();
    }
}

void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        unique_lock<mutex> lock(mtx);

        // Wait if the buffer is empty
        consumer_cv.wait(lock, [] { return !buffer.empty(); });

        int item = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed: " << item << " (Buffer size: " << buffer.size() << ")" << endl;

        // Notify producer that an item is consumed
        producer_cv.notify_one();
    }
}

int main() {
    thread producer1(producer, 1);
    thread producer2(producer, 2);
    thread consumer1(consumer, 1);
    thread consumer2(consumer, 2);

    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();

    return 0;
}
