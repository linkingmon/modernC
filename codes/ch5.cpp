#include <iostream>
#include <string>
using namespace std;

template <typename T>
T maxOfThree(T a, T b, T c) {
    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

// Template functions to return first and second elements of a pair
template <typename T1, typename T2>
T1 retFirst(const pair<T1, T2>& p) {
    return p.first;
}
template <typename T1, typename T2>
T2 retSecond(const pair<T1, T2>& p) {
    return p.second;
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type isEven(T n) {
    return n % 2 == 0;
}

int main () {
    cout << "\n\nProblmem 5-1: Template Functions" << endl;
    cout << "Max of 3 integers: " << maxOfThree(3, 7, 5) << endl;
    cout << "Max of 3 doubles: " << maxOfThree(2.5, 3.1, 1.4) << endl; 
    cout << "Max of 3 strings: " << maxOfThree(string("apple"), string("banana"), string("cherry")) << endl;


    cout << "\n\nProblmem 5-2: Template Functions with Pairs" << endl;
    pair<int, string> p1(1, "apple");
    cout << "Pair first and second: " 
         << retFirst(p1) << ", " 
         << retSecond(p1) << endl;
    pair<double, string> p2(2.5, "banana");
    cout << "Pair first and second: " 
         << retFirst(p2) << ", " 
         << retSecond(p2) << endl;

    cout << "\n\nProblmem 5-3: Template Functions with Enable If" << endl;
    cout << "Is 4 even? " << (isEven(4) ? "Yes" : "No") << endl;
    cout << "Is 5 even? " << (isEven(5) ? "Yes" : "No") << endl;
    // SFINAE: Uncommenting the following line will cause a compilation error
    // cout << "Is 5.5 even? " << (isEven(5.5) ? "Yes" : "No") << endl;
    return 0;
}