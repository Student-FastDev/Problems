#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()
int main(){
	int n;
	cin >> n;
	vector<int> v(n);
	for(auto& e : v)
		cin >> e;

	vector<int> pre1;
	vector<int> post1;
	bool found = 0;
	post1.pb(1);
	for(int i = 0; i < n; i++){
		if(v[i] == 1){
			found = 1;
			continue;
		}
		if(found)
			post1.pb(v[i]);
		else
			pre1.pb(v[i]);
	}

	sort(all(pre1));
	sort(all(post1));
	map<int, vector<int>> m;

	for(int x : pre1){
		int i = lower_bound(all(post1), x) - post1.begin() - 1;
		m[post1[i]].pb(x);
	}
	cout << "TAK" << endl;

	found = 0;
	for(int i = 0; i < n; i++){
		if(v[i] == 1)
			found = 1;
		if(found){
			cout << v[i] << ' ';
			for(int j : m[v[i]])
				cout << j << ' ';
		}
	}
}