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

int askType2(int l, int r) {
    if (l > r) return 0;
    cout << "? 2 " << l << " " << r << endl;
    int ans;
    cin >> ans;
    if (ans == 0) exit(0); 
    return ans;
}

char askType1(int i) {
    cout << "? 1 " << i << endl;
    char c;
    cin >> c;
    return c;
}

void solveTestCase() {
    int N;
    if (!(cin >> N)) return;

    vector<char> finalString(N + 1);
    vector<int> lastPosition(26, 0);

    char firstChar = askType1(1);
    finalString[1] = firstChar;
    lastPosition[firstChar - 'a'] = 1;

    for (int i = 2; i <= N; ++i) {
        vector<pair<int, int>> sortedCharacters; 
        for (int c = 0; c < 26; ++c) {
            if (lastPosition[c] > 0) {
                sortedCharacters.push_back({lastPosition[c], c});
            }
        }
        sort(all(sortedCharacters), greater<pair<int, int>>());

        int low = 0, high = size(sortedCharacters) - 1;
        int foundIndex = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int pos = sortedCharacters[mid].first;
            
            int distinctCount = askType2(pos, i);
            
            if (distinctCount == mid + 1) {
                foundIndex = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        if (foundIndex != -1) {
            int charIdx = sortedCharacters[foundIndex].second;
            finalString[i] = (char)('a' + charIdx);
            lastPosition[charIdx] = i;
        } else {
            char newChar = askType1(i);
            finalString[i] = newChar;
            lastPosition[newChar - 'a'] = i;
        }
    }

    cout << "! ";
    for (int i = 1; i <= N; ++i) {
        cout << finalString[i];
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    while(T--) {
        solveTestCase();
    }
    return 0;
}