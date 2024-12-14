#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MAX_N = 2*1e5+1;
const int MOD = 1e9+7;

struct Edge {
    int U, V, W;
    Edge(int U, int V, int W) : U(U), V(V), W(W) {}
};
vector<Edge> neighbourList[MAX_N];

bool canAchieveAverage(int N, double avg) {
    vector<double> DP(N, -1e18);
    DP[N-1] = 0;

    for (int i = N-1; i >= 0; --i) {
        for (const Edge& edge : neighbourList[i]) {
            DP[edge.V] = max(DP[edge.V], DP[edge.U] + edge.W - avg);
        }
    }

    for(int i = 0; i < N; i++) {
        if(DP[i] > 0) {
            return true;
        }
    }

    return DP[0] >= 0;
}

double findMaxAverage(int N) {
    double low = 0, high = 1e6, mid;
    for (int i = 0; i < 50; ++i) {
        mid = (low + high) / 2;
        if (canAchieveAverage(N, mid)) {
            low = mid;
        } else {
            high = mid;
        }
    }
    return low;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    for(int i = 0; i < M; i++) {
        int A, B, C;
        cin >> A >> B >> C;
        A--; B--;

        neighbourList[A].push_back(Edge(A, B, C));
    }

    cout << fixed << setprecision(6) << findMaxAverage(N) << endl;
    return 0;
}
