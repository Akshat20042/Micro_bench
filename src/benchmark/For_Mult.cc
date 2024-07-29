#include "benchmark/benchmark.h"
using namespace std;
#include <vector>
#include <random>

// Function to multiply matrices
void MatrixMultiply(int size) {
    vector<vector<int>> matrixA(size, vector<int>(size));
    vector<vector<int>> matrixB(size, vector<int>(size));
    vector<vector<int>> result(size, vector<int>(size, 0));

    // Initialize matrices with random values
    random_device rd;
    mt19937 gen(rd());
   uniform_int_distribution<> dis(1, 10);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrixA[i][j] = dis(gen);
            matrixB[i][j] = dis(gen);
        }
    }

   
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


BENCHMARK(BM_MatrixMultiply)->RangeMultiplier(2)->Range(2, 256);


BENCHMARK_MAIN();

