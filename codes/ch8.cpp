#include <iostream>
#include <vector>
#include <optional> // For std::optional
#include <variant>  // For std::variant
#include <tuple>   // For std::tuple
#include <string>
#include <chrono>  // For std::chrono
#include <ranges>  // For ranges and views
using namespace std;

std::optional<int> parseId(const int& value) {
    if (value < 0) {
        return std::nullopt; // Return an empty optional if the value is negative
    }
    return value; // Return the value wrapped in an optional
}

void printId(const std::optional<int>& id) {
    if (id) {
        std::cout << "ID: " << *id << std::endl; // Dereference the optional to get the value
    } else {
        std::cout << "Negative ID is not allowed" << std::endl; // Handle the case where the optional is empty
    }
}

void printValue(std::variant<int, std::string> value) {
    if (std::holds_alternative<int>(value)) {
        std::cout << "Value (int): " << std::get<int>(value) << std::endl; // Print the integer value
    } else {
        std::cout << "Value (string): " << std::get<std::string>(value) << std::endl; // Print the string value
    }
}

template<typename T>
inline void printConstExpr(T val) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "This is a constant expression that evaluates to an integral type: " << val << std::endl;
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "This is a constant expression that evaluates to a floating point type: " << val << std::endl;
    } else {
        std::cout << "This is a constant expression of an unknown type." << std::endl;
    }
}

int main () {
    cout << "\n\nProblem 8-1: Using std::optional for ID parsing\n";
    int value = 42; // Example value
    std::optional<int> id = parseId(value); // Call the function to parse the ID
    printId(id); // Print the ID if it exists
    
    value = -1; // Example of a negative value
    id = parseId(value); // Call the function again with a negative value
    printId(id); // Print the ID, which should indicate no value provided

    cout << "\n\nProblem 8-2: Using std::variant for value handling\n";
    printValue(42); // Call the function with an integer value
    printValue(std::string("Hello, World!")); // Call the function with a string value


    cout << "\n\nProblem 8-3: Using std::tuple for structured binding\n";
    std::tuple<int, double, std::string> myTuple(1, 3.14, "example");
    auto [intValue, doubleValue, stringValue] = myTuple; // Structured binding to unpack the tuple
    std::cout << "Tuple values: " << intValue << ", " << doubleValue << ", " << stringValue << std::endl; // Print the unpacked values

    cout << "\n\nProblem 8-4: Using constexpr for compile-time evaluation\n"; 
    printConstExpr(42); // Call the function with an integral constant expression
    printConstExpr(3.14); // Call the function with a floating point constant expression

    // g++ -std=c++20 -o ch8.cpp
    cout << "\n\nProblem 8-5: Using std::chrono for time measurement\n";
    vector<int> nums = {1, 2, 3, 4, 5, 6};
    auto result = nums
        | views::filter([](int n) { return n % 2 == 0; })       // 過濾偶數
        | views::transform([](int n) { return n * n; });        // 平方

    for (int x : result) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}