#include <iostream>
#include <vector>
#include <coroutine>
using namespace std;

template<typename T>
struct Generator {
    struct promise_type {
        T value;
        std::coroutine_handle<> continuation;

        auto get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        auto initial_suspend() {
            return std::suspend_always{};
        }

        auto final_suspend() noexcept {
            return std::suspend_always{};
        }

        void unhandled_exception() {
            std::terminate();
        }

        auto yield_value(T val) {
            value = val;
            return std::suspend_always{};
        }
    };

    using handle_type = std::coroutine_handle<promise_type>;

    Generator(handle_type h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); }

    bool has_value() const { return !handle.done(); }
    T value() const { return handle.promise().value; }
    bool next() { handle.resume(); return !handle.done(); }
    handle_type handle;
};

Generator<int> even_numbers(int n) {
    for (int i = 0; i <= n; i += 2) {
        co_yield i;
    }
}

Generator<string> generate_words() {
    co_yield "Alice";
    co_yield "Bob";
    co_yield "Charlie";
    co_yield "David";
    co_yield "Eve";
}

Generator<int> generate_Fibonacci(int n) {
    int a = 0, b = 1;
    for (int i = 0; i < n; ++i) {
        co_yield a;
        int next = a + b;
        a = b;
        b = next;
    }
}

int main() {
    cout << "\n\nProblem 1: Print even numbers from 0 to 30" << std::endl;
    auto even_gen = even_numbers(30);
    while(even_gen.next()) {
        std::cout << even_gen.value() << " ";
    }
    cout << std::endl;

    cout << "\n\nProblem 2: Print words" << std::endl;
    auto words_gen = generate_words();
    while(words_gen.next()) {
        std::cout << words_gen.value() << " ";
    }
    cout << std::endl;

    cout << "\n\nProblem 3: Generate Fibonacci sequence" << std::endl;
    auto fib_gen = generate_Fibonacci(10);
    while(fib_gen.next()) {
        std::cout << fib_gen.value() << " ";
    }
    cout << std::endl;
    return 0;
}