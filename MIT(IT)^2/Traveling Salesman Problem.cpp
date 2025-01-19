// clang-format off
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
#define FOR(i,l,r)for(auto i=(l);i<=(r);++i)
#define REP(i,n)FOR(i,0,(n)-1)
#define ssize(x)int(x.size())
template<class A,class B>auto&operator<<(ostream&o,pair<A,B>p){return o<<"("<<p.first<<", "<<p.second<<")";}
template<class T>auto operator<<(ostream&o,T x)->decltype(x.end(),o){o<<"{";int i=0;for(auto e:x)o<<(", ")+2*!i++<<e;return o<<"}";}
#ifdef DEBUG
#define debug(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<"\n";}(X)
#else
#define debug(...){}
#endif
// clang-format on

int
main()
{
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<LL> seq(N);
        for (auto& a : seq) {
            LL x, y;
            cin >> x >> y;
            a = x + y;
        }
        sort(seq.begin(), seq.end());

        LL score = 0;
        REP (i, N - 1) score += seq[i + 1] - seq[i];
        cout << score * 2 << "\n";
    }
    return 0;
}
