#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int N, P;
    cin >> N >> P;
    
    int valueArray[N];
    int divisionArray[N];
    
    for(int i = 0; i < N; i++) {
        cin >> valueArray[i];
        
        divisionArray[i] = valueArray[i] % P;
    }
    
    sort(divisionArray, divisionArray + N);
    
    int perfectPicks = 0;
    
    if(divisionArray[0] != divisionArray[1]) {
        perfectPicks++;
    }
    
    if(divisionArray[N-2] != divisionArray[N-1]) {
        perfectPicks++;
    }
    
    for(int i = 1; i < N-1; i++) {
        if(divisionArray[i] != divisionArray[i-1] && divisionArray[i] != divisionArray[i+1]) {
            perfectPicks++;
        }
    }
    
    cout << perfectPicks;
    return 0;
}
