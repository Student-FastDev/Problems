#include <iostream>
using namespace std;

long long countEven(long long A, long long B) {
    return (B / 2) - ((A - 1) / 2);
}

long long maxDeletedElements(long long A, long long B) {
    long long evenNumbers = countEven(A, B);
    
    long long unEvenNumbers = (B - A + 1) - evenNumbers;

    return (evenNumbers / 2) * 2 + (unEvenNumbers / 2) * 2;
}

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    long long A, B;
    cin >> A >> B;

    cout << maxDeletedElements(A, B) << endl;

    return 0;
}
