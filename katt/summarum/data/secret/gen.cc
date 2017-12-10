#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));
    int N;
    cin >> N;
    cout << N << endl;
    for (int i = 0; i < N; ++i) {
        int printedNumber = (rand()%200001)-100000;
        cout << printedNumber;
        if (i != N-1)
            cout << " ";
    }
    cout << endl;
    for (int i = 0; i < N; ++i) {
        int printedNumber = (rand()%200001)-100000;
        cout << printedNumber;
        if (i != N-1)
            cout << " ";
    }
    cout << endl;
}
