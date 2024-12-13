#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e6+1;
const int MOD = 1e9+7;

vector<int> counterArray(MAX_N, 0);
vector<int> DP(MAX_N, 0);

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    int uniqueGroups = 0;

    vector<int> keyString;
    vector<int> finalScore(N, 0);

    for(int i = 0; i < N; i++) {
        int tempVariable;
        cin >> tempVariable;

        if(DP[tempVariable] == 0) {
            uniqueGroups++;
            DP[tempVariable] = 1;
        }
        keyString.push_back(tempVariable);
    }

    finalScore[N-1] = uniqueGroups;
    for(int i = N-2; i >= 0; i--) {
        finalScore[i] = uniqueGroups - (keyString[i] - 1);
    }

    /*
    for(int i = 0; i < N; i++) {
        cout << finalScore[i] << " ";
    }
    cout << endl;
    */

    vector<int> groupsTable(uniqueGroups + 1, 0);
    vector<int> groupsTablePrefixSum(uniqueGroups + 1, 0);

    for(int i = 0; i < N; i++) {
        groupsTable[finalScore[i]]++;
    }

    groupsTablePrefixSum[0] = 0;
    for(int i = 1; i <= uniqueGroups; i++) {
        groupsTablePrefixSum[i] = groupsTablePrefixSum[i-1] + groupsTable[i];
    }

    for(int i = 0; i < N; i++) {
        int tempScore = finalScore[i];
        finalScore[i] = groupsTablePrefixSum[tempScore-1] + groupsTable[tempScore];
        groupsTable[tempScore]--;
    }

    for(int i = 0; i < N; i++) {
        cout << finalScore[i] << " ";
    }

    return 0;
}
