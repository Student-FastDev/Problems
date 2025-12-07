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

struct Bug {
    int complexity;
    int id;
};

struct Student {
    int ability;
    int cost;
    int id;
};

int studentCount, bugCount;
ll passLimit;
vector<Bug> bugList;
vector<Student> studentList;

bool check(int days, ll& finalCost, vector<int>& assignments) {
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    int studentPtr = 0;
    finalCost = 0;
    assignments.assign(bugCount + 1, 0);
    
    for (int i = 0; i < bugCount; i += days) {
        int requirement = bugList[i].complexity;
        
        while (studentPtr < studentCount && studentList[studentPtr].ability >= requirement) {
            pq.push({studentList[studentPtr].cost, studentList[studentPtr].id});
            studentPtr++;
        }
        
        if (pq.empty()) return false;
        
        pii bestStudent = pq.top();
        pq.pop();
        
        finalCost += bestStudent.first;
        if (finalCost > passLimit) return false;
        
        int studentId = bestStudent.second;
        
        for (int j = i; j < min(i + days, bugCount); ++j) {
            assignments[bugList[j].id] = studentId;
        }
    }
    
    return true;
}

void solveTestCase() {
    cin >> studentCount >> bugCount >> passLimit;

    bugList.resize(bugCount);
    for (int i = 0; i < bugCount; ++i) {
        cin >> bugList[i].complexity;
        bugList[i].id = i + 1;
    }

    studentList.resize(studentCount);
    for (int i = 0; i < studentCount; ++i) cin >> studentList[i].ability;
    for (int i = 0; i < studentCount; ++i) cin >> studentList[i].cost;
    for (int i = 0; i < studentCount; ++i) studentList[i].id = i + 1;

    sort(all(bugList), [](const Bug& a, const Bug& b) {
        return a.complexity > b.complexity;
    });

    sort(all(studentList), [](const Student& a, const Student& b) {
        return a.ability > b.ability;
    });

    int low = 1, high = bugCount;
    int bestDays = -1;

    vector<int> tempAssignments;
    ll tempCost;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid, tempCost, tempAssignments)) {
            bestDays = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (bestDays == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        vector<int> finalAssignments;
        check(bestDays, tempCost, finalAssignments);
        for (int i = 1; i <= bugCount; ++i) {
            cout << finalAssignments[i] << (i == bugCount ? "" : " ");
        }
        cout << endl;
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