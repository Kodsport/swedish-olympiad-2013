#include "validator.h"

typedef long long ll;

void run() {
	int l  = Arg("maxl");

    string inp = Line();
    assert(1 <= inp.size() && inp.size() <= l);
    for (char c : inp) {
        assert(c == 'N' || c == 'B' || c == 'S');
    }
    Eof();
}
