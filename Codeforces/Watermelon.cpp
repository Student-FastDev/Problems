#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
 
int main()
{
    int N;
    cin >> N;
    
    if(N == 2) {
        cout << "NO" << endl;
        return 0;
    }
    
    if(N % 2 == 0) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
 
    return 0;
}
