// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define size(x) (x).size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9 + 1;
const ll MOD = 1e9 + 7;

void solveTestCase() {
    int numberOfPoints;
    ll optimalLength;
    if (!(cin >> numberOfPoints >> optimalLength)) return;

    vector<ll> coordinates(numberOfPoints + 1);
    vector<ll> picturesquenessValues(numberOfPoints + 1);

    coordinates[0] = 0;
    picturesquenessValues[0] = 0;

    for (int i = 1; i <= numberOfPoints; ++i) {
        cin >> coordinates[i] >> picturesquenessValues[i];
    }

    vector<int> currentParent(numberOfPoints + 1);
    vector<long double> minCost(numberOfPoints + 1);
    vector<int> bestParent(numberOfPoints + 1);

    auto checkFeasibility = [&](long double lambda) -> bool {
        minCost[0] = 0;
        for (int i = 1; i <= numberOfPoints; ++i) {
            minCost[i] = 1e18;
        }

        for (int i = 1; i <= numberOfPoints; ++i) {
            for (int j = 0; j < i; ++j) {
                long double frustration = sqrtl(abs(coordinates[i] - coordinates[j] - optimalLength));
                long double value = minCost[j] + frustration - lambda * picturesquenessValues[i];
                if (value < minCost[i]) {
                    minCost[i] = value;
                    currentParent[i] = j;
                }
            }
        }
        return minCost[numberOfPoints] <= 0;
    };

    long double lowRange = 0.0, highRange = 1e7;
    for (int iter = 0; iter < 60; ++iter) {
        long double midValue = (lowRange + highRange) / 2.0;
        if (checkFeasibility(midValue)) {
            bestParent = currentParent;
            highRange = midValue;
        } else {
            lowRange = midValue;
        }
    }

    vector<int> path;
    int currentNode = numberOfPoints;
    while (currentNode > 0) {
        path.push_back(currentNode);
        currentNode = bestParent[currentNode];
    }
    reverse(all(path));

    for (int i = 0; i < size(path); ++i) {
        cout << path[i] << (i == size(path) - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    while (T--) {
        solveTestCase();
    }
    return 0;
}