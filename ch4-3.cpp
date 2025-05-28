#include <iostream>
#include <vector>
using namespace std;

int main () {
    vector<tuple<int,string,double>> my_tuples;
    // initialize the vector with some tuples
    my_tuples.emplace_back(1, "apple", 0.5);    
    my_tuples.emplace_back(2, "banana", 0.75);
    my_tuples.emplace_back(3, "cherry", 1.25);
    my_tuples.emplace_back(4, "date", 1.0);

    using tupleType = remove_reference<decltype(my_tuples[0])>::type; 
    tupleType element = {2, "banana", 0.75};
    cout << "Element: " << get<0>(element) << ", " 
         << get<1>(element) << ", " 
         << get<2>(element) << endl;
    return 0;
} 