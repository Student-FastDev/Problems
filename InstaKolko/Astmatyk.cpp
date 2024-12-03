#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

bool canReach(int maxHeight, const vector<int>& heights, const vector<vector<int>>& graph) {
    int N = heights.size();
    vector<bool> visited(N, false);
    queue<int> q;

    if (heights[0] > maxHeight) return false;

    q.push(0);
    visited[0] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == N - 1) {
            return true;
        }

        for (int neighbor : graph[current]) {
            if (!visited[neighbor] && heights[neighbor] <= maxHeight) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return false;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> heights(N);
    for (int i = 0; i < N; i++) {
        cin >> heights[i];
    }

    vector<vector<int>> graph(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int left = *min_element(heights.begin(), heights.end());
    int right = *max_element(heights.begin(), heights.end());
    int result = INT_MAX;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (canReach(mid, heights, graph)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (result == INT_MAX) {
        cout << "NIE ISTNIEJE" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}
