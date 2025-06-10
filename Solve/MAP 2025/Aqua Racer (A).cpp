#include<bits/stdc++.h>
using namespace std;

int main(){
	int a, b, c;
	cin >> a >> b >> c;

	if(a == b and b == c){
		cout << "NIE";
		return 0;
	}

	if(a == b){
		cout << 1 << " * " << c;
		return 0;
	}

	if(b == c){
		cout << 1 << " * " << a;
		return 0;
	}

	if(a == c){
		cout << 1 << " * " << b;
		return 0;
	}

	cout << a << " * " << 1;
}