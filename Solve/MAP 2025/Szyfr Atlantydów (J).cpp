#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

LL base = 647;
LL mod = 1e9 + 7;

int main() {
ios_base::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	vector <string> a(n);
	vector <bool> used(n, false);

	for (int i = 0; i < n; ++i) cin >> a[i];

	sort(a.begin(), a.end());

	// for(auto i : a) {
	// 	cout << i << " ";
	// }
	// cout << endl;

	vector<vector<LL>> prefhash(n, vector<LL>(n + 1));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
	 		prefhash[i][j + 1] = ((prefhash[i][j] + a[i][j]) * base) % mod;
	}


	for (int i = 1; i <= n; ++i) {
		int previousIndex = -1;
		bool wasUsed = 0;
		for(int j = 0; j < n; ++j) { 
			if(used[j]) continue;
			if (previousIndex != -1) {
				if(prefhash[j][i] != prefhash[previousIndex][i]) {
					cout << a[previousIndex] << endl;
					used[previousIndex] = 1;
					wasUsed = true;
					//cout << "skibidi";
					break;
				}
			}
			previousIndex = j;
		}
		if(!wasUsed) {
			cout << a[previousIndex] << endl;
			used[previousIndex] = 1;
			//cout << "skibidi";
		}
		// cout << "prev " << previousIndex << endl;
		// cout << "USED:" << endl;
		// for (int j = 0; j < n; j++) {
		// cout << used[j] << endl;
		// }
		// cout << "END" << endl; 
	}
}