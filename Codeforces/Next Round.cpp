#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
 
int main()
{
    int N, K;
    cin >> N >> K;
    
    int finalValue = -1;
    int S = 0;
    for(int i = 0; i < N; i++) {
        int A;
        cin >> A;
        
        if(i < K) {
            if(A > 0) {
                S++;
                finalValue = A;
            }
            else {
                cout << S << endl;
                return 0;
            }
        }
        else if(A == finalValue) {
            S++;
        }
    }
    
    cout << S;
    return 0;
}
