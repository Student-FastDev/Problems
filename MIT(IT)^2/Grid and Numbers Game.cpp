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

#define ENCODE(r, c) ((r) * M + (c))
#define DECODE(v) make_pair((v) / M, (v) % M)

bool
solve()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> board(N, vector<int>(M));
    set<pair<int, int>> active;
    REP (r, N) {
        REP (c, M) {
            cin >> board[r][c];
            active.insert({board[r][c], ENCODE(r, c)});
        }
    }
    int player = 0;  // 0 = starting
    while (!active.empty()) {
        auto [val, v] = *active.begin();
        active.erase(active.begin());
        auto [r, c] = DECODE(v);

        int to      = -1;
        if (r > 0 && board[r - 1][c] < val) to = max(to, board[r - 1][c]);
        if (c > 0 && board[r][c - 1] < val) to = max(to, board[r][c - 1]);
        if (r < N - 1 && board[r + 1][c] < val) to = max(to, board[r + 1][c]);
        if (c < M - 1 && board[r][c + 1] < val) to = max(to, board[r][c + 1]);
        to += 1;

        if (to >= val) continue;

        player = (player + (val - to)) % 2;
        board[r][c] = to;
    }
    
    if (player == 0) return false;
    return true;
}

int
main()
{
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) cout << (solve() ? "YES\n" : "NO\n");
    return 0;
}
