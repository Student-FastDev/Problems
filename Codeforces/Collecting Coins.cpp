#include <bits/stdc++.h>
using namespace std;
#ifdef DEBUG
auto operator<<(auto&o, auto x)->decltype(x.end(), o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
auto operator<<(auto&o, auto p)->decltype(p.first, o) {return o << '('<<p.first <<", "<<p.second<<')';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X)
#else
#define LOG(X...)(void)0
#endif

struct ed {
	int node;
	int c;
	int r;
};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector<vector<ed>> graph(n);
	for (int i = 0; i < m; i++) {
		int a, b, c, r;
		cin >> a >> b >> c >> r;
		a--, b--;
		graph[a].push_back({b, c, r});
		graph[b].push_back({a, c, r});
	}
	auto dij = [&](long long check) -> bool { // walk without better "good" edges :)
		vector<long long> dp(n, -1);
		priority_queue<pair<long long, int>> q;
		q.push({check, 0});
		while (!q.empty()) {
			int node = q.top().second;
			long long left = q.top().first;
			q.pop();
			if (dp[node] >= left)
				continue;
			dp[node] = left;
			for (auto &edge : graph[node]) {
				if (left - edge.c < 0)
					continue;
				if (edge.r - edge.c > 0)
					return true;
				if (dp[edge.node] >= left - edge.c + edge.r)
					continue;
				q.push({left - edge.c + edge.r, edge.node});
			}
		}
		if (dp[n-1] < 0)
			return false;
		return true;
	};
	
	long long left = 0;
	long long right = (long long)1e14 + 1;
	while (left != right) {
		long long mid = (left + right) / 2;
		if (dij(mid)) {
			right = mid;
		} else {
			left = mid + 1;
		}
	}
	cout << left << "\n";
}
