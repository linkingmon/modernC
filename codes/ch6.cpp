#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

template<typename T>
void printVector(const vector<T>& vec) {
    for (const auto& elem : vec) {
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    cout << "\n\nProblem 6-1: Lambda Functions" << endl;
    vector<string> names = {"Alice", "Bob", "Charlie"};
    std::for_each(names.begin(), names.end(), [](const string& name) {
        cout << "Hello, " << name << "!" << endl;
    });


    cout << "\n\nProblem 6-2: Sorting with decending order" << endl; 
    vector<double> numbers = {1.1, 2.2, 3.3, 4.8, 3.2, 5.5};
    sort(numbers.begin(), numbers.end(), [](double a, double b) {
        return a > b;
    });
    cout << "Sorted numbers in descending order: ";
    printVector(numbers);

    
    cout << "\n\nProblem 6-3: Counting elements with a condition" << endl;
    vector<string> words = {"apple", "banana", "cherry", "date", "elderberry", "fig", "grape"};
    int cnt = std::count_if(words.begin(), words.end(), [](const string& word) {
        return word.length() > 5;
    });
    cout << "Number of words longer than 5 characters: " << cnt << endl;

    cout << "\n\nProblem 6-4: Transforming elements in a vector" << endl;
    vector<int> numbers2 = {1, 2, 3, 4, 5};
    vector<int> squares;
    squares.resize(numbers2.size());
    std::transform(numbers2.begin(), numbers2.end(), squares.begin(), [](int n) {
        return n * n;
    });
    printVector(squares);

    return 0;
}