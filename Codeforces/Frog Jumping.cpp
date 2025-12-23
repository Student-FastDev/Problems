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
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; // 998244353

void solveTestCase() {
    ll M, A, B;
    cin >> M >> A >> B;

    ll gcdValue = std::gcd(A, B);
    ll scaledA = A / gcdValue;
    ll scaledB = B / gcdValue;
    ll scaledM = M / gcdValue;

    ll threshold = 2 * (scaledA + scaledB);
    ll maxK = min(scaledM, threshold + 2000);

    vector<bool> isReachable(maxK + 1, false);
    vector<ll> countArray(maxK + 1, 0);
    queue<int> bfsQueue;

    int currentCount = 0;

    for (int k = 0; k <= maxK; ++k) {
        if (k == 0) {
            if (!isReachable[0]) {
                isReachable[0] = true;
                currentCount++;
                bfsQueue.push(0);
            }
        } else {
            if (k >= scaledA && isReachable[k - scaledA]) {
                if (!isReachable[k]) {
                    isReachable[k] = true;
                    currentCount++;
                    bfsQueue.push(k);
                }
            }
        }

        while (!bfsQueue.empty()) {
            int u = bfsQueue.front();
            bfsQueue.pop();

            ll v1 = u - scaledB;
            if (v1 >= 0) {
                if (!isReachable[v1]) {
                    isReachable[v1] = true;
                    currentCount++;
                    bfsQueue.push((int)v1);
                }
            }

            ll v2 = u + scaledA;
            if (v2 <= k) {
                if (!isReachable[v2]) {
                    isReachable[v2] = true;
                    currentCount++;
                    bfsQueue.push((int)v2);
                }
            }
        }
        countArray[k] = currentCount;
    }

    ll totalSum = 0;
    ll loopLimit = min(scaledM, maxK);

    for (ll k = 0; k <= loopLimit; ++k) {
        ll weight = gcdValue;
        if (k == scaledM) {
            weight = (M % gcdValue) + 1;
        }
        totalSum += weight * countArray[k];
    }

    if (scaledM > maxK) {
        ll startK = maxK + 1;
        ll endK = scaledM - 1;

        if (startK <= endK) {
            ll countRange = endK - startK + 1;
            ll sumK = (startK + endK) * countRange / 2;
            ll sumVal = sumK + countRange;
            totalSum += sumVal * gcdValue;
        }

        ll lastVal = scaledM + 1;
        ll lastWeight = (M % gcdValue) + 1;
        totalSum += lastVal * lastWeight;
    }

    cout << totalSum << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}