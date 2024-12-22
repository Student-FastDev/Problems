#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int to, weight;
};

const int INF = INT_MAX;

typedef pair<int, int> PAIR;

void dijkstra(int start, const vector<vector<Edge>>& graph, vector<int>& dist) {
    priority_queue<PAIR, vector<PAIR>, greater<PAIR>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int current_dist = pq.top().first;
        int current = pq.top().second;
        pq.pop();

        if (current_dist > dist[current]) continue;

        for (const Edge& edge : graph[current]) {
            int next = edge.to;
            int weight = edge.weight;

            if (dist[current] + weight < dist[next]) {
                dist[next] = dist[current] + weight;
                pq.push({dist[next], next});
            }
        }
    }
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<Edge>> graph(N);

    for (int i = 0; i < M; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        graph[a].push_back({b, t});
        graph[b].push_back({a, t});
    }

    vector<int> guards(K);
    for (int i = 0; i < K; ++i) {
        cin >> guards[i];
    }

    int bubuStart;
    cin >> bubuStart;

    vector<int> bubuDist(N, INF);
    dijkstra(bubuStart, graph, bubuDist);

    vector<int> guardDist(N, INF);
    for (int guard : guards) {
        vector<int> tempDist(N, INF);
        dijkstra(guard, graph, tempDist);
        for (int i = 0; i < N; ++i) {
            guardDist[i] = min(guardDist[i], tempDist[i]);
        }
    }

    int bubuTime = bubuDist[1];
    if (bubuTime >= guardDist[1]) {
        cout << -1 << endl;
    } else {
        cout << bubuTime << endl;
    }

    return 0;
}
