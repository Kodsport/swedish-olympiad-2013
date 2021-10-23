#include <vector>
#include <tuple>
#include <cstring>
#include <cmath>
#include "validate.h"

using namespace std;

int main(int argc, char **argv) {
	init_io(argc, argv);

    int N, T;
    judge_in >> N >> T;
    vector<int> L(N);
    for (int i = 0; i < N; i++) judge_in >> L[i];

    int judget, judgen;
    judge_ans >> judget >> judgen;

    int teamt, teamn;
    if (!(cin >> teamt)) wrong_answer("Could not read t_s");
    if (teamt < T) {
        wrong_answer("t_s not >= T");
    }
    if (!(cin >> teamn)) wrong_answer("Could not read n_s");

    vector<int> minutes(N);
    for (int i = 0; i < N; i++) {
        if (!(cin >> minutes[i])) wrong_answer("Could not read minutes for track %d", i);
    }
	string tmp;
	if (cin >> tmp) wrong_answer("Trailing output");

    int realteamn = 0;
    for (int i = 0; i < N; i++) {
        if (minutes[i] == 0) continue;
        if (minutes[i] < L[i]) wrong_answer("ran track, but less than full lap??");
        if (minutes[i] % (L[i] / 2)) wrong_answer("did not run track 1+0.5n number of times");
        realteamn += (minutes[i] + (L[i] / 2)) / L[i];
    }
    if (realteamn != teamn) wrong_answer("claimed to run %d times, but actually ran %d times", teamn, realteamn);

	if (teamt < judget) {
		judge_error("gave better t_s than judge");
	} else if (teamt > judget) {
		wrong_answer("gave worse t_s than judge");
	}
	if (teamn < judgen) {
		judge_error("gave better n_s than judge");
	} else if (teamn > judgen) {
		wrong_answer("gave worse n_s than judge");
	}
    accept();
}
