#include <iostream>
#include <string>
using namespace std;
 
string str, posstr, mem[4];
int N;
 
bool f(bool prev, bool cur, int pos) {
        if (pos == N) {
                return true;
        }
        char& out = mem[(prev?2:0) + (cur?1:0)][pos];
        if (out)
                return out-1;
        char c = str[pos];
        bool works = false;
        for (int inext = 0; inext < 2; ++inext) {
                if (pos+1 == N && inext) continue;
                bool next = inext;
                if (c != 'X' && prev + cur + next != (c - '0')) continue;
                bool thisWorks = f(cur, next, pos+1);
                if (thisWorks)
                        posstr[pos] |= (cur ? 2 : 1);
                works |= thisWorks;
        }
        out = works+1;
        return works;
}
 
int main() {
        getline(cin, str);
        N = (int)str.size();
        for (int i = 0; i < N; ++i) {
                if (str[i] == 'X') {
                        if (i && str[i-1] != 'X') --str[i-1];
                        if (i+1 < N && str[i+1] != 'X') --str[i+1];
                }
        }
        posstr = mem[0] = mem[1] = mem[2] = mem[3] = string(N, (char)0);
 
        f(false, true, 0);
        f(false, false, 0);
        if (!N || posstr[0]) {
                char ar[4] = {'-', 'S', 'X', 'O'};
                for (int i = 0; i < N; ++i)
                        cout << ar[(int)posstr[i]];
                cout << endl;
        }
        else {
                cout << "fel" << endl;
        }
        return 0;
}