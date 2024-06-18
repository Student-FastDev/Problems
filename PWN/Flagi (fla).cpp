#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;
    
    int M[N];
    bool flagIndex[N] = {false};
    
    for(int i = 0; i < N; i++) {
        int tempNumber;
        cin >> tempNumber;
        M[i] = tempNumber;
    }
    
    for(int i = 1; i < N-1; i++) {
        if(M[i] > max(M[i-1], M[i+1])) {
            flagIndex[i] = true;
        }
    }
    
    int nextArray[N] = {-1};
    nextArray[N-1] = -1;
    
    for(int i = N - 2; i >= 0; i--) {
        if(flagIndex[i]) {
            nextArray[i] = i;
        } else {
            nextArray[i] = nextArray[i+1];
        }
    }
    
    int scoreValue = 0;
    for(int i = 1; i * i <= N; i++) {
        int nowPosition = 0;
        int counterValue = 0;
        while(nowPosition < N && counterValue < i) {
            nowPosition = nextArray[nowPosition];
            if(nowPosition == -1) {
                break;
            }
            counterValue++;
            nowPosition += i;
        }
        scoreValue = max(scoreValue, counterValue);
    }
    
    cout << scoreValue;

    return 0;
}
