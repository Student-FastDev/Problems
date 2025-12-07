// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto P)->decltype(P.first,o){return o<<'('<<P.first<<", "<<P.second <<')';}
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

const ll firstMOD = 1e9+7;
const ll secondMOD = 998244353;
const ll MAX_M = 1000005;

ll firstHash[MAX_M];
ll secondHash[MAX_M];

vector<int> neighbourList[MAX_M];
vector<ll> firstPowers, secondPowers;

struct User {
    int id;
    int k;
    vector<int> activitiesArray;
};

void solveTestCase() {
    int N, M;
    cin >> N >> M;

    vector<User> usersArray(N);
    for (int i = 0; i < N; i++) {
        usersArray[i].id = i + 1;
        cin >> usersArray[i].k;
        usersArray[i].activitiesArray.resize(usersArray[i].k);
        for (int j = 0; j < usersArray[i].k; j++) {
            cin >> usersArray[i].activitiesArray[j];
        }
    }

    vector<int> P(N);
    iota(all(P), 0);
    sort(all(P), [&](int a, int b) {
        return usersArray[a].k > usersArray[b].k;
    });

    ll firstBase = 333 + rng() % 5000;
    ll secondBase = 555 + rng() % 5000;

    firstPowers.resize(N + 1);
    secondPowers.resize(N + 1);
    firstPowers[0] = 1;
    secondPowers[0] = 1;
    for (int i = 1; i <= N; i++) {
        firstPowers[i] = (firstPowers[i-1] * firstBase) % firstMOD;
        secondPowers[i] = (secondPowers[i-1] * secondBase) % secondMOD;
    }

    for (int i = 0; i < N; i++) {
        int currentIndex = P[i];
        vector<int>& activitiesArray = usersArray[currentIndex].activitiesArray;

        if (activitiesArray.empty()) continue;

        ll currentFirst = firstHash[activitiesArray[0]];
        ll currentSecond = secondHash[activitiesArray[0]];
        int actionDifference = -1;

        for (int j = 1; j < size(activitiesArray); j++) {
            if (firstHash[activitiesArray[j]] != currentFirst || secondHash[activitiesArray[j]] != currentSecond) {
                actionDifference = activitiesArray[j];
                break;
            }
        }

        if (actionDifference != -1) {
            int actionA = activitiesArray[0];
            int actionB = actionDifference;
            
            vector<int>& listA = neighbourList[actionA];
            vector<int>& listB = neighbourList[actionB];
            
            int checkStep = -1;
            int l = 0, m = 0;
            
            while (l < size(listA) && m < size(listB)) {
                if (listA[l] == listB[m]) {
                    l++; m++;
                } else if (listA[l] < listB[m]) {
                    checkStep = listA[l];
                    break;
                } else {
                    checkStep = listB[m];
                    break;
                }
            }
            if (checkStep == -1) {
                if (l < size(listA)) checkStep = listA[l];
                else if (m < size(listB)) checkStep = listB[m];
            }
            
            cout << "YES" << endl;
            cout << usersArray[currentIndex].id << " " << usersArray[P[checkStep]].id << endl;
            return;
        }

        ll firstAdd = firstPowers[i];
        ll secondAdd = secondPowers[i];

        for (int x : activitiesArray) {
            firstHash[x] = (firstHash[x] + firstAdd) % firstMOD;
            secondHash[x] = (secondHash[x] + secondAdd) % secondMOD;
            neighbourList[x].push_back(i);
        }
    }

    cout << "NO" << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}
