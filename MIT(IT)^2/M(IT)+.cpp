#include <bits/stdc++.h>
using namespace std;
#ifdef DEBUG
auto operator<<(auto&o, auto p)->decltype(p.first, o) {return o << '('<<p.first <<", "<<p.second<<')';}
auto operator<<(auto&o, auto x)->decltype(x.end(), o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(X...)cerr<<"["#X"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(X)
#else
#define LOG(X...)(void)0
#endif

void solve() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	cin >> n;
	string s;
	cin >> s;
	bool started = 0;
	LOG(s);
	for (int i = 0; i < n; i++) {
		if (s[i] == 'M') {
			started = 1;
			if (i + 2 >= n) {
				cout << "NO\n";
				LOG(i, __LINE__);
				return;
			}
			if (s[i+1] != 'I' || s[i+2] != 'T') {
				cout << "NO\n";
				LOG(i, __LINE__);
				return;
			}
			i += 2;
		} else if (s[i] == 'I' && started) {
			LOG(i, s[i], n);
			if (i + 1 >= n) {
				cout << "NO\n";
				LOG(i, __LINE__);
				return;
			}
			if (s[i+1] != 'T') {
				cout << "NO\n";
				LOG(i, __LINE__);
				return;
			}
			i++;
		} else {
			cout << "NO\n";
			LOG(i, __LINE__);
			return;
		}
	}
	cout << "YES\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
		solve();
}
