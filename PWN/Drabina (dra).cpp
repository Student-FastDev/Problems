#include <iostream>

using namespace std;

int main()
{
    int z;
    cin >> z;
    
    int pt[31];
    pt[0] = 1;
    for(int i = 1; i <= 30; i++) {
        pt[i] = pt[i-1] * 2;
    }
    
    int f[1000000];
    f[0] = 1;
    f[1] = 1;
    
    for(int i = 2; i <= 1000000; i++){
        f[i] = (f[i-1] + f[i-2]) % pt[30];
    }
    
    for(int i = 0; i < z; i++) {
        int s, p;
        cin >> s >> p;
        
        cout << f[s] % pt[p] << endl;
    }
    return 0;
}
