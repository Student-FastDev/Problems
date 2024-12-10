#include <iostream>
#include <vector>
using namespace std;

void DFS(int v, vector<vector<int>>& neighbourList, vector<bool>& visited) {
    visited[v] = true;
    for (int u : neighbourList[v]) {
        if (!visited[u]) {
            DFS(u, neighbourList, visited);
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<vector<int>> neighbourList(N);
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        neighbourList[a].push_back(b);
        neighbourList[b].push_back(a);
    }
    
    vector<bool> visited(N, false);
    DFS(0, neighbourList, visited);
    
    bool isConnected = true;
    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            isConnected = false;
            break;
        }
    }
    
    if (isConnected) {
        cout << "SPOJNY" << endl;
    } else {
        cout << "NIE" << endl;
    }
    
    return 0;
}
