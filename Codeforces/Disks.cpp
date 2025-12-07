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

struct Disk {
    long long x, y, r;
    int id;
};

long long distance(const Disk& a, const Disk& b) {
    long long dX = a.x - b.x;
    long long dY = a.y - b.y;
    return dX * dX + dY * dY;
}

void solveTestCase() {
    int N;
    cin >> N;

    vector<Disk> disksArray(N);
    for (int i = 0; i < N; ++i) {
        cin >> disksArray[i].x >> disksArray[i].y >> disksArray[i].r;
        disksArray[i].id = i;
    }

    vector<vector<int>> neighbourList(N);
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            long long currentDistance = distance(disksArray[i], disksArray[j]);
            long long radiusSum = disksArray[i].r + disksArray[j].r;
            if (currentDistance == radiusSum * radiusSum) {
                neighbourList[i].push_back(j);
                neighbourList[j].push_back(i);
            }
        }
    }

    vector<int> colorArray(N, -1);
    bool possible = false;

    for (int i = 0; i < N; ++i) {
        if (colorArray[i] != -1) continue;

        bool isOkay = true;
        int countA = 0;
        int countB = 0;

        vector<int> queueArray;
        queueArray.push_back(i);
        colorArray[i] = 0;
        countA++;

        int currentHead = 0;
        while(currentHead < (int)size(queueArray)){
            int u = queueArray[currentHead++];

            for (int v : neighbourList[u]) {
                if (colorArray[v] == -1) {
                    colorArray[v] = 1 - colorArray[u];
                    if (colorArray[v] == 0) countA++;
                    else countB++;
                    queueArray.push_back(v);
                } else {
                    if (colorArray[v] == colorArray[u]) isOkay = false;
                }
            }
        }

        if (isOkay && countA != countB) {
            possible = true;
            break;
        }
    }

    if (possible) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
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
