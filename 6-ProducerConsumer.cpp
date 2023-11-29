#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> buffer;
const int BUFFER_SIZE = 5;

bool isBufferFull() {
    return buffer.size() >= BUFFER_SIZE;
}

bool isBufferEmpty() {
    return buffer.empty();
}

void producer() {
    for (int i = 1; i <= 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // Use a function instead of a lambda expression
        cv.wait(lock, isBufferFull);

        buffer.push(i);
        std::cout << "Produced: " << i << std::endl;

        lock.unlock();
        cv.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

void consumer() {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        // Use a function instead of a lambda expression
        cv.wait(lock, isBufferEmpty);

        int data = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << data << std::endl;

        lock.unlock();
        cv.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
