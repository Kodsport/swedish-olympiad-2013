#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long double ld;

#define repe(i, container) for (auto& i : container)

map<int, pair<ld, ld>> winningProb(vector<pair<int,ld>>& strengths)
{
    if (strengths.size() == 1)
    {
        return { {strengths[0].first, {1, strengths[0].second}}};
    }

    std::size_t const half_size = strengths.size() / 2;
    vector<pair<int, ld>> split_lo(strengths.begin(), strengths.begin() + half_size);
    vector<pair<int, ld>> split_hi(strengths.begin() + half_size, strengths.end());

    map<int, pair<ld, ld>> bottom = winningProb(split_lo);
    map<int, pair<ld, ld>> top = winningProb(split_hi);

    map<int, pair<ld, ld>> ret;
    repe(i, bottom)
    {
        repe(j, top)
        {
            if (ret.find(i.first)==ret.end())
            {
                ret[i.first] = { 0, i.second.second };
            }
            if (ret.find(j.first)==ret.end())
            {
                ret[j.first] = { 0, j.second.second };
            }
            ret[i.first].first += 1 / (1 + exp(j.second.second - i.second.second)) * i.second.first*j.second.first;
            ret[j.first].first += 1 / (1 + exp(i.second.second - j.second.second)) * j.second.first*i.second.first;
        }
    }

    return ret;
}

const ld epsilon = 1e-5;
int main(int argc, char **argv) {
	init_io(argc, argv);

	int n;
	judge_in >> n;
	int numplayers = 1<<n;
	vector<pair<int, ld>> strengths(numplayers);
	rep(i,0, numplayers)
	{
		ld s;
		judge_in >> s;
		strengths[i] = { i, s };
	}
	map<int, pair<ld, ld>> winner = winningProb(strengths);
	long double bestscore = 0;
	for (auto p : winner)
	{
		bestscore = max(bestscore, p.second.first);
	}

	auto check = [&](istream& sol, feedback_function feedback) {
		int contestantind;
		ld contestantans;
		if (!(sol >> contestantind >> contestantans)) feedback("Expected more output");
		if (contestantind <= 0 || contestantind>numplayers) feedback("Invalid index of best player");
		contestantind--;

		if (abs(contestantans-bestscore)>epsilon) feedback("Contestant win probability is not same as judge");

		for (auto p : winner)
		{
			if (p.first==contestantind)
			{
				if (abs(contestantans-p.second.first)>epsilon) feedback("Did not correctly determine win probability for chosen contestant");
			}
		}

		string trailing;
		if(sol >> trailing) feedback("Trailing output");
		return true;
	};

	bool judge_found_sol = check(judge_ans, judge_error);
	bool author_found_sol = check(author_out, wrong_answer);

	if(!judge_found_sol)
		judge_error("NO! judge got WA");

	if(!author_found_sol)
		wrong_answer("Contestant did not find optimal");

	accept();
}
