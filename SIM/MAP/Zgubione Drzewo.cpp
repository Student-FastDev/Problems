#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    auto query = [&](int r) -> vector<int> {
        cout << "? " << r << endl;
        cout.flush();
        vector<int> distances(N + 1);
        for (int i = 1; i <= N; ++i) {
            cin >> distances[i];
        }
        return distances;
    };

    vector<int> initialDistances = query(1);

    vector<int> even, odd;
    for (int i = 1; i <= N; ++i) {
        if (initialDistances[i] % 2 == 0) {
            even.push_back(i);
        } else {
            odd.push_back(i);
        }
    }

    vector<pair<int, int>> edges;

    vector<int> nodesToQuery = (even.size() <= odd.size()) ? even : odd;
    for (int node : nodesToQuery) {
        vector<int> distances;
        if(node == 1) distances = initialDistances;
        else distances = query(node);
        for (int i = 1; i <= N; ++i) {
            if (distances[i] == 1) {
                edges.emplace_back(node, i);
            }
        }
    }

    cout << "!" << endl;
    for (auto [u, v] : edges) {
        cout << u << " " << v << endl;
    }
    cout.flush();
    return 0;
}
