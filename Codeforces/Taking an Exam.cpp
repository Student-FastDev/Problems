#include <bits/stdc++.h>
using namespace std;
#ifdef DEBUG
auto operator<<(auto&o, auto x)->decltype(x.end(), o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
auto operator<<(auto&o, auto p)->decltype(p.first, o) {return o << '('<<p.first <<", "<<p.second<<')';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X)
#else
#define LOG(X...)(void)0
#endif

void solve() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int m, n;
	cin >> n >> m;
	vector<int> values(n);
	for (int i = 0; i < n; i++) {
		cin >> values[i];
	}
	sort(values.begin(), values.end());
	int count = 0;
	long long time = 0;
	for (int i = 0; i < n; i++) {
		if (time + values[i] <= (long long)m) {
			time += values[i];
			count++;
		}
	}
	LOG(count);
	cout << m + count << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
		solve();
}
