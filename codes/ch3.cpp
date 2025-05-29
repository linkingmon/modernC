#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
using namespace std;

template<typename T>
void printVector(const vector<T>& v) {
    for (const auto& elem : v) {
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    cout << "\n\nProblem 1: Print even numbers from 1 to 30" << std::endl;
    cout << "--------------------------------" << std::endl;
    std::vector<int> v(30);
    std::iota(v.begin(), v.end(), 1); // Fill vector with 1s
    std::for_each(v.begin(), v.end(), [](int x) {
        if(x % 2 == 0) {
            cout << x << " "; // Print even numbers
        } 
    });
    cout << std::endl;
    
    cout << "\n\nProblem 2: Sort names in ascending order by length" << std::endl;
    cout << "--------------------------------" << std::endl;
    std::vector<string> names = {"Alice", "Bob", "Charlie", "David"};
    std::sort(names.begin(), names.end(), [](const string& a, const string& b) {
        return a.size() > b.size(); // Sort names in ascending order
    });
    printVector(names); // Print sorted names

    cout << "\n\nProblem 3: Transform numbers by doubling them" << std::endl;
    cout << "--------------------------------" << std::endl;
    vector<int> randomNumbers = {5, 3, 8, 1, 2, 7, 4, 6, 9, 10};
    cout << "Before transformation: " << endl;
    printVector(randomNumbers); // Print transformed numbers
    std::transform(randomNumbers.cbegin(), randomNumbers.cend(), randomNumbers.begin(), [](int x) {
        return x * 2; // Double each number
    });
    cout << "After transformation: " << endl;
    printVector(randomNumbers); // Print transformed numbers

    cout << "\n\nProblem 4: Calculate sum of numbers from 1 to 10 with offset 33" << std::endl;
    cout << "--------------------------------" << std::endl;
    int sum = 33;
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::for_each(numbers.begin(), numbers.end(), [&sum](int x) {
        sum += x;
    });
    cout << sum << endl; // Print sum of numbers with offset

    cout << "\n\nProblem 5: Print words longer than - characters" << std::endl;
    cout << "--------------------------------" << std::endl;
    int count = 6;
    vector<string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    std::for_each(words.begin(), words.end(), [count](const string& word) {
        if (word.size() > count) {
            cout << word << " "; // Print words longer than 4 characters
        }
    });
    cout << endl;

    cout << "\n\nProblem 6: Sort numbers in ascending order with a toggle" << std::endl;
    cout << "--------------------------------" << std::endl;
    bool ascending = true;
    vector<int> nums = {5, 3, 8, 1, 2};
    cout << "ascending: " << ascending << endl;
    std::sort(nums.begin(), nums.end(), [ascending](int a, int b) {
        return ascending ? a < b : a > b; // Sort in ascending order
    });
    printVector(nums); // Print sorted numbers
    ascending = !ascending; // Toggle ascending flag
    cout << "ascending: " << ascending << endl;
    std::sort(nums.begin(), nums.end(), [ascending](int a, int b) {
        return ascending ? a < b : a > b; // Sort in ascending order
    });
    printVector(nums); // Print sorted numbers
    return 0;
}