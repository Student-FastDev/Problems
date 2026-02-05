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
#define size(x)  (int)(x).size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7;

struct Segment {
    char type;
    int length;
};

void solveTestCase() {
    int N, M;
    cin >> N >> M;
    string S;
    cin >> S;

    vector<Segment> segmentArray;
    if (M > 0) {
        char currentType = S[0];
        int currentLength = 0;
        for (char c : S) {
            if (c == currentType) {
                currentLength++;
            } else {
                segmentArray.push_back({currentType, currentLength});
                currentType = c;
                currentLength = 1;
            }
        }
        segmentArray.push_back({currentType, currentLength});
    }

    ll maxCoins = 0;
    ll scenariosCount = 1;

    for (int k = N; k >= 1; --k) {
        if (segmentArray.empty()) break;

        vector<Segment> nextSegments;
        nextSegments.reserve(size(segmentArray));

        bool foundAny = false;
        int pairsCount = 0;
        ll waysInStep = 1;

        for (int i = 0; i < size(segmentArray); ++i) {
            if (segmentArray[i].type == 'C' && i + 1 < size(segmentArray) && segmentArray[i+1].type == 'Z') {
                foundAny = true;
                pairsCount++;

                ll lengthC = segmentArray[i].length;
                ll lengthZ = segmentArray[i+1].length;

                waysInStep = (waysInStep * lengthC) % MOD;
                waysInStep = (waysInStep * lengthZ) % MOD;

                int remainingC = segmentArray[i].length - 1;
                int remainingZ = segmentArray[i+1].length - 1;

                if (remainingC > 0) {
                    if (!nextSegments.empty() && nextSegments.back().type == 'C') {
                        nextSegments.back().length += remainingC;
                    } else {
                        nextSegments.push_back({'C', remainingC});
                    }
                }

                if (remainingZ > 0) {
                    if (!nextSegments.empty() && nextSegments.back().type == 'Z') {
                        nextSegments.back().length += remainingZ;
                    } else {
                        nextSegments.push_back({'Z', remainingZ});
                    }
                }
                i++; 
            } else {
                if (!nextSegments.empty() && nextSegments.back().type == segmentArray[i].type) {
                    nextSegments.back().length += segmentArray[i].length;
                } else {
                    nextSegments.push_back(segmentArray[i]);
                }
            }
        }

        if (!foundAny) break;

        maxCoins += (ll)k * pairsCount;
        scenariosCount = (scenariosCount * waysInStep) % MOD;
        segmentArray = move(nextSegments);
    }

    cout << maxCoins << " " << scenariosCount << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }

    return 0;
}