#include <iostream>
using namespace std;

int fibSeq(int N) {
    if (N == 1)
        return 1;
    else if (N == 2)
        return 2;
    
    int a = 1, b = 2;
    for (int i = 3; i <= N; i++) {
        int temp = b;
        b = (a + b) % 10;
        a = temp;
    }
    return b;
}

int findLastDigit(int n) {
    int f[60] = {0};
    for(int i = 1; i < 60; i++) {
        f[i] = fibSeq(i) % 10;
    }
    return f[n % 60];
}

int main() {
    int N;
    cin >> N;
    cout << (findLastDigit(N) + findLastDigit(N - 2)) % 10;
    return 0;
}
