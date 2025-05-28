
#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <mutex>
using namespace std;

void increment(int& value) {
    for (int i = 0; i < 100000; ++i) {
        ++value;
    }
}

std::mutex mtx;
void incrementWithLock(int& value) {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++value;
    }
}

int main () {
    int count = 10;
    for (size_t i = 0; i < count; i++)
    {
        int value = 0;
        std::thread t1(increment, std::ref(value));
        std::thread t2(increment, std::ref(value));
        std::thread t3(increment, std::ref(value));
        std::thread t4(increment, std::ref(value));
        t1.join();
        t2.join();
        t3.join();
        t4.join();

        int valueWithLock = 0;
        std::thread t5(incrementWithLock, std::ref(valueWithLock));
        std::thread t6(incrementWithLock, std::ref(valueWithLock));
        std::thread t7(incrementWithLock, std::ref(valueWithLock));
        std::thread t8(incrementWithLock, std::ref(valueWithLock));
        t5.join();
        t6.join();
        t7.join();
        t8.join();

        cout << "Trail " << i << " Value for no-lock and with-lock are: " 
             << value << " (no-lock), " 
             << valueWithLock << " (with-lock)" << endl;
    }
    return 0;
}