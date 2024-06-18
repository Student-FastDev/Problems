#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int MAX_N = 1001;
int map[MAX_N][MAX_N];
int visited[MAX_N * MAX_N];

int formulaCreator(int i, int j, int middle) {
    return (i * i * i) - (j * j) + (middle * middle) + (i * j * middle);
}

void checkIterative(int start_i, int start_j, int& countingVariable, int max, int tag, int limitValue) {
    queue<pair<int, int>> q;
    q.push({start_i, start_j});
    visited[start_i * limitValue + start_j] = tag;

    while (!q.empty()) {
        int a = q.front().first;
        int b = q.front().second;
        q.pop();
        countingVariable++;

        if (a + 1 < limitValue && map[a + 1][b] <= max && visited[(a + 1) * limitValue + b] != tag) {
            visited[(a + 1) * limitValue + b] = tag;
            q.push({a + 1, b});
        }
        if (b + 1 < limitValue && map[a][b + 1] <= max && visited[a * limitValue + (b + 1)] != tag) {
            visited[a * limitValue + (b + 1)] = tag;
            q.push({a, b + 1});
        }
        if (a - 1 >= 0 && map[a - 1][b] <= max && visited[(a - 1) * limitValue + b] != tag) {
            visited[(a - 1) * limitValue + b] = tag;
            q.push({a - 1, b});
        }
        if (b - 1 >= 0 && map[a][b - 1] <= max && visited[a * limitValue + (b - 1)] != tag) {
            visited[a * limitValue + (b - 1)] = tag;
            q.push({a, b - 1});
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    int maxValue = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
            maxValue = max(maxValue, map[i][j]);
        }
    }

    int left = 0;
    int right = maxValue;
    int middle;

    while (left <= right) {
        middle = (left + right) / 2;
        bool isGood = false;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (map[i][j] <= middle && visited[i * n + j] != middle) {
                    int scoreCounter = 0;
                    checkIterative(i, j, scoreCounter, middle, middle, n);
                    if (scoreCounter >= m) {
                        isGood = true;
                        break;
                    }
                }
            }
            if (isGood) {
                break;
            }
        }

        if (isGood) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    cout << left;
    return 0;
}
