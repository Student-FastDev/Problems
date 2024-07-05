#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void dfs(int guest, const vector<int>& leftOf, vector<bool>& visited) {
    int current = guest;
    while (!visited[current]) {
        visited[current] = true;
        current = leftOf[current];
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> leftOf(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> leftOf[i];
    }

    vector<bool> visited(n + 1, false);
    int tableCount = 0;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i, leftOf, visited);
            ++tableCount;
        }
    }

    cout << tableCount << endl;
    return 0;
}
