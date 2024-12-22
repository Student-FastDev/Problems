#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
 
int main()
{
    int N;
    cin >> N;
    
    int A = 0;
    for(int i = 0; i < N; i++) {
        string S;
        cin >> S;
        
        int L = S.length();
        int plusAmount = 0;
        int minusAmount = 0;
        for(int i = 0; i < L; i++) {
            if(S[i] == '+') {
                plusAmount++;
            }
            else if(S[i] == '-') {
                minusAmount++;
            }
        }
        
        if(plusAmount == 2) {
            A++;
        }
        else if(minusAmount == 2) {
            A--;
        }
    }
    
    cout << A << endl;
    
    return 0;
}
