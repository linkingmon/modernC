
// generatet 10 thread and print its id
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <functional>
using namespace std;

int main() {
    int threadCnt = 10;
    cout << "With mutex lock:" << endl;
    std::vector<std::thread> threads;
    std::mutex mtx;

    for (int i = 0; i < threadCnt; ++i) {
        threads.emplace_back([i, &mtx]() {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "Thread ID: " << std::this_thread::get_id() << " - Index: " << i << std::endl;
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    // if no lock guard is used, the output may be interleaved
    cout << "Without mutex lock:" << endl;
    threads.clear();
    for (int i = 0; i < threadCnt; i++) {
        threads.emplace_back([i]() {
            std::cout << "Thread ID: " << std::this_thread::get_id() << " - Index: " << i << std::endl;
        });
    }
    for(auto& t : threads) {
        t.join();
    }

    return 0;
}