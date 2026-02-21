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
    int N;
    cin >> N;
    
    vector<int> A(N + 1), B(N + 1);
    vector<int> countArray(N + 1, 0);
    
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        countArray[A[i]]++;
    }
    for (int i = 1; i <= N; ++i) {
        cin >> B[i];
        countArray[B[i]]++;
    }

    for (int i = 1; i <= N; ++i) {
        if (countArray[i] % 2 != 0) {
            cout << -1 << endl;
            return;
        }
    }

    vector<vector<pii>> neighbourList(N + 1);
    for (int i = 1; i <= N; ++i) {
        neighbourList[A[i]].push_back({B[i], i});
        neighbourList[B[i]].push_back({A[i], i});
    }

    vector<int> pointerArray(N + 1, 0);
    vector<bool> usedArray(N + 1, false);
    vector<bool> swapEdges(N + 1, false);

    for (int i = 1; i <= N; ++i) {
        while (pointerArray[i] < size(neighbourList[i])) {
            int currentElement = i;
            while (true) {
                int nextNode = -1;
                while (pointerArray[currentElement] < size(neighbourList[currentElement])) {
                    auto [v, number] = neighbourList[currentElement][pointerArray[currentElement]++];
                    if (!usedArray[number]) {
                        usedArray[number] = true;
                        swapEdges[number] = (currentElement == A[number]);
                        nextNode = v;
                        break;
                    }
                }
                if (nextNode == -1) break;
                currentElement = nextNode;
            }
        }
    }

    vector<int> finalAnswer;
    for (int i = 1; i <= N; ++i) {
        if (swapEdges[i]) finalAnswer.push_back(i);
    }

    cout << size(finalAnswer) << endl;
    for (int i = 0; i < size(finalAnswer); ++i) {
        cout << finalAnswer[i] << (i + 1 == size(finalAnswer) ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
