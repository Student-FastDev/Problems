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
const int MAX_ROOMS = 100005;
const int LOG_N_VAL = 20;

int nRooms, nQueries;
vector<int> neighbourList[MAX_ROOMS];
ll illusionRates[MAX_ROOMS];
int entryTime[MAX_ROOMS], exitTime[MAX_ROOMS];
int timerCount;
int ancestors[MAX_ROOMS][LOG_N_VAL];
ll fenwickTree[MAX_ROOMS];

void performDFS(int currentRoom, int parentRoom) {
    entryTime[currentRoom] = ++timerCount;
    ancestors[currentRoom][0] = parentRoom;
    for (int i = 1; i < LOG_N_VAL; ++i) {
        ancestors[currentRoom][i] = ancestors[ancestors[currentRoom][i-1]][i-1];
    }
    for (int nextRoom : neighbourList[currentRoom]) {
        if (nextRoom != parentRoom) {
            performDFS(nextRoom, currentRoom);
        }
    }
    exitTime[currentRoom] = timerCount;
}

bool isAncestor(int ancestorRoom, int descendantRoom) {
    return entryTime[ancestorRoom] <= entryTime[descendantRoom] && exitTime[ancestorRoom] >= exitTime[descendantRoom];
}

int getLowestCommonAncestor(int roomU, int roomV) {
    if (isAncestor(roomU, roomV)) return roomU;
    if (isAncestor(roomV, roomU)) return roomV;
    for (int i = LOG_N_VAL - 1; i >= 0; --i) {
        if (!isAncestor(ancestors[roomU][i], roomV)) {
            roomU = ancestors[roomU][i];
        }
    }
    return ancestors[roomU][0];
}

void updateFenwick(int index, ll value) {
    for (; index <= nRooms; index += index & -index)
        fenwickTree[index] += value;
}

void rangeUpdate(int leftRange, int rightRange, ll value) {
    updateFenwick(leftRange, value);
    updateFenwick(rightRange + 1, -value);
}

ll queryFenwick(int index) {
    ll currentSum = 0;
    for (; index > 0; index -= index & -index)
        currentSum += fenwickTree[index];
    return currentSum;
}

void solveTestCase() {
    cin >> nRooms >> nQueries;
    for (int i = 1; i <= nRooms; ++i) {
        cin >> illusionRates[i];
    }
    for (int i = 0; i < nRooms - 1; ++i) {
        int roomU, roomV;
        cin >> roomU >> roomV;
        neighbourList[roomU].push_back(roomV);
        neighbourList[roomV].push_back(roomU);
    }

    timerCount = 0;
    performDFS(1, 1);

    for (int i = 0; i <= nRooms; ++i) fenwickTree[i] = 0;
    
    for (int i = 1; i <= nRooms; ++i) {
        rangeUpdate(entryTime[i], exitTime[i], abs(illusionRates[i]));
    }

    while (nQueries--) {
        int queryType;
        cin >> queryType;
        if (queryType == 1) {
            int roomU;
            ll newRate;
            cin >> roomU >> newRate;
            ll differenceValue = abs(newRate) - abs(illusionRates[roomU]);
            illusionRates[roomU] = newRate;
            rangeUpdate(entryTime[roomU], exitTime[roomU], differenceValue);
        } else {
            int roomU, roomV;
            cin >> roomU >> roomV;
            int lcaRoom = getLowestCommonAncestor(roomU, roomV);
            ll sumToU = queryFenwick(entryTime[roomU]);
            ll sumToV = queryFenwick(entryTime[roomV]);
            ll sumToLca = queryFenwick(entryTime[lcaRoom]);
            
            ll pathSum = sumToU + sumToV - 2 * sumToLca + abs(illusionRates[lcaRoom]);
            ll minimumEnergy = 2 * pathSum - abs(illusionRates[roomU]) - abs(illusionRates[roomV]);
            cout << minimumEnergy << endl;
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