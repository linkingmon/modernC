#include <iostream>
using namespace std;

template <typename T>
auto square(T x) -> decltype(x * x) {
    return x * x;
}

int main () {
    int i = 5;
    double d = 3.14;
    auto i_squared = square(i);
    auto d_squared = square(d);
    std::cout << "Square of " << i << " is " << i_squared << std::endl;
    std::cout << "Square of " << d << " is " << d_squared << std::endl;
    return 0;
}