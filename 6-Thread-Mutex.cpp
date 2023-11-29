#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

const int buffer_size = 5;  // Size of the shared buffer

std::vector<int> buffer;  // Shared buffer
std::mutex mtx;           // Mutex for synchronization
std::condition_variable cv;  // Condition variable for synchronization

// Function to simulate a producer
void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait if the buffer is full
        cv.wait(lock, [] { return buffer.size() < buffer_size; });

        // Produce an item and add it to the buffer
        int item = rand() % 100;
        buffer.push_back(item);
        std::cout << "Producer " << id << " produced: " << item << " (Buffer size: " << buffer.size() << ")\n";

        // Notify consumers that the buffer is not empty anymore
        cv.notify_all();
    }
}

// Function to simulate a consumer
void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait if the buffer is empty
        cv.wait(lock, [] { return !buffer.empty(); });

        // Consume an item from the buffer
        int item = buffer.back();
        buffer.pop_back();
        std::cout << "Consumer " << id << " consumed: " << item << " (Buffer size: " << buffer.size() << ")\n";

        // Notify producers that the buffer is not full anymore
        cv.notify_all();
    }
}

int main() {
    // Create producer and consumer threads
    std::thread producer_thread(producer, 1);
    std::thread consumer_thread(consumer, 1);

    // Join the threads with the main thread
    producer_thread.join();
    consumer_thread.join();

    return 0;
}
