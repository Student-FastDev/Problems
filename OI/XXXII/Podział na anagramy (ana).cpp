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
const ll MOD = 1e9+7; 

int N;
string S;
vector<int> prefixMasks;

bool canWithD(int D, vector<int> &outPrevious) {
    vector<char> DP(N + 1, 0);
    DP[0] = 1;
    outPrevious.assign(N + 1, -1);

    unordered_map<int, int> reachableMasks;
    reachableMasks.reserve(N * 2);

    int addPointer = 0;
    for (int i = 1; i <= N; ++i) {
        while (addPointer <= i - D) {
            if (DP[addPointer]) {
                int mask = prefixMasks[addPointer];
                if (reachableMasks.find(mask) == reachableMasks.end())
                    reachableMasks[mask] = addPointer;
            }
            ++addPointer;
        }
        bool isOK = false;
        int neededMask = prefixMasks[i];
        auto iterator = reachableMasks.find(neededMask);
        if (iterator != reachableMasks.end()) {
            DP[i] = 1;
            outPrevious[i] = iterator->second;
            isOK = true;
        } else {
            for (int k = 0; k < 26 && !isOK; ++k) {
                int neededMask2 = prefixMasks[i] ^ (1 << k);
                auto secondIterator = reachableMasks.find(neededMask2);
                if (secondIterator != reachableMasks.end()) {
                    DP[i] = 1;
                    outPrevious[i] = secondIterator->second;
                    isOK = true;
                }
            }
        }
    }
    return DP[N];
}

void solveTestCase() {
    cin >> N;
    cin >> S;
    prefixMasks.assign(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        int bit = 1 << (S[i - 1] - 'a');
        prefixMasks[i] = prefixMasks[i - 1] ^ bit;
    }

    int leftRange = 1, rightRange = N, bestLength = 1;
    vector<int> bestPrevious;
    while (leftRange <= rightRange) {
        int middleValue = (leftRange + rightRange) >> 1;
        vector<int> tempPrevious;
        if (canWithD(middleValue, tempPrevious)) {
            bestLength = middleValue;
            bestPrevious = move(tempPrevious);
            leftRange = middleValue + 1;
        } else {
            rightRange = middleValue - 1;
        }
    }

    if (bestPrevious.empty()) {
        canWithD(bestLength, bestPrevious);
    }

    vector<pii> segments;
    int current = N;
    while (current > 0) {
        int previousIndex = bestPrevious[current];
        if (previousIndex < 0) {
            segments.clear();
            segments.emplace_back(1, N);
            break;
        }
        segments.emplace_back(previousIndex + 1, current);
        current = previousIndex;
    }
    reverse(all(segments));

    cout << bestLength << endl;
    cout << size(segments) << endl;
    for (auto &p : segments) {
        cout << p.first << ' ' << p.second << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}