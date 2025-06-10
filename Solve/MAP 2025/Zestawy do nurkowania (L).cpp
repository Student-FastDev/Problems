#include<bits/stdc++.h>
using namespace std;

int main(){
	int m, p, b, k;
	cin >> m >> p >> b >> k;
	int ans = min({m, p, b});
	cout << max(0, ans - k) << endl;
}