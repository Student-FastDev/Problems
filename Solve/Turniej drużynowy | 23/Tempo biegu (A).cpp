#include <bits/stdc++.h>

using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    float a;
    int m, s;
    
    cin >> a;
    
    m = 60 / a;
    s = int(3600 / a) % 60;
    
    if(m < 10)
        cout << 0;
        
    cout << m << ':';
    
    if(s < 10)
    cout << 0;
    cout << s;
    
}