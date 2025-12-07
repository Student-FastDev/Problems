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

const int MAX_DIM = 1005;
int countOfChar[MAX_DIM][MAX_DIM][26];
ll prefBenefit[MAX_DIM][MAX_DIM][26];
string templateGrid[MAX_DIM];

struct SpecialPhoto {
    int r1, c1, r2, c2;
    char c;
    int id;
};

void solveTestCase() {
    int N, M, K;
    if (!(cin >> N >> M >> K)) return;

    for (int i = 0; i < N; ++i) {
        cin >> templateGrid[i];
    }

    vector<SpecialPhoto> photos(K);
    for (int i = 0; i < K; ++i) {
        cin >> photos[i].r1 >> photos[i].c1 >> photos[i].r2 >> photos[i].c2 >> photos[i].c;
        photos[i].id = i;
        
        int charIdx = photos[i].c - 'a';
        countOfChar[photos[i].r1][photos[i].c1][charIdx]++;
        countOfChar[photos[i].r2 + 1][photos[i].c1][charIdx]--;
        countOfChar[photos[i].r1][photos[i].c2 + 1][charIdx]--;
        countOfChar[photos[i].r2 + 1][photos[i].c2 + 1][charIdx]++;
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            for (int charIdx = 0; charIdx < 26; ++charIdx) {
                countOfChar[i][j][charIdx] += countOfChar[i - 1][j][charIdx] 
                                            + countOfChar[i][j - 1][charIdx] 
                                            - countOfChar[i - 1][j - 1][charIdx];
            }
        }
    }

    ll globalSum = 0;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            int currentTemplateChar = templateGrid[i - 1][j - 1] - 'a';
            
            int histogram[26];
            int totalExplicit = 0;
            for (int c = 0; c < 26; ++c) {
                histogram[c] = countOfChar[i][j][c];
                totalExplicit += histogram[c];
            }
            histogram[currentTemplateChar] += (K - totalExplicit);

            ll costs[26];
            ll currentS = 0;
            for (int c = 0; c < 26; ++c) {
                currentS += (ll)histogram[c] * c;
            }
            
            costs[0] = currentS;
            ll countLess = histogram[0];
            
            for (int c = 0; c < 25; ++c) {
                ll change = countLess - (ll)(K - countLess);
                costs[c + 1] = costs[c] + change;
                countLess += histogram[c + 1];
            }

            ll baseCost = costs[currentTemplateChar];
            globalSum += baseCost;

            for (int c = 0; c < 26; ++c) {
                prefBenefit[i][j][c] = costs[c] - baseCost;
            }
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            for (int c = 0; c < 26; ++c) {
                prefBenefit[i][j][c] += prefBenefit[i - 1][j][c] 
                                      + prefBenefit[i][j - 1][c] 
                                      - prefBenefit[i - 1][j - 1][c];
            }
        }
    }

    ll minTotalDistance = INF;

    for (int i = 0; i < K; ++i) {
        int r1 = photos[i].r1;
        int c1 = photos[i].c1;
        int r2 = photos[i].r2;
        int c2 = photos[i].c2;
        int charIdx = photos[i].c - 'a';

        ll rectangleSum = prefBenefit[r2][c2][charIdx] 
                        - prefBenefit[r1 - 1][c2][charIdx] 
                        - prefBenefit[r2][c1 - 1][charIdx] 
                        + prefBenefit[r1 - 1][c1 - 1][charIdx];
        
        ll currentTotalDistance = globalSum + rectangleSum;
        if (currentTotalDistance < minTotalDistance) {
            minTotalDistance = currentTotalDistance;
        }
    }

    cout << minTotalDistance << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}