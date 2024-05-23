#include <iostream>
#include <cstdlib>

using namespace std;

// params: N, M, A
int main() {
    srand(time(0));
    int N, M, A;
    cin >> N >> M >> A;
    cout << N << " " << M << endl;
    for (int i = 0; i < N; ++i) {
        int x,y;
        x = max(-A+1,(rand()%(2*A))-A);
        y = max(-A+1,(rand()%(2*A))-A);
        cout << x << " " << y << endl;
    }
    for (int i = 0; i < M; ++i) {
        int x,y;
        x = max(-A+1,(rand()%(2*A))-A);
        y = max(-A+1,(rand()%(2*A))-A);
        cout << x << " " << y << endl;
    }
}
