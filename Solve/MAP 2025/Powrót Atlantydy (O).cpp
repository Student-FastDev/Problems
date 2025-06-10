#include<bits/stdc++.h>
using namespace std;

int main(){
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
	string ans;
	for(int i = 1; i < k; i += 2)
		ans += "1";
	ans += s;
	if(k&1)
		ans[0] = '7';
	cout << ans << endl;
}