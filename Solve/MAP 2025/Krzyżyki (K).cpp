#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin >> t;

	while(t--){
		cout << 5 << endl;
		int x;
		cin >> x;
		vector<int> m(10);
		m[1] = 9;
		m[2] = 8;
		m[3] = 7;
		m[4] = 6;
		m[6] = 4;
		m[7] = 3;
		m[8] = 2;
		m[9] = 1;
		cout << m[x] << endl;
	}
}