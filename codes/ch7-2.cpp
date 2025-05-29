#include <iostream>
#include <thread>
#include <future>
#include <vector>
using namespace std;

int main () {
    vector<int> numbers = {1, 2, 3, 4, 5};
    std::future<int> fut = std::async([numbers]() {
        int sum = 0;
        for (int num : numbers) {
            sum += num;
        }
        return sum;
    });
    std::cout << "Sum of numbers: " << fut.get() << std::endl;
    return 0;
}