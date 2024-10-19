#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2*1e5+1;
const int MOD = 1e9+7;

vector<int> neighbourList[MAX_N];
int visitedArray[MAX_N];
int bfsDistanceArray[MAX_N];

void addEdge(int A, int B) {
	neighbourList[A].push_back(B);
	neighbourList[B].push_back(A);
}

void DFS(int srcVertex, int parentColor) {
	visitedArray[srcVertex] = parentColor;

	for(auto i : neighbourList[srcVertex]) {
		if(visitedArray[i] == 0) {
			DFS(i, parentColor);
		}
	}
}

void BFS(int srcVertex) {
	queue<int> bfsQue;
    bfsQue.push(srcVertex);

	while(!bfsQue.empty()) {
		int bfsVertex = bfsQue.front();

		for(int i = 0; i < neighbourList[bfsVertex].size(); i++) {
            int currentIndex = neighbourList[bfsVertex][i];
			if(bfsDistanceArray[currentIndex] == 0) {
				bfsQue.push(currentIndex);
                bfsDistanceArray[currentIndex] = bfsDistanceArray[bfsVertex] + 1;
			}
		}
		bfsQue.pop();
	}
}

void resetArrays(int N) {
    fill(visitedArray, visitedArray + N + 1, 0);
    fill(bfsDistanceArray, bfsDistanceArray + N + 1, 0);
    for(int i = 0; i <= N; i++) {
        neighbourList[i].clear();
    }
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	
	int T;
	cin >> T;

	while (T--) {
		int N, M;
		cin >> N >> M;

		resetArrays(N);

		for(int i = 0; i < M; i++) {
			int A, B;
			cin >> A >> B;

			addEdge(A, B);
		}

		int friendGroups = 0;
		for(int i = 1; i <= N; i++) {
			if(visitedArray[i] == 0) {
				DFS(i, i);
				friendGroups++;
			}
		}

		int P;
		cin >> P;

		cout << "Znajomi numeru " << P << ":" << endl;
		BFS(P);

		for(int i = 1; i <= N; i++) {
			if(bfsDistanceArray[i] > 0 && i != P) {
				cout << i << ": " << bfsDistanceArray[i] << endl;
			}
		}

		cout << "Grup znajomych jest " << friendGroups << "." << endl;
	}

	return 0;
}
