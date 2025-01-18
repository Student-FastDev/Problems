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
        int mod = 0;
        string str;
        cin >> str;
        if (str.back() == '2') {
            cout << str.c_str() << " 2\n";
            continue;
        }
        for (const auto& ch : str) mod = (mod + (ch - '0')) % 3;
        if (mod == 0) {
            cout << str.c_str() << " 3\n";
            continue;
        }
        int pos = -1;
        REP (i, ssize(str))
            if (str[i] - '0' == mod) pos = i;
        if (pos != -1) {
            cout << (str.substr(0, pos) + str.substr(pos + 1, str.size() - pos)).c_str() << " 3\n";
            continue;
        }

        // Only 1
        if (ssize(str) % 2 == 0) {
            cout << str.c_str() << " 11\n";
            continue;
        } else {
            str.pop_back();
            cout << str.c_str() << " 11\n";
        }
    }

    return 0;
}
