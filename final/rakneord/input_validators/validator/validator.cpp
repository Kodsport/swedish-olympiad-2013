#include "validator.h"
#include <climits>

void run() {
	long long N = Int(1, Arg("n"));
	if (Arg("ismax", 0)) assert(N==999999999999);
	Space();
	long long K = Int(1, 86744000000000LL);
	Endl();
	Eof();
}