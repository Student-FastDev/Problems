#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <functional>

using namespace std;

typedef pair<int, int> Edge;
typedef tuple<int, int, int> GraphEdge;

void primMST(int N, vector<vector<Edge>>& graph) {
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    vector<bool> visited(N + 1, false);
    vector<int> result;

    pq.push({0, 1});
    int totalCost = 0;

    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        result.push_back(u);
        totalCost += cost;

        for (auto& [nextCost, v] : graph[u]) {
            if (!visited[v]) {
                pq.push({nextCost, v});
            }
        }
    }

    for (int i = 0; i < result.size(); ++i) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<Edge>> graph(N + 1);

    for (int i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].emplace_back(c, b);
        graph[b].emplace_back(c, a);
    }

    primMST(N, graph);

    return 0;
}
