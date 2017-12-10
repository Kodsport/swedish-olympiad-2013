#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long L;

int main() {
    L N;
    cin >> N;
    vector<L> arr1, arr2;
    L A = 0;
    L B = 0;
    for (int i = 0; i < N; ++i) {
        L cur;
        cin >> cur;
        arr1.push_back(cur);
        A += cur;
    }
    for (int i = 0; i < N; ++i) {
        L cur ;
        cin >> cur;
        arr2.push_back(cur);
        B += cur;
    }

    sort(arr2.begin(),arr2.end());

    L minimum = 1LL<<62;
    for (int i = 0; i < N; ++i) {
        L diff = B + 2*arr1[i] - A;
        L look = ceil(diff/2.0);
        size_t pos = (lower_bound(arr2.begin(), arr2.end(),look)-arr2.begin());
        if (pos < N) {
            minimum = min(minimum, abs((B-arr2[pos]+arr1[i]) - (A-arr1[i]+arr2[pos])));
        }
        --pos;
        if (pos >= 0) {
            minimum = min(minimum, abs((B-arr2[pos]+arr1[i]) - (A-arr1[i]+arr2[pos])));
        }
    }

    cout << minimum << endl;
}
