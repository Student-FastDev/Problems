#include <iostream>
#include <vector>
#include <bitset>

const int MAX_N = 3001;

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<bitset<MAX_N>> adj(N + 1);

    for (int i = 0; i < M; ++i) {
        int V, U;
        cin >> V >> U;
        adj[V][U] = 1;
        adj[U][V] = 1;
    }

    long long triangleCount = 0;

    for (int V = 1; V <= N; ++V) {
        for (int U = V + 1; U <= N; ++U) {
            if (adj[V][U]) {
                triangleCount += (adj[V] & adj[U]).count();
            }
        }
    }

    cout << triangleCount/3 << endl;

    return 0;
}
