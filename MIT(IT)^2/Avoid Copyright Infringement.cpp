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

string makeBlock(char letter, int count) {
    if (count <= 0) return "";
    string s = "";
    s += letter;
    for (int i = 0; i < count - 1; ++i) {
        s += 'I';
        s += letter;
    }
    return s;
}

void solveTestCase() {
    int X, Y, Z;
    cin >> X >> Y >> Z;

    if (X == 0 && Z == 0) {
        if (Y == 1) cout << "YES" << endl << "I" << endl;
        else cout << "NO" << endl;
        return;
    }

    for (int k = 0; k <= X; ++k) {
        if (X > 0 && k == 0) continue;
        if (X == 0 && k > 0) break;

        for (int l = k - 1; l <= k + 1; ++l) {
            if (l < 0) continue;
            if (Z > 0 && l == 0) continue;
            if (Z == 0 && l > 0) break;
            if (l > Z) continue;
            if (k == 0 && l == 0) continue;

            ll neededI = 0;
            if (k > 0) neededI += (ll)X - k;
            if (l > 0) neededI += (ll)Z - l;

            if (Y < neededI) continue;
            
            ll excessI = Y - neededI;
            if (excessI > 2) continue;

            cout << "YES" << endl;

            vector<string> blocksM;
            if (k > 0) {
                for (int i = 0; i < k - 1; ++i) blocksM.push_back("M");
                blocksM.push_back(makeBlock('M', X - (k - 1)));
            }
            
            vector<string> blocksT;
            if (l > 0) {
                for (int i = 0; i < l - 1; ++i) blocksT.push_back("T");
                blocksT.push_back(makeBlock('T', Z - (l - 1)));
            }

            string finalResult = "";
            
            bool startI = (excessI > 0);
            if (startI) {
                finalResult += 'I';
                excessI--;
            }

            bool turnM = false;
            if (X > 0 && Z > 0) {
                if (k > l) turnM = true;
                else if (l > k) turnM = false;
                else turnM = true;
            } else if (X > 0) {
                turnM = true;
            } else {
                turnM = false;
            }

            int M = 0, T = 0;
            while (M < k || T < l) {
                if (turnM) {
                    finalResult += blocksM[M++];
                } else {
                    finalResult += blocksT[T++];
                }
                turnM = !turnM;
            }

            if (excessI > 0) finalResult += 'I';

            cout << finalResult << endl;
            return;
        }
    }

    cout << "NO" << endl;
    return;
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
