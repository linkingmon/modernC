#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <stdexcept>
#include <string>
using namespace std;

double divide(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    return static_cast<double>(a) / b;
}

int main () {
    try {
        std::cout << "10 / 2 = " << divide(10, 2) << std::endl;
        std::cout << "10 / 0 = " << divide(10, 0) << std::endl; // This will throw an exception
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl; // Catch and handle the exception
    }
    return 0;
}