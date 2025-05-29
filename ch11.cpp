#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <chrono>
#include <unordered_map>
#include <string>
using namespace std;



int main () {
    // insert 1000000 element in vector and list to compare the time used
    cout << "\n\nProblem 1: Insert 10 million elements in vector and list" << std::endl;
    std::vector<int> vec;
    std::list<int> lst;
    int cnt = 10'000'000;
    auto start_vec = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < cnt; ++i) {
        vec.push_back(i);
    }
    auto end_vec = std::chrono::high_resolution_clock::now();
    auto duration_vec = std::chrono::duration_cast<std::chrono::milliseconds>(end_vec - start_vec);
    std::cout << "Time taken to insert elements in vector: " << duration_vec.count() << " ms" << std::endl;
    auto start_lst = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < cnt; ++i) {
        lst.push_back(i);
    }   
    auto end_lst = std::chrono::high_resolution_clock::now();
    auto duration_lst = std::chrono::duration_cast<std::chrono::milliseconds>(end_lst - start_lst);
    std::cout << "Time taken to insert elements in list: " << duration_lst.count() << " ms" << std::endl;

    cout << "\n\nProblem 2: Top-5 character frequencies in a paragraph" << std::endl; 
    string paragraph = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    unordered_map<string, int> word_count;
    for(const auto& c : paragraph) {
        // Only count alphabetic characters
        if (isalpha(c)) {
            // string(1, tolower(c)) creates a string of length 1 with the character c converted to lowercase
            word_count[string(1, tolower(c))]++;
        }
    }
    cout << "Top-5 character frequencies in the paragraph:" << endl;
    vector<pair<string, int>> sorted_word_count(word_count.begin(), word_count.end());
    sort(sorted_word_count.begin(), sorted_word_count.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Sort by frequency in descending order
    });
    for (int i = 0; i < 5 && i < sorted_word_count.size(); ++i) {
        cout << sorted_word_count[i].first << ": " << sorted_word_count[i].second << endl;
    }

    //建立一個 task queue，使用 list 管理任務物件，支援中間插入與刪除。
    cout << "\n\nProblem 3: Task queue using list" << std::endl;
    class Task {
    public:
        Task(int id) : id(id) {}
        int getId() const { return id; }
    private:
        int id;
    };

    class TaskQueue {
    public:
        void addTask(const Task& task) {
            tasks.push_back(task);
        }

        void removeTask(int id) {
            tasks.remove_if([id](const Task& task) { return task.getId() == id; });
        }

        void printTasks() const {
            for (const auto& task : tasks) {
                cout << "Task ID: " << task.getId() << endl;
            }
        }
    private:
        std::list<Task> tasks;
    };  
    TaskQueue queue;
    queue.addTask(Task(1));
    queue.addTask(Task(2));
    queue.addTask(Task(3));
    cout << "Tasks in the queue:" << endl;
    queue.printTasks();
    queue.removeTask(2);
    cout << "Tasks after removing Task 2:" << endl;
    queue.printTasks();
}