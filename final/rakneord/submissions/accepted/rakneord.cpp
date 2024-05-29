#include <bits/stdc++.h>

using namespace std;

string getUnder100(int a, bool prefix){
    switch(a){
	case 0: return "";
	case 1: if(prefix)return "en"; return "ett";
	case 2: return "tva";
	case 3: return "tre";
	case 4: return "fyra";
	case 5: return "fem";
	case 6: return "sex";
	case 7: return "sju";
	case 8: return "atta";
	case 9: return "nio";
	case 10: return "tio";
	case 11: return "elva";
	case 12: return "tolv";
	case 13: return "tretton";
	case 14: return "fjorton";
	case 15: return "femton";
	case 16: return "sexton";
	case 17: return "sjutton";
	case 18: return "arton";
	case 19: return "nitton";
	default: {
				switch(a/10){
				case 2: return "tjugo"+getUnder100(a%10, prefix);
				case 3: return "trettio"+getUnder100(a%10, prefix);
				case 4: return "fyrtio"+getUnder100(a%10, prefix);
				case 5: return "femtio"+getUnder100(a%10, prefix);
				case 6: return "sextio"+getUnder100(a%10, prefix);
				case 7: return "sjuttio"+getUnder100(a%10, prefix);
				case 8: return "attio"+getUnder100(a%10, prefix);
				case 9: return "nittio"+getUnder100(a%10, prefix);
				default: return "ERRORGIVINGTOLARGENUMBERINgetUnder100";
				}
			 }
	}
}

string getUnder1000(int a, bool prefix){
	if(a < 100)
		return getUnder100(a, prefix);
	return getUnder100(a/100, 0) + "hundra" + getUnder100(a%100, prefix);
}

string get(long long a){
	string ret="";
	long long tusen=1000, miljon=1000000, miljard=1000000000;
	ret += getUnder1000(a/miljard, 1);
	if(a/miljard == 1)
		ret += "miljard";
	else if(a/miljard >= 2)
		ret += "miljarder";
	long long m=(a%miljard)/miljon;
	ret += getUnder1000(m, 1);
	if(m == 1)
		ret += "miljon";
	else if(m >= 2)
		ret += "miljoner";
	m=(a%miljon)/tusen;
	if(m == 1)
		ret += "ettusen";
	else if(m > 1)
		ret += getUnder1000(m, 1) + "tusen";
	m=a%tusen;
	ret += getUnder1000(m, 0);
	return ret;
}

int getLength(long long a){

	return get(a).length();
}

long long tusenLength=16260, miljonLength=37425000, miljardLength=61585000000LL;
long long N, K;
vector<pair<pair<string, int>, long long> > family;

long long Min(long long a, long long b){
	return a < b ? a : b;
}

long long Max(long long a, long long b){
	return a > b ? a : b;
}

long long Floor(long long a, int digits){
	long long b=1;
	for(int i=0; i < digits; ++i)
		b *= 10;
	return (a/b)*b;
}

long long getFamilySize(pair<pair<string, int>, int> p){
	switch(p.first.second){
	case 0: return (p.first.first).length();
	case 3: return 1000LL*(p.first.first).length()+tusenLength;
	case 6: return 1000000LL*(p.first.first).length()+miljonLength;
	case 9: return 1000000000LL*(p.first.first).length()+miljardLength;
	default: return 0;
	}
}

long long power10(int a){
	long long i=1;
	for(int j=0; j < a; ++j)
		i *= 10LL;
	return i;
}

char getChar(long long n, long long k, pair<string, int> p){
	long long tusen=1000, miljon=1000000, miljard=1000000000;
	long long slen = p.first.length();
	family.clear();
	if(n >= miljard){
		for(long long i=miljon; i < miljard; i += miljon)
			family.push_back(make_pair(make_pair(p.first+get(i), 6), i));
	}
	if(n >= miljon){
		for(long long i=tusen; i < miljon; i += tusen)
			family.push_back(make_pair(make_pair(p.first+get(i), 3), i));
	}
	if(n >= tusen){
		for(long long i=0; i < tusen; i += 1)
			family.push_back(make_pair(make_pair(p.first+get(i), 0), i));
	}
	for(long long i=miljard; i < Floor(n, 9); i += miljard)
		family.push_back(make_pair(make_pair(p.first+get(i), 9), i));
	for(long long i=Max(Floor(n, 9), miljon); i < Floor(n, 6); i += miljon)
		family.push_back(make_pair(make_pair(p.first+get(i), 6), i));
	for(long long i=Max(Floor(n, 6), tusen); i < Floor(n, 3); i += tusen)
		family.push_back(make_pair(make_pair(p.first+get(i), 3), i));
	for(long long i=Floor(n, 3); i <= n; i += 1)
		family.push_back(make_pair(make_pair(p.first+get(i), 0), i));
	sort(family.begin(), family.end());
	long long ksaved;
	bool top=0;
	for(int i=0; true; ++i){
		long long l=getFamilySize(family[i]);
		if(Floor(n, p.second) <= family[i].second){
			if(!top){
				ksaved=k;
			}
			top=true;
		}
		else
			top=false;
		if(k < l){
			if(top)
				return getChar(n-Floor(n, p.second), ksaved, make_pair(p.first+get(Floor(n, p.second)), p.second-3));
			if(!family[i].first.second)
				return family[i].first.first[k];
			return getChar(power10(family[i].first.second)-1, k, make_pair(family[i].first.first, family[i].first.second));
		}
		else
			k -= l;
	}
}

int main()
{
	scanf("%lld%lld", &N, &K);
	for(long long i=K-1; i <= K+1; ++i){
		printf("%c", getChar(N, i, make_pair("", 9)));
	}	
	return 0;
}

