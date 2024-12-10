#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void DFS(int company, const vector<vector<int>>& neighbourList, unordered_set<int>& visited, unordered_set<int>& dishonest, bool& found) {
    if (visited.count(company) || found) return;
    visited.insert(company);
    if (dishonest.count(company)) {
        found = true;
        return;
    }
    for (int dependent : neighbourList[company]) {
        DFS(dependent, neighbourList, visited, dishonest, found);
    }
}

int main() {
    int N;
    cin >> N;
    vector<vector<int>> neighbourList(N + 1);
    for (int i = 1; i <= N; ++i) {
        int a;
        cin >> a;
        if (a != 0) {
            neighbourList[i].push_back(a);
        }
    }

    int Q;
    cin >> Q;
    unordered_set<int> dishonest;
    for (int i = 0; i < Q; ++i) {
        int company;
        cin >> company;
        dishonest.insert(company);
    }

    int M;
    cin >> M;
    unordered_set<int> visited;
    bool found = false;
    DFS(M, neighbourList, visited, dishonest, found);

    if (found) {
        cout << "NIEUCZCIWA" << endl;
    } else {
        cout << "UCZCIWA" << endl;
    }

    return 0;
}
