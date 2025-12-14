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

const int MAX_CITIES = 200005;
vector<pair<int, int>> neighbourList[MAX_CITIES];
int finalCosts[MAX_CITIES];
int initialTotalCost = 0;

void dfsCalculateInitialCost(int currentCity, int parentCity) {
    for (auto& edge : neighbourList[currentCity]) {
        int nextCity = edge.first;
        int weight = edge.second;
        if (nextCity != parentCity) {
            initialTotalCost += weight;
            dfsCalculateInitialCost(nextCity, currentCity);
        }
    }
}

void dfsPropagateCosts(int currentCity, int parentCity, int currentCost) {
    finalCosts[currentCity] = currentCost;
    for (auto& edge : neighbourList[currentCity]) {
        int nextCity = edge.first;
        int weightToNext = edge.second;
        if (nextCity != parentCity) {
            int weightFromNext = 1 - weightToNext;
            int nextCost = currentCost - weightToNext + weightFromNext;
            dfsPropagateCosts(nextCity, currentCity, nextCost);
        }
    }
}

void solveTestCase() {
    int numberOfCities;
    cin >> numberOfCities;
    for (int i = 0; i < numberOfCities - 1; ++i) {
        int sourceCity, targetCity;
        cin >> sourceCity >> targetCity;
        neighbourList[sourceCity].push_back({targetCity, 0});
        neighbourList[targetCity].push_back({sourceCity, 1});
    }

    dfsCalculateInitialCost(1, -1);
    dfsPropagateCosts(1, -1, initialTotalCost);

    int minReversals = 2000000000;
    for (int i = 1; i <= numberOfCities; ++i) {
        if (finalCosts[i] < minReversals) {
            minReversals = finalCosts[i];
        }
    }

    cout << minReversals << endl;
    vector<int> optimalCapitals;
    for (int i = 1; i <= numberOfCities; ++i) {
        if (finalCosts[i] == minReversals) {
            optimalCapitals.push_back(i);
        }
    }

    for (int i = 0; i < size(optimalCapitals); ++i) {
        cout << optimalCapitals[i] << (i == size(optimalCapitals) - 1 ? "" : " ");
    }
    cout << endl;

    for (int i = 1; i <= numberOfCities; ++i) {
        neighbourList[i].clear();
    }
    initialTotalCost = 0;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}