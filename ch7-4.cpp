
#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <mutex>
#include <chrono>
#include <functional>
using namespace std::chrono_literals;
using namespace std;

void calculate() {
    std::this_thread::sleep_for(1s);
    std::cout << "Calculation done." << std::endl;
}

// future_status contains three values:
// 1. ready: The asynchronous operation has completed.
// 2. timeout: The operation has not completed within the specified time.
// 3. deferred: The operation has not started yet and will not start until the result is needed.

int main () {
    future<void> fut = async(launch::async, calculate);
    int timeout = 0;
    // if launch::async is not specified, the function will be executed in a deferred manner.
    // In this case, the future will not be ready until the result is needed.
    while(fut.wait_for(100ms) != std::future_status::ready) {
        timeout += 100;
        std::cout << "timeout: " << timeout << " seconds remaining." << std::endl;
    }
    
    return 0;
}