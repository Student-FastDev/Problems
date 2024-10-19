#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
int main()
{
    int T;
    cin >> T;
    
    for(int i = 0; i < T; i++) {
        string S;
        cin >> S;
        
        int N = S.length();
        int sumValue = 0;
        
        for(int i = 0; i < N; i++) {
            sumValue += S[i] - '0';
        }
        
        cout << sumValue << endl;
    }
 
    return 0;
}
