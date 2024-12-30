#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 1e9+1;
const int MOD = 1e9+7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<vector<int>> adjacencyList(N);
        for (int I = 1; I < N; I++) {
            int nodeU, nodeV;
            cin >> nodeU >> nodeV;
            nodeU--;
            nodeV--;
            adjacencyList[nodeU].push_back(nodeV);
            adjacencyList[nodeV].push_back(nodeU);
        }

        vector<int> degrees(N, 2);
        for (int I = 0; I < N; I++) {
            if (adjacencyList[I].size() == 1) {
                degrees[I] = 0;
                int neighbor = adjacencyList[I][0];
                degrees[neighbor] = min(degrees[neighbor], 1);
            }
        }

        int totalDegreeOne = count(degrees.begin(), degrees.end(), 1);
        int totalDegreeTwo = count(degrees.begin(), degrees.end(), 2);
        vector<int> subtreeSizeTwo(N), parents(N, -1), subtreeSizeOne(N);

        ll result = 0;
        auto depthFirstSearch = [&](auto &&self, int currentNode) -> void {
            subtreeSizeTwo[currentNode] = (degrees[currentNode] == 2);
            subtreeSizeOne[currentNode] = (degrees[currentNode] == 1);

            for (auto neighbor : adjacencyList[currentNode]) {
                if (neighbor == parents[currentNode]) {
                    continue;
                }
                parents[neighbor] = currentNode;
                self(self, neighbor);
                subtreeSizeTwo[currentNode] += subtreeSizeTwo[neighbor];
                subtreeSizeOne[currentNode] += subtreeSizeOne[neighbor];

                if (degrees[currentNode] == 0) {
                    result += subtreeSizeOne[neighbor] + subtreeSizeTwo[neighbor];
                } else if (degrees[neighbor] == 1) {
                    result += subtreeSizeTwo[neighbor];
                }
                if (degrees[neighbor] == 0) {
                    result += totalDegreeOne - subtreeSizeOne[neighbor] + totalDegreeTwo - subtreeSizeTwo[neighbor];
                } else if (degrees[currentNode] == 1) {
                    result += totalDegreeTwo - subtreeSizeTwo[neighbor];
                }
            }
        };
        depthFirstSearch(depthFirstSearch, 0);
        cout << result << "\n";
    }
    return 0;
}
