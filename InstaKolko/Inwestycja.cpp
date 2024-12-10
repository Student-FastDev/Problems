#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<long long>> neighbourList;
vector<long long> subtreeSize;

long long DFS(long long node, long long parent) {
    long long size = 1;
    for (long long neighbor : neighbourList[node]) {
        if (neighbor != parent) {
            size += DFS(neighbor, node);
        }
    }
    subtreeSize[node] = size;
    return size;
}

int main() {
    long long N;
    cin >> N;

    neighbourList.resize(N + 1);
    subtreeSize.resize(N + 1);

    for (long long i = 0; i < N - 1; ++i) {
        long long U, V;
        cin >> U >> V;
        neighbourList[U].push_back(V);
        neighbourList[V].push_back(U);
    }

    DFS(1, -1);

    long long maxLoad = 0;
    for (long long U = 1; U <= N; ++U) {
        for (long long V : neighbourList[U]) {
            if (subtreeSize[V] < subtreeSize[U]) {
                long long load = subtreeSize[V] * (N - subtreeSize[V]);
                maxLoad = max(maxLoad, load);
            }
        }
    }

    cout << maxLoad << endl;
    return 0;
}
