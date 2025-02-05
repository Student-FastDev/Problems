#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 200001;
vector<int> neighbourList[MAX_N];

int guildArray[MAX_N];

void DFS(int A, int P) {
    if (P == 2) {
        guildArray[A] = 1;
    } else {
        guildArray[A] = 2;
    }

    for (auto i : neighbourList[A]) {
        if (guildArray[i] == 0) {
            DFS(i, guildArray[A]);
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= M; i++) {
        int A, B;
        cin >> A >> B;
        neighbourList[A].push_back(B);
        neighbourList[B].push_back(A);
    }

    bool onlyOne = false;
    for (int i = 1; i <= N; i++) {
        if(neighbourList[i].empty()) {
            onlyOne = true;
        }
        if (guildArray[i] == 0) {
            DFS(i, 2);
        }
    }
    
    if(onlyOne) {
        cout << "NIE" << endl;
        return 0;
    } else {
        cout << "TAK" << endl;
        for(int i = 1; i <= N; i++) {
            cout << (guildArray[i] == 1 ? "S" : "K") << endl;
        }
    }

    return 0;
}
