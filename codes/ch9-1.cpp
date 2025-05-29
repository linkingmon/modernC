#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <thread>
#include <future>
#include <functional>
#include <random>
#include <chrono>
#include <variant>
#include <cstdlib>
#include <iomanip>
using namespace std;


class statistics {
    public: 
    // constructor
    statistics(int nThread = 8) : nThread(nThread) {}

    double mean(const vector<int>& v) const {
        vector<double> results = calc<double>(v, [this](const vector<int>& sub_v) {
            return static_cast<double>(accumulate(sub_v.begin(), sub_v.end(), (long long)0)) / sub_v.size();
        });
        return accumulate(results.begin(), results.end(), 0.0) / results.size();
    }
    // fucntion for max min nEven for vector v
    int max(const vector<int>& v) const {
        vector<int> results = calc<int>(v, [](const vector<int>& sub_v) {
            return *max_element(sub_v.begin(), sub_v.end());
        });
        return *max_element(results.begin(), results.end());
    }
    int min(const vector<int>& v) const {
        vector<int> results = calc<int>(v, [](const vector<int>& sub_v) {
            return *min_element(sub_v.begin(), sub_v.end());
        });
        return *min_element(results.begin(), results.end());    
    }
    int nEven(const vector<int>& v) const {
        vector<int> results = calc<int>(v, [](const vector<int>& sub_v) {
            return count_if(sub_v.begin(), sub_v.end(), [](int x) { return x % 2 == 0; });
        });
        return accumulate(results.begin(), results.end(), 0);
    }

    private:
    template<typename T>
    vector<T> calc(const vector<int>& v, function<T(const vector<int>&)> func) const {
        // create threads for each function
        vector<future<T>> futures;
        futures.reserve(nThread);
        for (int i = 0; i < nThread; ++i) {
            futures.emplace_back(
                async(launch::async, func, vector<int>(v.begin() + i * v.size() / nThread, v.begin() + (i + 1) * v.size() / nThread))
            );
        }
        // wait for all threads to finish and collect results
        vector<T> results;
        results.reserve(nThread);
        for (auto& fut : futures) {
            results.push_back(fut.get());
        }
        return results;
    }
    int nThread; // number of threads to use
};

int main () {
    cout << "Experimenting with multithreading in C++ for mean, min, max, and nEven calculations." << endl;
    // random number generation for 100000000 values
    std::vector<int> v(100'000'000);
    std::generate(v.begin(), v.end(), std::rand);
    vector<int> theardCnts = {1, 2, 4, 8};
    cout << setw(10) << "Threads"
        << setw(20) << "Result" 
        << setw(20) << "Time (ms)" << endl;
    for(auto nThread : theardCnts) {
        statistics stats(nThread);
        vector<function<variant<double, int>()>> funcs = { 
                [&stats, &v]() { return stats.mean(v); },
                [&stats, &v]() { return stats.min(v); },
                [&stats, &v]() { return stats.max(v); },
                [&stats, &v]() { return stats.nEven(v); }
        };

        for(auto& func : funcs) {
            auto start = chrono::high_resolution_clock::now();
            auto result = func();
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << setw(10) << nThread;
            if(std::holds_alternative<double>(result)) {
                cout << setw(20) << fixed << get<double>(result); 
            } else if(std::holds_alternative<int>(result)) {
                cout << setw(20) << fixed << get<int>(result);
            }
            cout << setw(20) << duration.count() << endl;
        }
    }
    return 0;
}