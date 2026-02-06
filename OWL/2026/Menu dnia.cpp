// Catling
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define endl '\n'
#define all(X) X.begin(),X.end()
#define size(X) X.size()

const int MAX_N = 1e5;
const int MOD = 1e9 + 9;
const ll INF = 1e18 + 67;

const int BUFFER_SIZE = 1 << 16;
char buffer[BUFFER_SIZE];
int bufferPosition = 0, bufferLength = 0;

inline char readChar() {
    if (bufferPosition == bufferLength) {
        bufferPosition = 0;
        bufferLength = fread(buffer, 1, BUFFER_SIZE, stdin);
        if (bufferLength == 0) return EOF;
    }
    return buffer[bufferPosition++];
}

inline int readInt() {
    int X = 0;
    char C = readChar();
    bool isNegative = false;
    while (C < '0' || C > '9') {
        if (C == '-') isNegative = true;
        if (C == EOF) return 0;
        C = readChar();
    }
    while (C >= '0' && C <= '9') {
        X = (X << 3) + (X << 1) + (C - '0');
        C = readChar();
    }
    return isNegative ? -X : X;
}

struct BestState {
    ll value;
    int color;
};

void solveTestCase() {
    int N = readInt();
    int M = readInt();

    BestState firstMinimum = {0, 0};
    BestState secondMinimum = {0, 0};

    int A, V;
    ll currentDP;
    for(int i = 0; i < N; i++) {
        A = readInt();
        V = readInt();

        currentDP = V;
        if(A != firstMinimum.color) {
            currentDP += firstMinimum.value;
        } else {
            currentDP += secondMinimum.value;
        }

        if(A == firstMinimum.color) {
            if(currentDP > firstMinimum.value) firstMinimum.value = currentDP;
        } else if(A == secondMinimum.color) {
            if(currentDP > secondMinimum.value) {
                secondMinimum.value = currentDP;
                if(secondMinimum.value > firstMinimum.value) {
                    swap(firstMinimum, secondMinimum);
                }
            }
        } else {
            if(currentDP > firstMinimum.value) {
                secondMinimum = firstMinimum;
                firstMinimum = {currentDP, A};
            } else if(currentDP > secondMinimum.value) {
                secondMinimum = {currentDP, A};
            }
        }
    }

    cout << firstMinimum.value << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T = 1;
    
    while(T--) {
        solveTestCase();
    }
}
