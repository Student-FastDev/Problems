#include <iostream>

using namespace std;

const int MAX_N = 46;
long long dpFib[MAX_N];

int main()
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    int N;
    cin >> N;
    
    dpFib[1] = 1;
    
    for(int i = 2; i < N; i++) {
        dpFib[i] = dpFib[i-1] + dpFib[i-2];
    }
    
    for(int i = 0; i < N; i++) {
        cout << dpFib[i] << " ";
    }
    cout << endl;

    return 0;
}