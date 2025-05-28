#include <iostream>
#include <vector>
#include <future>
#include <numeric> // for std::accumulate
using namespace std; 


int main () {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<int> large_vector(100'000'000, 1);
    std:future<int> fut = std::async( [=](){return std::accumulate(large_vector.begin(), large_vector.end(), 0); } );
    cout << "The sum of the large vector is: " << fut.get() << endl;
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    cout << "Time taken to compute the sum: " << elapsed.count() << " seconds" << endl;

    // use 4 threads to compute the sum
    cout << "Recommending number of threads: " << std::thread::hardware_concurrency() << endl;
    start = std::chrono::high_resolution_clock::now();
    std::vector<std::future<int>> futures;
    int num_threads = 8;
    int chunk_size = large_vector.size() / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        futures.push_back(std::async([=, &large_vector]() {
            int start_index = i * chunk_size;
            int end_index = (i == num_threads - 1) ? large_vector.size() : start_index + chunk_size;
            return std::accumulate(large_vector.begin() + start_index, large_vector.begin() + end_index, 0);
        }));
    }
    int total_sum = 0;
    for (auto& fut : futures) {
        total_sum += fut.get();
    }
    cout << "The total sum using " << num_threads << " threads is: " << total_sum << endl;
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start;
    cout << "Time taken to compute the sum with " << num_threads << " threads: " << elapsed2.count() << " seconds" << endl;
    return 0;
}