#include <iostream>
#include <map>

using namespace std;

map<int,int> cardArray;

int main()
{
    int N;
    cin >> N;
    
    for(int i = 0; i < N; i++) {
        int A;
        cin >> A;
        
        cardArray[A]++;
    }
    
    int minAmount = 1000000000;
    int finalValue = 0;

    for(int i = 0; i < 1000001; i++) {
        if(cardArray[i] > 0) {
            minAmount = min(minAmount, cardArray[i]);
            minAmount--;
            finalValue = i+1;
            if(minAmount == 0){
                break;
            }
        }
        else {
            break;
        }
    }
    
    cout << finalValue+1 << endl;
    return 0;
}
