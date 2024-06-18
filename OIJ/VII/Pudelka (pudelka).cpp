#include <iostream>
#include <map>

using namespace std;

map<int,int> countArray;

int main()
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    int maxValue = -1;
    
    
    for(int i = 0; i < N; i++) {
        int A;
        cin >> A;
        
        countArray[A]++;
        
        maxValue = max(maxValue, countArray[A]);
        
    }
    
    cout << maxValue << endl;
    

    return 0;
}
