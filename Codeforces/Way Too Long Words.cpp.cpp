#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
 
int main()
{
    int N;
    cin >> N;
    
    for(int i = 0; i < N; i++) {
        string S;
        cin >> S;
        
        if(S.length() > 10) {
            cout << S[0] << S.length()-2 << S[S.length()-1] << endl;
        }
        else {
            cout << S << endl;
        }
    }
 
    return 0;
}
