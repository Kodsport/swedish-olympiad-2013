#include "validator.h"

void run() {
	int N, K;
	N = Int(1, 100);
	Space();
	K = Int(1, 10000);
	Endl();

	for (int i=0; i<N; i++) {
		SpacedInts(N, 1, 1000);
	}
	SpacedInts(K, 1, 1000);
	Eof();
}