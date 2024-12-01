#include <iostream>
#include <vector>
#include <string>
using namespace std;

class UnionFind {
private:
    vector<int> parentArray, rankArray, offsetArray;

public:
    UnionFind(int N) {
        parentArray.resize(N);
        rankArray.resize(N, 0);
        offsetArray.resize(N, 0);
        for (int i = 0; i < N; i++) {
            parentArray[i] = i;
        }
    }

    int find(int x) {
        if (parentArray[x] != x) {
            int root = find(parentArray[x]);
            offsetArray[x] += offsetArray[parentArray[x]];
            parentArray[x] = root;
        }
        return parentArray[x];
    }

    bool unionSets(int x, int y, int diff) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rankArray[rootX] > rankArray[rootY]) {
                parentArray[rootY] = rootX;
                offsetArray[rootY] = offsetArray[x] - offsetArray[y] + diff;
            } else if (rankArray[rootX] < rankArray[rootY]) {
                parentArray[rootX] = rootY;
                offsetArray[rootX] = offsetArray[y] - offsetArray[x] - diff;
            } else {
                parentArray[rootY] = rootX;
                offsetArray[rootY] = offsetArray[x] - offsetArray[y] + diff;
                rankArray[rootX]++;
            }
        } else {
            if (offsetArray[y] - offsetArray[x] != diff) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    int N, Z;
    cin >> N >> Z;

    UnionFind uf(N);
    vector<string> resultArray;

    for (int z = 0; z < Z; z++) {
        int i, j, w;
        cin >> i >> j >> w;
        i--;
        j--;

        if (uf.unionSets(i, j, w)) {
            resultArray.push_back("TAK");
        } else {
            resultArray.push_back("NIE");
        }
    }

    for (const string &res : resultArray) {
        cout << res << "\n";
    }

    return 0;
}
