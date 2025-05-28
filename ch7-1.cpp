#include <iostream>
#include <thread>
#include <string>

void printThread(std::string message) {
    std::cout << "Thread " << std::this_thread::get_id() << ": " << message << std::endl;
}

int main () {
    std::thread t1(printThread, "thread A");
    std::thread t2(printThread, "thread B");
    t1.join();
    t2.join();
    return 0;
}