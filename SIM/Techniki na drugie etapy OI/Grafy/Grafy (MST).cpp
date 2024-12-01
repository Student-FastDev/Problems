#include <bits/stdc++.h>
using namespace std;

inline void readINT(int *n) {
    register char c = 0, znak_liczby = 1;
    while (c < 33) c = getc_unlocked(stdin);
    
    if (c == 45) {
        znak_liczby = -1;
        c = getc_unlocked(stdin);
    }
    
    (*n) = 0;
    while (c > 32) {
        (*n) = (*n) * 10 + c - 48;
        c = getc_unlocked(stdin);
    }
    
    (*n) *= znak_liczby;
}

struct Edge {
    int U, V, weightValue;
};

class UnionFind {
public:
    int* parentNode;

    UnionFind(int N) {
        parentNode = new int[N + 1];
        for (int i = 1; i <= N; i++) {
            parentNode[i] = -1;
        }
    }

    ~UnionFind() {
        delete[] parentNode;
    }

    int find(int x) {
        if (parentNode[x] < 0) return x;
        return parentNode[x] = find(parentNode[x]);
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (parentNode[rootX] > parentNode[rootY]) swap(rootX, rootY);
            parentNode[rootX] += parentNode[rootY];
            parentNode[rootY] = rootX;
            return true;
        }
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    readINT(&N);
    readINT(&M);

    Edge edges[M];
    for (int i = 0; i < M; i++) {
        readINT(&edges[i].U);
        readINT(&edges[i].V);
        readINT(&edges[i].weightValue);
    }

    UnionFind uf(N);
    long long mstWeight = 0;
    int edgesUsed = 0;

    for (int i = 0; i < M && edgesUsed < N - 1; i++) {
        Edge edge = edges[i];
        if (uf.unite(edge.U, edge.V)) {
            mstWeight += edge.weightValue;
            edgesUsed++;
        }
    }

    cout << mstWeight << "\n";
    return 0;
}
