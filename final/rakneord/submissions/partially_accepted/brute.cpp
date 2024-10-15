#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

map<int, string> basecases;
map<int, string> tens;
void init()
{
	basecases[1] = "ett";
	basecases[2] = "tva";
	basecases[3] = "tre";
	basecases[4] = "fyra";
	basecases[5] = "fem";
	basecases[6] = "sex";
	basecases[7] = "sju";
	basecases[8] = "atta";
	basecases[9] = "nio";
	basecases[10] = "tio";
	basecases[11] = "elva";
	basecases[12] = "tolv";
	basecases[13] = "tretton";
	basecases[14] = "fjorton";
	basecases[15] = "femton";
	basecases[16] = "sexton";
	basecases[17] = "sjutton";
	basecases[18] = "arton";
	basecases[19] = "nitton";

	tens[20] = "tjugo";
	tens[30] = "trettio";
	tens[40] = "fyrtio";
	tens[50] = "femtio";
	tens[60] = "sextio";
	tens[70] = "sjuttio";
	tens[80] = "attio";
	tens[90] = "nittio";
}
string get_part(int rem, string magnitude)
{
	if (rem == 0) return "";
	string ret = "";
	int ten_r = rem % 100;
	if (ten_r)
	{
		if (rem == 1)
		{
			if (magnitude == "") ret = "ett";
			if (magnitude == "tusen") ret = "ettusen";
			if (magnitude == "miljoner") ret = "enmiljon";
			if (magnitude == "miljarder") ret = "enmiljard";
		}
		else
		{
			if (ten_r < 20)
			{
				ret += basecases[ten_r];
			}
			else
			{
				ret += tens[ten_r - ten_r % 10] + basecases[ten_r % 10];
			}
			if (sz(ret) >= 3 && sz(magnitude))
			{
				if (ret.substr(sz(ret) - 3) == "ett")
				{
					rep(i, 3)ret.pop_back();
					ret += "en";
				}
			}
			ret += magnitude;
		}
	}
	else ret += magnitude;
	int hundred = rem - rem % 100;
	if (hundred)
	{
		ret = basecases[hundred/100] + "hundra" + ret;
	}

	return ret;
}

string get_word(int i)
{
	vi remainders;
	while (i)
	{
		remainders.push_back(i % 1000);
		i /= 1000;
	}
	string ret = "";

	if (sz(remainders))
	{
		ret += get_part(remainders[0], "");
	}
	if (sz(remainders)>1)
	{
		string s = get_part(remainders[1], "tusen");

		ret = s + ret;
		
	}
	if (sz(remainders)>2)
	{
		string s = get_part(remainders[2], "miljoner");

		ret = s + ret;
		
	}
	if (sz(remainders)>3)
	{
		string s = get_part(remainders[3], "miljarder");

		ret = s + ret;
		
	}

	return ret;
}

int wlen(int max)
{
	int ret = 0;
	repp(i, 1, max + 1) ret += sz(get_word(i));
	return ret;
}

signed main()
{
	fast();

	init();
	assert(get_word(1) == "ett");
	assert(get_word(2) == "tva");
	assert(get_word(3) == "tre");
	assert(get_word(4) == "fyra");
	assert(get_word(5) == "fem");
	assert(get_word(6) == "sex");
	assert(get_word(7) == "sju");
	assert(get_word(8) == "atta");
	assert(get_word(9) == "nio");
	assert(get_word(10) == "tio");
	assert(get_word(11) == "elva");
	assert(get_word(12) == "tolv");
	assert(get_word(13) == "tretton");
	assert(get_word(14) == "fjorton");
	assert(get_word(15) == "femton");
	assert(get_word(16) == "sexton");
	assert(get_word(17) == "sjutton");
	assert(get_word(18) == "arton");
	assert(get_word(19) == "nitton");
	assert(get_word(20) == "tjugo");
	assert(get_word(30) == "trettio");
	assert(get_word(40) == "fyrtio");
	assert(get_word(50) == "femtio");
	assert(get_word(60) == "sextio");
	assert(get_word(70) == "sjuttio");
	assert(get_word(80) == "attio");
	assert(get_word(90) == "nittio");
	assert(get_word(91) == "nittioett");
	assert(get_word(100) == "etthundra");
	assert(get_word(198) == "etthundranittioatta");
	assert(get_word(201) == "tvahundraett");
	assert(get_word(1121) == "ettusenetthundratjugoett");
	assert(get_word(581743) == "femhundraattioentusensjuhundrafyrtiotre");
	assert(get_word(51101001) == "femtioenmiljoneretthundraentusenett");
	assert(get_word(162500020) == "etthundrasextiotvamiljonerfemhundratusentjugo");
	assert(get_word(1002001004) == "enmiljardtvamiljonerettusenfyra");
	assert(get_word(91011091000) == "nittioenmiljarderelvamiljonernittioentusen");

	assert(wlen(999) == 16260);
	assert(wlen(9999) == 235600);
	//assert(wlen(99999) == 2908000);
	//assert(wlen(999999) == 37425000);
	//assert(wlen(9999999) == 472250000);
	//assert(wlen(99999999) == 5319500000);


	int n, k;
	cin >> n >> k;
	k--;
	vector<string> words;
	repp(i, 1, n+1)
	{
		words.push_back(get_word(i));
	}
	sort(all(words));
	string ans = "";
	repe(s, words) ans += s;
	cout << ans[k] << ans[k + 1] << ans[k + 2];

	return 0;
}
