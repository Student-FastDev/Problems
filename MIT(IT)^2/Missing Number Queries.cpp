#include <bits/stdc++.h>
using namespace std;
#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif


int main() {
    ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n, q;
	cin >> n >> q;
	vector<int> values(n);
	for (int i = 0; i < n; i++)
		cin >> values[i];
	
	vector<set<int>> sets(n + 1);
	for (int i = 0; i < n; i++)
		sets[values[i]].insert(i);
	
	set<pair<int, int>> first;
	set<pair<int, int>> last;
	for (int i = 1; i <= n; i++) {
		if (sets[i].size() > 0) {
			first.insert({*sets[i].begin(), i});
			last.insert({*sets[i].rbegin(), i});
		} else {
			first.insert({n+1, i});
			last.insert({-1, i});
		}
	}
	
	for (int query = 0; query < q; query++) {
		int query_type;
		cin >> query_type;
		if (query_type == 1) {
			int x, y;
			cin >> x >> y;
			x--;
			int before = values[x];
			values[x] = y;
			 // erase last element

			bool was_first = 0;
			auto it_this = sets[before].find(x);
			if (sets[before].begin() == it_this)
				was_first = 1;
			bool was_last = 0;
			if (prev(sets[before].end()) == it_this)
				was_last = 1;
			sets[before].erase(x);
			if (was_first) {
				first.erase({x, before});
				if (sets[before].size() > 0) {
					first.insert({*sets[before].begin(), before});
				} else {
					first.insert({n+1, before});
				}
			}
			if (was_last) {
				last.erase({x, before});
				if (sets[before].size() > 0) {
					last.insert({*sets[before].rbegin(), before});
				} else {
					last.insert({-1, before});
				}
			}
		
			// add new it
			if (sets[y].size() == 0) {
				first.erase({n+1, y});
				last.erase({-1, y});
			} else {
				auto low = *sets[y].begin();
				auto high = *sets[y].rbegin();
				first.erase({low, y});
				last.erase({high, y});
			}
			sets[y].insert(x);
			first.insert({*sets[y].begin(), y});
			last.insert({*sets[y].rbegin(), y});			
		} else {
			auto i1 = *last.begin();
			auto i2 = *first.rbegin();
			int l, r;
			cin >> l >> r;
			l--, r--;
			if (i1.first < l) {
				cout << i1.second << "\n";
			} else if (i2.first > r) {
				cout << i2.second << "\n";
			}
		}
	}
}
