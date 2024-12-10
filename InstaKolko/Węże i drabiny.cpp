#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

int minDiceThrows(int N, vector<pair<int, int>>& laddersArray, int M, vector<pair<int, int>>& snakes) {
    unordered_map<int, int> board;
    for (auto& ladder : laddersArray) {
        board[ladder.first] = ladder.second;
    }
    for (auto& snake : snakes) {
        board[snake.first] = snake.second;
    }

    vector<bool> visited(101, false);
    queue<pair<int, int>> Q;
    Q.push({1, 0});
    visited[1] = true;

    while (!Q.empty()) {
        auto [pos, throws] = Q.front();
        Q.pop();

        if (pos == 100) {
            return throws;
        }

        for (int i = 1; i <= 6; ++i) {
            int nextPos = pos + i;
            if (nextPos > 100) continue;
            if (board.find(nextPos) != board.end()) {
                nextPos = board[nextPos];
            }
            if (!visited[nextPos]) {
                visited[nextPos] = true;
                Q.push({nextPos, throws + 1});
            }
        }
    }

    return -1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N;
        vector<pair<int, int>> laddersArray(N);
        for (int i = 0; i < N; ++i) {
            cin >> laddersArray[i].first >> laddersArray[i].second;
        }
        cin >> M;
        vector<pair<int, int>> snakes(M);
        for (int i = 0; i < M; ++i) {
            cin >> snakes[i].first >> snakes[i].second;
        }
        cout << minDiceThrows(N, laddersArray, M, snakes) << endl;
    }
    return 0;
}
