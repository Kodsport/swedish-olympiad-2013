#include <bits/stdc++.h>
//#include <bits/extc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define enablell 0

#define ll long long
#if enablell
#define int ll
#endif
#define vi vector<int>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define p2 pair<int, int>
#define p3 tuple<int,int,int>
#define p4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vp3 vector<p3>
#define vp4 vector<p4>
#if enablell
#define inf 1e18
#else
#define inf int(1e9)
#endif

#define read(a) cin >> a
#define read2(a,b) cin >> a >> b
#define write(a) cout << (a) << "\n"
#define quit cout << endl; _Exit(0);
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#ifdef _DEBUG
#define noop cout << "";
#define deb __debugbreak();
#else
#define noop ;
#define deb ;
#endif

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high; i >= 0; i--)
#define perr(i, low, high) for (int i = high; i >= low; i--)

#define readpush(type,vect) type temp; read(temp); vect.(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define insideinterval(v, interval) (v >= interval.first && v <= interval.second)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))
#define first(a) (*begin(a))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))
#define sign(a) ((a>0) ? 1 : -1)

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

template <typename T, typename U>
void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r)
{
    l = { l.first + r.first,l.second + r.second };
}

bool bpm(vvb& graph, int u, vb& seen, vi& matchR, vi& order)
{
    // Try every job one by one
    repe(v, order)
    {
        // If applicant u is interested in
        // job v and v is not visited
        if (graph[u][v] && !seen[v])
        {
            // Mark v as visited
            seen[v] = true;

            // If job 'v' is not assigned to an
            // applicant OR previously assigned
            // applicant for job v (which is matchR[v])
            // has an alternate job available.
            // Since v is marked as visited in
            // the above line, matchR[v] in the following
            // recursive call will not get job 'v' again
            if (matchR[v] < 0 || bpm(graph, matchR[v],
                seen, matchR,order))
            {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}


int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Release\\in.txt");
#endif

    dread2(int, n, m);

    vvi musicians(n);

    vi occurences(m);
    vi occurenceSize(m);

    rep(i, n)
    {
        dread(int, t);
        
        rep(j, t)
        {
            dread(int, measure);
            measure--;
            occurences[measure]++;
            musicians[i].emplace_back(measure);
        }
    }

    rep(i, n)
    {
        rep(j, musicians[i].size())
        {
            occurenceSize[musicians[i][j]] += musicians[i].size();
        }
    }

    vi order(m);
    rep(i, m)
    {
        order[i] = i;
    }

    sort(all(order), [&](const int& lhs, const int& rhs)
        {
            if (occurences[lhs] != occurences[rhs])
            {
                return occurences[lhs] < occurences[rhs];
            }
            else
            {
                return occurenceSize[lhs] > occurenceSize[rhs];
            }
        }); 

    vi musicianOrder(n);
    rep(i, n)
    {
        musicianOrder[i] = i;
    }

    sort(all(musicianOrder), [&](const int& lhs, const int& rhs)
        {
            if (musicians[lhs].size() != musicians[rhs].size())
            {
                return musicians[lhs].size() > musicians[rhs].size();
            }
            else
            {

            }

        });

    double ans = 0;
    int n_played = 1;

    bool changed;
    vvb graph(n, vb(m));

    vb canBeMatched(n, true);
    vb unMatchedMeasure(m, true);

    do
    {
        changed = false;

        repe(g, graph)
        {
            fill(all(g), 0);
        }

        rep(i, musicians.size())
        {
            repe(j, musicians[i])
            {
                if (unMatchedMeasure[j])
                {
                    graph[i][j] = 1;
                }
            }
        }


        vi matchR(m, -1);


        // Count of jobs assigned to applicants
        int matches = 0;
        repe(u, musicianOrder)
        {
            if (!canBeMatched[u])
            {
                continue;
            }
            // Mark all jobs as not seen
            // for next applicant.
            vb seen(m);

            // Find if the applicant 'u' can get a job
            if (bpm(graph, u, seen, matchR, order))
                matches++;
        }

        if (matches > 0)
        {
            changed = true;
        }

        set<int> matched;
        rep(i, matchR.size())
        {
            if (matchR[i] != -1)
            {
                matched.insert(matchR[i]);
                unMatchedMeasure[i] = false;
            }
        }

        rep(i, n)
        {
            if (!setcontains(matched,i))
            {
                canBeMatched[i] = false;
                musicians[i] = vi();
            }
        }

        ans += double(matches) / n_played;
        n_played++;

    } while (changed);

    cout << fixed << setprecision(15) << ans;

    quit;
}
