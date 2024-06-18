#include <iostream>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    int numbersArray[N];
    for (int i = 0; i < N; i++) {
        cin >> numbersArray[i];
    }

    int outputArray[2][N+1] = {0};

    for(int j = 1; j < N; j++) {
        outputArray[0][j] = j;
    }
    for(int i = 1; i <= K; i++) {
        for(int j = 0; j < N; j++) {
            outputArray[i % 2][j] = outputArray[(i-1) % 2][j];
        }
        for(int j = 0; j < N; j++) {
            if(numbersArray[j] > -1) {
                outputArray[i % 2][numbersArray[j]] = min(outputArray[i % 2][numbersArray[j]], outputArray[(i-1) % 2][j] + 1);
            }
        }
        for(int j = 1; j < N; j++) {
            outputArray[i % 2][j] = min(outputArray[i % 2][j], outputArray[i % 2][j-1] + 1);
        }
    }

    cout << outputArray[K % 2][N-1];
    return 0;
}
