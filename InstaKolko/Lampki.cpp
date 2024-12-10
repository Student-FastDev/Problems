#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void BFS(int start, const vector<vector<int>>& neighbourList, vector<int>& color, vector<string>& result) {
    queue<int> q;
    q.push(start);
    color[start] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : neighbourList[u]) {
            if (color[v] == -1) {
                color[v] = 1 - color[u];
                q.push(v);
            } else if (color[v] == color[u]) {
                queue<int> markQueue;
                markQueue.push(start);
                while (!markQueue.empty()) {
                    int x = markQueue.front();
                    markQueue.pop();
                    if (result[x] == "fajne") {
                        result[x] = "niefajne";
                        for (int y : neighbourList[x]) {
                            if (result[y] == "fajne") {
                                markQueue.push(y);
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> neighbourList(N + 1);
    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        neighbourList[A].push_back(B);
        neighbourList[B].push_back(A);
    }

    vector<int> color(N + 1, -1);
    vector<string> result(N + 1, "fajne");

    for (int i = 1; i <= N; ++i) {
        if (color[i] == -1) {
            BFS(i, neighbourList, color, result);
        }
    }

    for (int i = 1; i <= N; ++i) {
        cout << result[i] << endl;
    }
    return 0;
}
