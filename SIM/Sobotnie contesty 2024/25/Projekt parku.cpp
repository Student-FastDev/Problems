#include <iostream>
using namespace std;

int main() {
	int T;
	cin >> T;
	
	for(int i = 0; i < T; i++) {
		int N;
		long long S = 0;
		cin >> N;
		
		int treeArray[N+2][2] = {0};
		
		for(int j = 0; j < N; j++) {
			int A, B;
			cin >> A >> B;
			treeArray[A][B]++;
		}
		
		for(int j = 0; j <= N; j++) {
			if(treeArray[j][0] > 0 && treeArray[j][1] > 0) {
				S += N-2;
			}
			if(j >= 1 && j <= N && treeArray[j][0] > 0 && treeArray[j-1][1] > 0 && treeArray[j+1][1] > 0) {
				S++;
			}
			if(j >= 1 && j <= N && treeArray[j][1] > 0 && treeArray[j-1][0] > 0 && treeArray[j+1][0] > 0) {
				S++;
			}
		}
		
		cout << S << endl;
	}
}