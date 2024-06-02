#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    int N = 19;
    int M = 20;
    cout << N << " " << M << endl;
    for (int i = 0; i < N; ++i) {

        // select random subset out of N nodes
        int buckets = (M + 31) / 32;
        unsigned int masks[buckets];
        for (int j = 0; j < buckets; ++j)
            masks[j] = (i < 1 ? (rand()) : (rand() & rand() & rand() & rand()));

        vector<int> pregen;
        for (int j = 0; j < M; ++j) if (masks[j/32] & (1<<(j%32))) pregen.push_back(j+1);
        cout << pregen.size() << " ";
        for (int j = 0; j < pregen.size(); ++j) {
            cout << pregen[j] << " ";
        }
        cout << endl;
    }
}
