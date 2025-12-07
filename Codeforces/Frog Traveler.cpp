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
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int wellDepth;
    if (!(cin >> wellDepth)) return;

    vector<int> maxJump(wellDepth + 1);
    for (int i = 1; i <= wellDepth; ++i) cin >> maxJump[i];

    vector<int> slipDistance(wellDepth + 1);
    for (int i = 1; i <= wellDepth; ++i) cin >> slipDistance[i];

    vector<int> minJumps(wellDepth + 1, -1);
    vector<pii> pathParent(wellDepth + 1);

    set<int> unvisitedLandPoints;
    for (int i = 0; i < wellDepth; ++i) unvisitedLandPoints.insert(i);

    queue<int> bfsQueue;
    minJumps[wellDepth] = 0;
    bfsQueue.push(wellDepth);

    while (!bfsQueue.empty()) {
        int currentStart = bfsQueue.front();
        bfsQueue.pop();

        int maxReach = currentStart - maxJump[currentStart];
        int minReach = currentStart - 1;

        auto it = unvisitedLandPoints.lower_bound(maxReach);

        while (it != unvisitedLandPoints.end()) {
            int landDepth = *it;
            if (landDepth > minReach) break;

            int nextStart = landDepth;
            if (landDepth != 0) {
                nextStart = landDepth + slipDistance[landDepth];
            }

            if (landDepth == 0) {
                if (minJumps[0] == -1) {
                    minJumps[0] = minJumps[currentStart] + 1;
                    pathParent[0] = {currentStart, 0};
                }
                it = unvisitedLandPoints.erase(it);
                goto end_bfs;
            }

            if (minJumps[nextStart] == -1) {
                minJumps[nextStart] = minJumps[currentStart] + 1;
                pathParent[nextStart] = {currentStart, landDepth};
                bfsQueue.push(nextStart);
            }

            it = unvisitedLandPoints.erase(it);
        }
    }

    end_bfs:;

    if (minJumps[0] == -1) {
        cout << -1 << endl;
    } else {
        cout << minJumps[0] << endl;
        vector<int> path;
        int curr = 0;

        while (curr != wellDepth) {
            pii P = pathParent[curr];
            path.push_back(P.second);
            curr = P.first;
        }
        reverse(all(path));
        for (int i = 0; i < size(path); ++i) {
            cout << path[i] << (i == size(path) - 1 ? "" : " ");
        }
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while (T--) {
        solveTestCase();
    }
    return 0;
}