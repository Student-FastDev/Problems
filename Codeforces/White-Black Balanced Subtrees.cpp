#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 
pair<int, int> DFS(int nodeIndex, const vector<vector<int>>& treeArray, const string& S, int& balancedCount) {
    int white = (S[nodeIndex] == 'W');
    int black = (S[nodeIndex] == 'B');
 
    for (int child : treeArray[nodeIndex]) {
        pair<int, int> result = DFS(child, treeArray, S, balancedCount);
        white += result.first;
        black += result.second;
    }
 
    if (white == black) {
        balancedCount++;
    }
 
    return {white, black};
}
 
int main() {
    int T;
    cin >> T;
 
    while (T--) {
        int N;
        cin >> N;
 
        vector<vector<int>> treeArray(N);
        for (int i = 1; i < N; ++i) {
            int parentValue;
            cin >> parentValue;
            treeArray[parentValue - 1].push_back(i); 
        }
 
        string S;
        cin >> S;
 
        int balancedCount = 0;
        DFS(0, treeArray, S, balancedCount);
 
        cout << balancedCount << endl;
    }
 
    return 0;
}
