#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

const double eps = 1e-12;

double px[100005], py[100005];
int N;

// use f for ternary search
double f(double x) {
    double ret = 0;
    for (int i = 0; i < N; ++i) {
        double dx = px[i]-x;
        double dy = py[i];
        ret += sqrt(dx*dx + dy*dy);
    }
    return ret;
}

int main() {
    cin >> N;
    double l = 100000.0, r = -100000.0;
    for (int i = 0; i < N; ++i) {
        cin >> px[i] >> py[i];
        l = min(l,px[i]);
        r = max(r,px[i]);
    }

    while (l + eps < r) {
        double lt = l+(r-l)/3;
        double rt = l+2*(r-l)/3;
        double f1 = f(lt);
        double f2 = f(rt);
        if (f1 > f2) {
            l = lt;
        } else {
            r = rt;
        }
    }
    printf("%.9lf\n",2*f((l+r)/2));
}
