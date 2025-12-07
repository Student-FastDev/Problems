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
    int numberOfObjects;
    cin >> numberOfObjects;

    int requiredDeactivated;
    double epsilonPerMils;
    cin >> requiredDeactivated >> epsilonPerMils;

    ll targetX, targetY;
    cin >> targetX >> targetY;

    vector<double> squaredDistances(numberOfObjects);
    for(int i = 0; i < numberOfObjects; ++i) {
        ll objectX, objectY;
        cin >> objectX >> objectY;
        ll diffX = objectX - targetX;
        ll diffY = objectY - targetY;
        squaredDistances[i] = (double)(diffX * diffX + diffY * diffY);
    }

    double maxFailureProbability = epsilonPerMils / 1000.0;

    double leftRange = 0.0;
    double rightRange = 400000.0; 

    for(int iteration = 0; iteration < 100; ++iteration) {
        double middleValue = leftRange + (rightRange - leftRange) / 2.0;
        bool isPossible = false;
        
        if (middleValue < 1e-9) {
            int sureHits = 0;
            for(double squaredDist : squaredDistances) {
                if (squaredDist < 1e-9) sureHits++;
            }
            if (sureHits >= requiredDeactivated) isPossible = true;
            else isPossible = (1.0 <= maxFailureProbability);
        } else {
            vector<double> probabilities;
            probabilities.reserve(numberOfObjects);
            double radiusSquared = middleValue * middleValue;
            
            for(double squaredDist : squaredDistances) {
                if (squaredDist <= radiusSquared) {
                    probabilities.push_back(1.0);
                } else {
                    probabilities.push_back(exp(1.0 - squaredDist / radiusSquared));
                }
            }

            vector<double> dpTable(numberOfObjects + 1, 0.0);
            dpTable[0] = 1.0;

            for(double probability : probabilities) {
                for(int j = numberOfObjects; j >= 1; --j) {
                    dpTable[j] = dpTable[j] * (1.0 - probability) + dpTable[j-1] * probability;
                }
                dpTable[0] = dpTable[0] * (1.0 - probability);
            }

            double failureProbability = 0.0;
            for(int j = 0; j < requiredDeactivated; ++j) {
                failureProbability += dpTable[j];
            }
            
            isPossible = (failureProbability <= maxFailureProbability);
        }

        if(isPossible) {
            rightRange = middleValue;
        } else {
            leftRange = middleValue;
        }
    }

    cout << fixed << setprecision(10) << rightRange << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}