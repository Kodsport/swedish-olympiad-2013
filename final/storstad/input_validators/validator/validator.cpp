#include "validator.h"

const int MAX_N = 1e5;
const int MAX_M = 1e5;
const int MAX_COORD = 1e4;

void run() {
	int N = Int(1, Arg("maxn", MAX_N));
	Space();
	int M = Int(1, Arg("maxm", MAX_M));
	Endl();

	for (int i=0; i<N+M; i++) {
		int x = Int(-MAX_COORD, MAX_COORD);
		Space();
		int y = Int(-MAX_COORD, MAX_COORD);
		Endl();
	}
}
