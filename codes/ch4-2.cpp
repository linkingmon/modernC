#include <iostream>
#include <unordered_map>
using namespace std;

int main () {
    unordered_map<int, int> my_map;
    // randomly generated code to fill the map with rand()
    for (int i = 0; i < 10; ++i) {
        my_map[i] = rand() % 100; // Fill with random values
    }
    for(const auto& [idx, value]: my_map) {
        std::cout << "Index: " << idx << ", Value: " << value << std::endl;
    }
    return 0;
}