#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int to, time;
};

const int MAXN = 100001;
const int INF = INT_MAX;

vector<Edge> graph[MAXN];
vector<Edge> reverse_graph[MAXN]; // Reverse graph to calculate reverse distances
int stop_time[MAXN];
int dist_home[MAXN], dist_store[MAXN];
int reverse_dist_home[MAXN], reverse_dist_store[MAXN]; // Reverse distance arrays

void dijkstra(int start, int dist[], const vector<Edge> graph[], int N, const string &dist_name) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    fill(dist, dist + N + 1, INF);
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int curr_dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (curr_dist > dist[node]) continue;

        for (Edge edge : graph[node]) {
            int next_node = edge.to;
            int time = edge.time;
            int new_dist = curr_dist + time + stop_time[next_node];
            if (new_dist < dist[next_node]) {
                dist[next_node] = new_dist;
                pq.push({new_dist, next_node});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; ++i) {
        int C;
        cin >> C;
        if (C == 1) {
            int K;
            cin >> K;
            stop_time[i] = K;
        } else {
            stop_time[i] = 0;
        }
    }

    for (int i = 0; i < M; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        graph[u].push_back({v, t});
        reverse_graph[v].push_back({u, t});
    }

    dijkstra(1, dist_home, graph, N, "dist_home");
    dijkstra(N, dist_store, graph, N, "dist_store");

    dijkstra(1, reverse_dist_home, reverse_graph, N, "reverse_dist_home");
    dijkstra(N, reverse_dist_store, reverse_graph, N, "reverse_dist_store");

    int Q;
    cin >> Q;

    while (Q--) {
        int building, hour;
        cin >> building >> hour;

        int start_time = hour * 60;

        int time_to_store_via_building = dist_home[building] + reverse_dist_store[building] - stop_time[building] + dist_store[1];
        int time_back_home_via_building = dist_home[N] + dist_store[building] + reverse_dist_home[building] - stop_time[building];

        int total_time = start_time + min(time_back_home_via_building, time_to_store_via_building);

        if (total_time < 20 * 60) {
            int return_hour = total_time / 60;
            int return_minute = total_time % 60;
            cout << "TAK " << return_hour << ":" << return_minute << endl;
        } else {
            cout << "NIE" << endl;
        }
    }

    return 0;
}