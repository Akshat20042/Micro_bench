// /**
//  * Demo for using Benchmarking using Google's benchmark platform:
//  * Run:
//          bazel run src/benchmark/main_benchmark -c opt -- --benchmark_format=csv | \
//          tee src/benchmark/outputs/main_benchmark.csv
//          python3 src/benchmark/plot.py src/benchmark/outputs/main_benchmark.csv
//  */
// #include "benchmark/benchmark.h"

// #include <chrono>
// #include <string>

// void SomeFunction(size_t size) {
//   std::string s1(size, '-');
//   std::string s2(size, '-');
//   benchmark::DoNotOptimize(s1.compare(s2));
// }

// static void BM_SomeFunction(benchmark::State& state) {
//   // Perform setup here
//   for (auto _ : state) {
//     // This code gets timed
//     SomeFunction(state.range(0));
//   }
// }
// // Register the function as a benchmark
// // BENCHMARK(BM_SomeFunction)->Arg(100000)->Arg(200000)->Arg(400000);

// BENCHMARK(BM_SomeFunction)->RangeMultiplier(2)->Range(1 << 10, 1 << 20);

// // Run the benchmark
// BENCHMARK_MAIN();



#include "benchmark/benchmark.h"

#include <vector>
#include <random>
#include <omp.h>

// Function to multiply matrices using OpenMP
void MatrixMultiply(int size) {
    std::vector<std::vector<int>> matrixA(size, std::vector<int>(size));
    std::vector<std::vector<int>> matrixB(size, std::vector<int>(size));
    std::vector<std::vector<int>> result(size, std::vector<int>(size, 0));

    // Initialize matrices with random values
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrixA[i][j] = dis(gen);
            matrixB[i][j] = dis(gen);
        }
    }

    // Matrix multiplication with OpenMP
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    benchmark::DoNotOptimize(result);
}

static void BM_MatrixMultiply(benchmark::State& state) {
    for (auto _ : state) {
        MatrixMultiply(state.range(0));
    }
}

// Register the function as a benchmark
BENCHMARK(BM_MatrixMultiply)->RangeMultiplier(2)->Range(2, 256);

// Run the benchmark
BENCHMARK_MAIN();
