#include <iostream>
#include <vector>

using namespace std;

vector<int> neighbourList[1000001];
bool visited[1000001];

bool DFS(int node, int dishonest) {
    if (node == dishonest) return true;
    visited[node] = true;
    for (int neighbor : neighbourList[node]) {
        if (!visited[neighbor]) {
            if (DFS(neighbor, dishonest)) return true;
        }
    }
    return false;
}

int main() {
    int N;
    cin >> N;
    
    for (int i = 1; i <= N; ++i) {
        int a;
        cin >> a;
        if (a != i) {
            neighbourList[a].push_back(i);
        }
    }
    
    int X, M;
    cin >> X >> M;
    
    fill(visited, visited + N + 1, false);
    
    if (DFS(M, X)) {
        cout << "NIEUCZCIWA" << endl;
    } else {
        cout << "UCZCIWA" << endl;
    }
    
    return 0;
}
