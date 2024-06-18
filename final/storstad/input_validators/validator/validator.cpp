#include "validator.h"

void run() {
	int N = Int(1, 100000);
	Space();
	int M = Int(1, 100000);
	Endl();

	for (int i=0; i<N+M; i++) {
		int x = Int(-10000, 10000);
		Space();
		int y = Int(-10000, 10000);
		Endl();
	}
	Eof();
}