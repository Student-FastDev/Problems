#include <bits/stdc++.h>
#include <iostream>
 
using namespace std;
 
int main()
{
    int N;
    cin >> N;
    
    int scoreValue = 0;
    for(int i = 0; i < N; i++) {
        int A, B, C;
        cin >> A >> B >> C;
        
        int nowValue = 0;
        if(A == 1) {
            nowValue++;
        }
        if(B == 1) {
            nowValue++;
        }
        if(C == 1) {
            nowValue++;
        }
        
        if(nowValue >= 2) {
            scoreValue++;
        }
    }
    
    cout << scoreValue << endl;
 
    return 0;
}
