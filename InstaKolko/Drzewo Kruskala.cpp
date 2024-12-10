#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    long long U, V, weight, index;
    bool operator<(const Edge& other) const {
        if (weight == other.weight) {
            return index < other.index;
        }
        return weight < other.weight;
    }
};

long long find(vector<long long>& parent, long long U) {
    if (parent[U] != U) {
        parent[U] = find(parent, parent[U]);
    }
    return parent[U];
}

void unite(vector<long long>& parent, vector<long long>& rank, long long U, long long V) {
    long long rootU = find(parent, U);
    long long rootV = find(parent, V);
    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

int main() {
    long long N, M;
    cin >> N >> M;
    vector<Edge> edges(M);
    for (long long i = 0; i < M; ++i) {
        cin >> edges[i].U >> edges[i].V >> edges[i].weight;
        edges[i].index = i + 1;
    }

    sort(edges.begin(), edges.end());

    vector<long long> parent(N + 1), rank(N + 1, 0);
    for (long long i = 1; i <= N; ++i) {
        parent[i] = i;
    }

    vector<long long> MST;
    for (const auto& edge : edges) {
        if (find(parent, edge.U) != find(parent, edge.V)) {
            unite(parent, rank, edge.U, edge.V);
            MST.push_back(edge.index);
            if (MST.size() == N - 1) break;
        }
    }

    for (long long index : MST) {
        cout << index << endl;
    }

    return 0;
}
