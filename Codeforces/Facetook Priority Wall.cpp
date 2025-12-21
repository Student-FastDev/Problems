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

void solveTestCase() {
    string myName;
    cin >> myName;

    int N;
    cin >> N;

    map<string, int> priorityScoreMap;
    set<string> distinctNameSet;

    for (int i = 0; i < N; ++i) {
        string firstPerson, actionType;
        cin >> firstPerson >> actionType;

        string secondPersonRaw, dummyString;
        int currentScore = 0;

        if (actionType == "posted") {
            cin >> dummyString;
            cin >> secondPersonRaw;
            cin >> dummyString;
            currentScore = 15;
        } else if (actionType == "commented") {
            cin >> dummyString;
            cin >> secondPersonRaw;
            cin >> dummyString;
            currentScore = 10;
        } else {
            cin >> secondPersonRaw;
            cin >> dummyString;
            currentScore = 5;
        }

        string secondPerson = secondPersonRaw.substr(0, size(secondPersonRaw) - 2);

        distinctNameSet.insert(firstPerson);
        distinctNameSet.insert(secondPerson);

        if (firstPerson == myName) {
            priorityScoreMap[secondPerson] += currentScore;
        }
        if (secondPerson == myName) {
            priorityScoreMap[firstPerson] += currentScore;
        }
    }

    vector<pair<int, string>> resultList;
    for (const string& personName : distinctNameSet) {
        if (personName == myName) continue;
        resultList.push_back({priorityScoreMap[personName], personName});
    }

    sort(all(resultList), [](const pair<int, string>& a, const pair<int, string>& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });

    for (const auto& entry : resultList) {
        cout << entry.second << endl;
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