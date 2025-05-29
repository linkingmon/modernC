#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>
#include <execution>
using namespace std;

class Timer 
{
public:
    void call() const {
        ++cnt;
        // name += "test"; // uncommenting this line will cause a compilation error due to const correctness
    }

    int getCount() const {
        return cnt;
    }
    private:
    mutable int cnt = 0; // Counter for the number of calls
    string name = "Timer"; // Name of the timer
};

template<typename T>
concept Iterable = requires(T t) {
    { begin(t) } -> std::input_iterator;
    { end(t) } -> std::input_iterator;
};

template<Iterable Container>
void printContainer(const Container& container) {
    for (const auto& item : container) {
        cout << item << " ";
    }
    cout << endl;
}

int main () {
    cout << "\n\nProblem1: Timer class with const method and mutable member" << endl;
    Timer timer;
    for(int i = 0; i < 10; ++i) {
        timer.call(); // Call the timer method
    }
    cout << "Timer called " << timer.getCount() << " times." << endl; // Output the number of calls

    cout << "\n\nProblem2: Print contents of containers using concepts" << endl;
    vector<int> vec = {1, 2, 3, 4, 5};
    printContainer(vec); // Print the contents of the vector
    list<string> lst = {"Hello", "World", "C++", "Concepts"};
    printContainer(lst); // Print the contents of the list
    // printContainer(1) // Uncommenting this line will cause a compilation error because int is not iterable

    cout << "\n\nProblem3: Measure time taken to square elements in a large vector" << endl;
    vector<int> large_vec(100'000'000, 42); // Create a large vector with 1 million elements
    auto start = std::chrono::high_resolution_clock::now();
    std::transform(large_vec.cbegin(), large_vec.cend(), large_vec.begin(), [](int x) { return x * x; });
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Time taken to square 1 million elements in vector: " << duration.count() << " ms" << endl;

    large_vec = vector<int>(100'000'000, 42); // Reset the vector to the same size and value
    start = std::chrono::high_resolution_clock::now();
    std::transform(std::execution::par_unseq, large_vec.cbegin(), large_vec.cend(), large_vec.begin(), [](int x) { return x * x; });
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Time taken to parallel square 1 million elements in vector: " << duration.count() << " ms" << endl;

    return 0;
}