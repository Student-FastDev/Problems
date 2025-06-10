#include<bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long LL;

int main(){
	cin.tie(0)->sync_with_stdio(0), cout.tie(0);
	LL t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		int cnt0 = 0, cnt1 = 0, cntm1 = 0, cnte = 0;
		for(int i = 0; i < n; i++){
			LL x;
			cin >> x;
			if(x == 0LL)
				cnt0++;
			else if(x == 1LL)
				cnt1++;
			else if(x == -1LL)
				cntm1++;
			else
				cnte++;
		}	

		if(cntm1 == 0){
			if(cnte < 2)
				cout << "TAK\n";
			else
				cout << "NIE\n";
		}else{
			if(cnte != 0)
				cout << "NIE\n";
			else{
				if(cnt1== 0){
					if(cntm1 == 1)
						cout << "TAK\n";
					else
						cout << "NIE\n";
				}else
					cout << "TAK\n";
			}
		}
	}
}