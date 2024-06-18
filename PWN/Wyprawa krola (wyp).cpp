#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX_N = 5000000;
vector<int> graf[MAX_N];
bool odwiedzone[MAX_N];

int bfs(int start, int target, int n) {
    queue<pair<int, int>> q;
    q.push({start, 0});
    odwiedzone[start] = true;

    while (!q.empty()) {
        int node = q.front().first;
        int dist = q.front().second;
        q.pop();

        if (node % n == 0 && node != start) {
            return dist;
        }

        for (int neighbor : graf[node]) {
            if (!odwiedzone[neighbor]) {
                odwiedzone[neighbor] = true;
                q.push({neighbor, dist + 1});
            }
        }
    }
    return -1;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graf[a].push_back(b);
    }

    
    for (int i = 0; i < k; i++) {
        for (int j = 1 + n*i; j <= n*(i+1); j++) {
            for (int l : graf[j]) {
                if((j-1) / n == (l - 1) / n) {
                    graf[l].push_back(j + n);
                    graf[j + n].push_back(l + n); 
                }
            }
        }
    }
   
    int min_path = bfs(1, n * (k+1), n);
    cout << min_path;

    return 0;
}
