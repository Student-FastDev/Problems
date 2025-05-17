#include<bits/stdc++.h>
using namespace std;
#define st first
#define nd second
typedef long long LL;
#define eb emplace_back

map<LL, LL> xddd;

void dfs(LL u, LL p, vector<vector<pair<LL, LL>>>& adj, LL mask){
	xddd[mask]++;
	for(auto [i, m] : adj[u]){
		if(i == p)
			continue;
		dfs(i, u, adj, mask ^ m);
	}
}

int main(){
	cin.tie(0)->sync_with_stdio(0), cout.tie(0);
	LL n;
	cin >> n;

	vector<vector<pair<LL, LL>>> adj(n);

	for(LL i = 0; i < n-1; i++){
		LL a, b;
		cin >> a >> b;
		a--; b--;
		LL mask = 0;
		LL k;
		cin >> k;
		while(k--){
			LL x;
			cin >> x;
			x--;
			mask ^= (1LL<<x);
		}
		adj[a].eb(b, mask);
		adj[b].eb(a, mask);
	}

	dfs(0, 0, adj, 0);

	LL result = 0;
	for (auto& [_, cnt] : xddd) {
    	result += 1LL * cnt * (cnt - 1) / 2;
	}
 	cout << result << '\n';
}