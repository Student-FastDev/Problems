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

void solveTestCase() {
    int N;
    cin >> N;
    vector<int> valuesArray(N);
    vector<int> frequencyArray(N + 2, 0);
    for (int i = 0; i < N; ++i) {
        cin >> valuesArray[i];
        frequencyArray[valuesArray[i]]++;
    }

    int currentMex = 0;
    while (frequencyArray[currentMex] > 0) {
        currentMex++;
    }

    vector<int> resultArray;
    int currentIndex = 0;

    vector<bool> seenFlags(N + 2, false);
    vector<int> seenValues;
    seenValues.reserve(N);

    while (currentIndex < N) {
        int targetMex = currentMex;
        resultArray.push_back(targetMex);

        int foundCount = 0;
        int i = currentIndex;

        for (; i < N; ++i) {
            int currentValue = valuesArray[i];
            frequencyArray[currentValue]--;
            if (frequencyArray[currentValue] == 0) {
                currentMex = min(currentMex, currentValue);
            }

            if (currentValue < targetMex) {
                if (!seenFlags[currentValue]) {
                    seenFlags[currentValue] = true;
                    seenValues.push_back(currentValue);
                    foundCount++;
                }
            }

            if (foundCount == targetMex) {
                i++;
                break;
            }
        }
        currentIndex = i;

        for (int seenValue : seenValues) {
            seenFlags[seenValue] = false;
        }
        seenValues.clear();
    }

    int resultLength = size(resultArray);
    cout << resultLength << endl;
    for (int i = 0; i < resultLength; ++i) {
        cout << resultArray[i] << (i == resultLength - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int testCaseCount;
    cin >> testCaseCount;

    while (testCaseCount--) {
        solveTestCase();
    }
    return 0;
}