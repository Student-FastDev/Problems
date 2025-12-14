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
const ll MAX_N = 2005;
const ll MOD = 1e9+7; // 998244353

const int MAX_K = 2005;
const int MAX_Q_ASK = 2005;

struct GarlandPoint {
    int row, col;
    ll weight;
};

struct QuerySegment {
    int y1, y2, id, type;
};

struct SimulationEvent {
    int type;
    int param;
};

ll interactionValues[MAX_K][MAX_Q_ASK];
vector<GarlandPoint> garlandList[MAX_K];
vector<QuerySegment> querySegmentsArray[MAX_N];
vector<SimulationEvent> eventList;
int garlandActiveStatus[MAX_K];
ll binaryIndexedTree[MAX_N];
int N, M, K;

void updateBit(int indexNumber, ll valueToAdd) {
    for (; indexNumber <= M; indexNumber += indexNumber & -indexNumber)
        binaryIndexedTree[indexNumber] += valueToAdd;
}

ll queryBit(int indexNumber) {
    ll totalSum = 0;
    for (; indexNumber > 0; indexNumber -= indexNumber & -indexNumber)
        totalSum += binaryIndexedTree[indexNumber];
    return totalSum;
}

void solveTestCase() {
    cin >> N >> M >> K;

    for (int i = 1; i <= K; ++i) {
        int numberOfPoints;
        cin >> numberOfPoints;
        garlandList[i].resize(numberOfPoints);
        for (int j = 0; j < numberOfPoints; ++j) {
            cin >> garlandList[i][j].row >> garlandList[i][j].col >> garlandList[i][j].weight;
        }
        sort(all(garlandList[i]), [](const GarlandPoint& a, const GarlandPoint& b) {
            return a.row < b.row;
        });
        garlandActiveStatus[i] = 1;
    }

    int Q;
    cin >> Q;
    int queryIndex = 0;
    for (int i = 0; i < Q; ++i) {
        string commandString;
        cin >> commandString;
        if (commandString == "SWITCH") {
            int garlandIndex;
            cin >> garlandIndex;
            eventList.push_back({0, garlandIndex});
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            querySegmentsArray[x1 - 1].push_back({y1, y2, queryIndex, -1});
            querySegmentsArray[x2].push_back({y1, y2, queryIndex, 1});
            eventList.push_back({1, queryIndex});
            queryIndex++;
        }
    }

    for (int i = 1; i <= K; ++i) {
        memset(binaryIndexedTree, 0, sizeof(ll) * (M + 1));

        int pointIndex = 0;
        int currentGarlandLength = (int)size(garlandList[i]);

        for (int currentRow = 0; currentRow <= N; ++currentRow) {
            while(pointIndex < currentGarlandLength && garlandList[i][pointIndex].row == currentRow) {
                updateBit(garlandList[i][pointIndex].col, garlandList[i][pointIndex].weight);
                pointIndex++;
            }

            for (const auto& segment : querySegmentsArray[currentRow]) {
                ll currentValue = queryBit(segment.y2) - queryBit(segment.y1 - 1);
                if (segment.type == 1) interactionValues[i][segment.id] += currentValue;
                else interactionValues[i][segment.id] -= currentValue;
            }
        }
    }

    for (const auto& event : eventList) {
        if (event.type == 0) {
            garlandActiveStatus[event.param] ^= 1;
        } else {
            ll finalAnswer = 0;
            for (int i = 1; i <= K; ++i) {
                if (garlandActiveStatus[i]) {
                    finalAnswer += interactionValues[i][event.param];
                }
            }
            cout << finalAnswer << endl;
        }
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