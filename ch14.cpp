#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <stdexcept>
#include <string>
#include <chrono>
#include <cassert>
using namespace std;


class Task {
public:
    Task(int id) : id(id) {
        cout << "Task " << id << " created." << endl;
    }
    ~Task() {
        cout << "Task " << id << " destroyed." << endl;
    }
    // copy constructor
    Task(const Task& other) : id(other.id) {
        cout << "Task " << id << " copied." << endl;
    }
    // move constructor
    Task(Task&& other) noexcept : id(other.id) {
        cout << "Task " << id << " moved." << endl;
        other.id = -1; // Invalidate the moved-from object
    }
    // move assginment operator
    Task& operator=(Task&& other) noexcept {
        if (this != &other) {
            cout << "Task " << id << " move assigned from Task " << other.id << "." << endl;
            id = other.id;
            other.id = -1; // Invalidate the moved-from object
        }
        return *this;
    }
    int getId() const { return id; }
    private:
    int id;
}; 

constexpr int square(int x) {
    return x * x;
}
int main () {
    cout << "\n\nProblem 1: Compare push_back and emplace_back in vector" << std::endl;
    std::vector<string> vec;
    int cnt = 1'000'000;
    auto start_push_back = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < cnt; ++i) {
        vec.push_back("text");
    }
    auto end_push_back = std::chrono::high_resolution_clock::now();
    auto duration_push_back = std::chrono::duration_cast<std::chrono::milliseconds>(end_push_back - start_push_back);
    std::cout << "Time taken to push_back 1 million elements in vector: " << duration_push_back.count() << " ms" << std::endl;
    
    auto start_emplace_back = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < cnt; ++i) {
        // only faster when the object is complex
        vec.emplace_back("text");
    }
    auto end_emplace_back = std::chrono::high_resolution_clock::now();
    auto duration_emplace_back = std::chrono::duration_cast<std::chrono::milliseconds>(end_emplace_back - start_emplace_back);
    std::cout << "Time taken to emplace_back 1 million elements in vector: " << duration_emplace_back.count() << " ms" << std::endl;

    cout << "\n\nProblem 2: Moving constructors and move assignment operator" << std::endl;
    {
    Task task(1);
    Task taskNext(2);
    Task taskMove = std::move(task); // Move task to taskMove
    taskNext = std::move(taskMove); // Move taskMove to taskNext
    }

    cout << "\n\nProblem 3: Calculate square of a number at compile time" << std::endl;
    static_assert(square(5) == 25);
    // static_assert(square(5) == 26); // uncomment to see the compile-time error
}