#pragma GCC optimize("O3,unroll-loops")
#include <bits/allocator.h>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>

using namespace std;

// Align arrays to 64-byte boundaries (width of an AVX-512 register / cache line)
alignas(64) int X_F[100005];
alignas(64) int Y_F[100005];
alignas(64) int X_A[100005];
alignas(64) int Y_A[100005];

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    for (int i = 0; i < N; ++i) {
        cin >> X_F[i] >> Y_F[i];
    }

    for (int j = 0; j < M; ++j) {
        cin >> X_A[j] >> Y_A[j];
    }

    long long min_dist = 9e18; // Positive infinity 

    // O(N * M) Hot Loop
    for (int j = 0; j < M; ++j) {
        int ax = X_A[j];
        int ay = Y_A[j];
        long long current_sum = 0;

        // Blocked accumulation: prevents 32-bit overflow while keeping SIMD math in 32-bit.
        // 32-bit vector math is 2x faster than 64-bit vector math because it fits 2x more elements.
        for (int i = 0; i < N; i += 1024) {
            unsigned int block_sum = 0;
            int limit = min(N, i + 1024);
            
            #pragma omp simd reduction(+:block_sum)
            for (int k = i; k < limit; ++k) {
                block_sum += std::abs(X_F[k] - ax) + std::abs(Y_F[k] - ay);
            }
            current_sum += block_sum;
        }

        if (current_sum < min_dist) {
            min_dist = current_sum;
        }
    }

    cout << min_dist << "\n";
    return 0;
}
