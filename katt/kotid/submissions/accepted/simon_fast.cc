#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

namespace {
int N, K;
const int INF = 1 << 30;

inline int left(int ind) { return 2*ind; }
inline int right(int ind) { return 2*ind + 1; }
inline int parent(int ind) { return ind >> 1; }

static const char digit_pairs[201] = {
  "00010203040506070809"
  "10111213141516171819"
  "20212223242526272829"
  "30313233343536373839"
  "40414243444546474849"
  "50515253545556575859"
  "60616263646566676869"
  "70717273747576777879"
  "80818283848586878889"
  "90919293949596979899"
};
char* itostr(char* out, int val) {
    // return out + sprintf(out, "%d ", val);

    if (val == 0) {
        *out++ = '0';
        *out++ = ' ';
        return out;
    }
 
    int size;
    if (val >= 10000) {
        if (val >= 10000000) {
            if (val >= 1000000000)
                size = 10;
            else if(val >= 100000000)
                size = 9;
            else 
                size = 8;
        }
        else {
            if (val >= 1000000)
                size = 7;
            else if (val >= 100000)
                size = 6;
            else
                size = 5;
        }
    }
    else {
        if (val >= 100) {
            if (val >= 1000)
                size = 4;
            else
                size = 3;
        }
        else {
            if (val >= 10)
                size = 2;
            else
                size = 1;
        }
    }
 
    char* b = out + size-1;
    while (val >= 10) {
        int pos = val % 100;
        val /= 100;
        *(short*)(b - 1) = *(short*)(digit_pairs + 2*pos); 
        b -= 2;
    }
    if (val > 0) {
        *b-- = '0' + (val % 10);
    }
    out += size;
    *out++ = ' ';
    return out;
}

template <int Log>
void loop(int pow2, int* __restrict__ nodes, int* __restrict__ results) {
    int nleft = N;
    for (int iteration = 0; nleft > 0; ++iteration) {
        int kleft = K;
        while (nodes[1] <= kleft) {
            int ind = 1;
            for (int i = 0; i < Log; ++i) {
                ind = (nodes[left(ind)] <= kleft ? left(ind) : right(ind));
            }

            int pos = ind - pow2;
            kleft -= nodes[ind];
            nodes[ind] = INF;
            results[pos] = iteration;
            --nleft;

            for (int i = 0; i < Log; ++i) {
                int nextv = min(nodes[ind], nodes[ind^1]);
                ind = parent(ind);
                if (nextv == nodes[ind])
                    break;
                nodes[ind] = nextv;
            }
        }
    }
}
}

int main() {
    if (scanf("%d %d", &N, &K) < 2) return 1;
    if (N == 0) return 0;

    int mask = N - 1;
    mask |= mask >> 1;
    mask |= mask >> 2;
    mask |= mask >> 4;
    mask |= mask >> 8;
    mask |= mask >> 16;
    int pow2 = mask + 1;

    int* nodes = (int*)malloc((pow2 * 2) * sizeof(int));
    int* results = (int*)malloc(N * sizeof (int));

    char buffer[5000];
    size_t read;
    int now = 0, ind = pow2;
    while ((read = fread((void*)buffer, 1, sizeof buffer, stdin))) {
        for (size_t i = 0; i < read; ++i) {
            if ('0' <= buffer[i] && buffer[i] <= '9') {
                now *= 10;
                now += buffer[i] - '0';
            }
            else if (now) {
                nodes[ind++] = now;
                now = 0;
            }
        }
    }
    if (now) {
        nodes[ind++] = now;
        now = 0;
    }

    for (int i = pow2 + N; i < 2*pow2; ++i)
        nodes[i] = INF;
    for (int i = pow2; i --> 1; ) {
        nodes[i] = min(nodes[left(i)], nodes[right(i)]);
    }

    int log = 0;
    for (int m = mask; m; m >>= 1)
        ++log;

#define LOOP(ind) case ind: loop<ind>(pow2, nodes, results); break
    switch (log) {
        LOOP(0);
        LOOP(1);
        LOOP(2);
        LOOP(3);
        LOOP(4);
        LOOP(5);
        LOOP(6);
        LOOP(7);
        LOOP(8);
        LOOP(9);
        LOOP(10);
        LOOP(11);
        LOOP(12);
        LOOP(13);
        LOOP(14);
        LOOP(15);
        LOOP(16);
        LOOP(17);
        LOOP(18);
        LOOP(19);
        LOOP(20);
        LOOP(21);
        LOOP(22);
        LOOP(23);
        LOOP(24);
    }

    char *it = buffer, *end = buffer + sizeof buffer - 50;
    for (int i = 0; i < N; ++i) {
        if (it > end) {
            fwrite(buffer, 1, it-buffer, stdout);
            it = buffer;
        }
        it = itostr(it, results[i]);
    }
    // it++; // preserve the last whitespace for no other reason than easy diffing
    *(it-1) = '\n';
    fwrite(buffer, 1, it-buffer, stdout);
    return 0;
}
