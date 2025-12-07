// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  (int)x.size()

const ll INF = 9223372036854775806;

struct Item {
    char type;
    int origIdx;
};

void solveTestCase() {
    string S;
    if (!(cin >> S)) return;
    int N = size(S);

    vector<Item> items;
    items.reserve(N);
    for(int i=0; i<N; ++i) {
        if(S[i] != 'X') {
            items.push_back({S[i], i});
        }
    }

    if(items.empty()) {
        cout << fixed << setprecision(6) << 0.0 << endl;
        return;
    }

    int K = size(items);
    vector<int> delta(K);
    ll sBase = 0;

    for(int i=0; i<K; ++i) {
        int nextI = (i + 1) % K;
        int d;
        if (i < K - 1) {
            d = items[nextI].origIdx - items[i].origIdx;
        } else {
            d = N - items[i].origIdx + items[0].origIdx;
        }
        
        if(d == 1 && items[i].type == items[nextI].type) {
            d = 2;
        }
        delta[i] = d;
        sBase += d;
    }

    // Best Odd Density
    ll L_odd;
    if (sBase % 2 != 0) L_odd = sBase;
    else L_odd = sBase + 1;
    double ans = (double)K / (2.0 * L_odd);

    // Prepare for BS
    // q[i] is the baseline parity of item i relative to item 0, determined by minimal gaps delta
    vector<int> q(K);
    q[0] = 0;
    for(int i=0; i<K-1; ++i) {
        q[i+1] = (q[i] + delta[i]) % 2;
    }

    auto check = [&](double lambda, int pattern) -> bool {
        auto getScore = [&](int idx, int s) -> double {
            int p = q[idx] ^ s;
            int targetL = pattern; 
            int targetR = 1 - pattern;
            if (items[idx].type == 'L') return (p == targetL ? 1.0 : 0.0);
            else return (p == targetR ? 1.0 : 0.0);
        };

        double bestVal = -1e18;

        for(int startS = 0; startS < 2; ++startS) {
            double dp[2];
            dp[startS] = getScore(0, startS);
            dp[1 - startS] = -1e18;

            for(int i = 0; i < K - 1; ++i) {
                double ndp[2];
                double score0 = getScore(i+1, 0);
                double score1 = getScore(i+1, 1);
                
                // From 0 to 0: cost 0
                // From 1 to 0: cost lambda
                if (dp[0] > -1e17 || dp[1] > -1e17) {
                    ndp[0] = score0 + max(dp[0], dp[1] - lambda);
                    // From 0 to 1: cost lambda
                    // From 1 to 1: cost 0
                    ndp[1] = score1 + max(dp[0] - lambda, dp[1]);
                } else {
                    ndp[0] = -1e18;
                    ndp[1] = -1e18;
                }
                
                dp[0] = ndp[0];
                dp[1] = ndp[1];
            }

            int targetEnd = startS ^ (sBase & 1);
            
            double val = -1e18;
            if (dp[0] > -1e17 || dp[1] > -1e17) {
                if(targetEnd == 0) {
                     val = max(dp[0], dp[1] - lambda);
                } else {
                     val = max(dp[0] - lambda, dp[1]);
                }
            }
            bestVal = max(bestVal, val);
        }

        return bestVal >= lambda * sBase;
    };

    double low = 0, high = 1.0;
    for(int iter=0; iter<50; ++iter) {
        double mid = (low + high) / 2;
        if(check(mid, 0)) low = mid;
        else high = mid;
    }
    ans = max(ans, low);

    low = 0, high = 1.0;
    for(int iter=0; iter<50; ++iter) {
        double mid = (low + high) / 2;
        if(check(mid, 1)) low = mid;
        else high = mid;
    }
    ans = max(ans, low);

    cout << fixed << setprecision(6) << floor((ans + 1e-9) * 1000000.0) / 1000000.0 << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    solveTestCase();
    return 0;
}