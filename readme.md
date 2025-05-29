# Modern C++ Notes and Exercises

This repository contains notes and hands-on exercises designed by chatGPT for **Modern C++** features, including C++11, C++14, C++17, and C++20.

## 📚 Table of Contents

| Chapter | Topic                                  | Description |
|---------|----------------------------------------|-------------|
| 01      | C++ Basics Refresher                   | Variables, references, RAII, `nullptr` |
| 02      | Smart Pointers and Resource Management | `unique_ptr`, `shared_ptr`, `weak_ptr`, circular reference |
| 03      | Lambda Expressions                     | Syntax, capture list, STL integration |
| 04      | Type Deduction                         | `auto`, `decltype`, return type deduction |
| 05      | Templates and Type Traits              | Function/class templates, `enable_if`, `constexpr` |
| 06      | STL and Range-based For Loops          | Common STL containers and algorithms (`sort`, `count_if`, etc.) |
| 07      | Concurrency and Thread Support         | `std::thread`, `std::async`, `mutex`, synchronization |
| 08      | C++17/20 Features                      | `std::optional`, `variant`, structured binding, ranges |
| 09      | * Project Review                       | Two projects applying features from chapters 1–8          |
| 10      | Coroutines & Generators                | Use `co_yield` and create resumable generators            |
| 11      | STL Container Internals                | Compare `vector`, `list`, `map`, `unordered_map` etc.     |
| 12      | Modern c++ Design Patterns             | strategy, observer, state, factory pattern                |
| 13      | Exception and Unit Testing             | Use `doctest` to test C++ code                            |
| 14      | Modern c++ Performance Enhance         | `std::move`, `emplace_back`                               |
| 15      | Move, Atomic, Parallel, Concepts       | Use `std::move`, `atomic`, `execution`, and `concepts`    |

---

## 🛠 Build Tips

- If C++20 required: compile with `-std=c++20`
- Example:
  ```bash
  g++ -std=c++20 -O2 *.cpp  
