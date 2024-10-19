#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
 
int main()
{
    long long N, M, A;
    cin >> N >> M >> A;
    
    long long heightValue = 0;
    if(N % A != 0) {
        heightValue = (N / A) + 1;   
    }
    else {
        heightValue = N / A;
    }
    
    long long widthValue = 0;
    if(M % A != 0) {
        widthValue = (M / A) + 1;   
    }
    else {
        widthValue = M / A;
    }
 
    cout << heightValue * widthValue << endl;
    return 0;
}
