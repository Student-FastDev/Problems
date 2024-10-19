#include <bits/stdc++.h>
#include <iterator>
#include <vector>

using namespace std;

int findArea(int A) {
    int minimumNumberSum = 1e9 + 1;

    for(int i = 1; i * i <= A; i++) {
        if(A % i == 0) {
            int divisorNumber = i;
            int secondDivisorNumber = A/i;
            
            int numberSum = 2*divisorNumber + 2*secondDivisorNumber;

            if(numberSum < minimumNumberSum) {
                minimumNumberSum = numberSum;
            } 
        }
    }
    
    return minimumNumberSum;
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    int P;
    cin >> P;

    int scoreNumbers = findArea(P);
    cout << scoreNumbers << endl;
    return 0;
}
