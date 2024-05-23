#include "validator.h"

void run() {
	int n = 1 << (int)Int(1, 10);
	Endl();

	SpacedFloats(n, 0, 10, 3);
	Eof();
}