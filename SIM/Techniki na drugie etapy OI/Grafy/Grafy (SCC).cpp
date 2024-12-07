#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void firstDepthFirstSearch(int v, vector<vector<int>>& graph, vector<bool>& visited, stack<int>& Stack) {
    visited[v] = true;
    for (int u : graph[v]) {
        if (!visited[u]) {
            firstDepthFirstSearch(u, graph, visited, Stack);
        }
    }
    Stack.push(v);
}

void secondDepthFirstSearch(int v, vector<vector<int>>& transposedGraph, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);
    for (int u : transposedGraph[v]) {
        if (!visited[u]) {
            secondDepthFirstSearch(u, transposedGraph, visited, component);
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> graph(N + 1);
    vector<vector<int>> transposedGraph(N + 1);

    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        graph[A].push_back(B);
        transposedGraph[B].push_back(A);
    }

    stack<int> Stack;
    vector<bool> visited(N + 1, false);

    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) {
            firstDepthFirstSearch(i, graph, visited, Stack);
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> SCCs;

    while (!Stack.empty()) {
        int v = Stack.top();
        Stack.pop();
        if (!visited[v]) {
            vector<int> component;
            secondDepthFirstSearch(v, transposedGraph, visited, component);
            SCCs.push_back(component);
        }
    }

    int sccCount = SCCs.size();
    if (sccCount == 1) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> inDegree(sccCount, 0);
    vector<int> outDegree(sccCount, 0);
    vector<int> sccIndex(N + 1, -1);

    for (int i = 0; i < sccCount; ++i) {
        for (int v : SCCs[i]) {
            sccIndex[v] = i;
        }
    }

    for (int i = 1; i <= N; ++i) {
        for (int j : graph[i]) {
            if (sccIndex[i] != sccIndex[j]) {
                outDegree[sccIndex[i]]++;
                inDegree[sccIndex[j]]++;
            }
        }
    }

    int sourcesValue = 0, sinksValue = 0;
    for (int i = 0; i < sccCount; ++i) {
        if (inDegree[i] == 0) sourcesValue++;
        if (outDegree[i] == 0) sinksValue++;
    }

    cout << max(sourcesValue, sinksValue) << endl;

    return 0;
}
