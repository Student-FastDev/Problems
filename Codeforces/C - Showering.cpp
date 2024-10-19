#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
int main()
{
    int T;
    cin >> T;
    
    for(int i = 0; i < T; i++) {
        int N, S, M;
        cin >> N >> S >> M;
        
        bool isPossible = false;
        int lastInterval = 0;
        for(int i = 0; i < N; i++) {
            int A, B;
            cin >> A >> B;
            
            if(A - lastInterval >= S) {
                isPossible = true;
            }
            lastInterval = B;
        }
        
        if(M - lastInterval >= S) {
            isPossible = true;
        }
        
        if(isPossible) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
 
    return 0;
}
