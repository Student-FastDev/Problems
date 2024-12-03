#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

int main() {
    int N, M;
    cin >> N >> M;

    UnionFind uf(N);

    for (int i = 0; i < M; ++i) {
        int A, B;
        cin >> A >> B;
        uf.unite(A, B);
    }

    int Z;
    cin >> Z;

    for (int i = 0; i < Z; ++i) {
        int X, Y;
        cin >> X >> Y;
        if (uf.find(X) == uf.find(Y)) {
            cout << "TAK" << endl;
        } else {
            cout << "NIE" << endl;
        }
    }

    return 0;
}
