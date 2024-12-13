#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const int MOD = 1e9+7;

inline void readINT(int *N)
{
    register char C = 0, 
    numberCharacter = 1;
    while (C < 33) {
        C = getc_unlocked(stdin);
    }

    if(C == 45) {
        numberCharacter =- 1;  C=getc_unlocked(stdin);
    }
    (*N) = 0;
    
    while (C > 32) {
        (*N) = (*N)*10 + C-48; C=getc_unlocked(stdin);
    } 
    (*N)*=numberCharacter;
} 

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, L;

    readINT(&N);
    vector<int> A(N + 1);
    for(int i = 1; i <= N; i++) {
        readINT(&A[i]);
    }

    readINT(&M);
    vector<int> B(M + 1);
    for(int i = 1; i <= M; i++) {
        readINT(&B[i]);
    }

    readINT(&L);
    vector<int> C(L + 1);
    for(int i = 1; i <= L; i++) {
        readINT(&C[i]);
    }

    vector<vector<int>> helperArray(N + 1, vector<int>(L + 1));
    vector<int> aPrefixFitting(N + 1), bPrefixFitting(M + 1);

    for(int i = 0; i <= N; i++)
        helperArray[i][0] = -1;
    for(int j = 0; j <= L; j++)
        helperArray[0][j] = -1;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= L; j++) {
            if(A[i] == C[j])
                helperArray[i][j] = (j > 1 ? helperArray[i-1][j-1] : i);
            else
                helperArray[i][j] = helperArray[i-1][j];
        }
        aPrefixFitting[i] = helperArray[i][L];
    }

    helperArray.assign(M + 1, vector<int>(L + 1));
    for(int i = 0; i <= M; i++)
        helperArray[i][0] = -1;
    for(int j = 0; j <= L; j++)
        helperArray[0][j] = -1;

    for(int i = 1; i <= M; i++) {
        for(int j = 1; j <= L; j++) {
            if(B[i] == C[j])
                helperArray[i][j] = (j > 1 ? helperArray[i-1][j-1] : i);
            else
                helperArray[i][j] = helperArray[i-1][j];
        }
        bPrefixFitting[i] = helperArray[i][L];
    }

    vector<vector<int>> LCS(N + 1, vector<int>(M + 1)), reverseLCS(N + 2, vector<int>(M + 2));
    
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(A[i] == B[j])
                LCS[i][j] = LCS[i-1][j-1] + 1;
            else
                LCS[i][j] = max(LCS[i-1][j], LCS[i][j-1]);
        }
    }

    for(int i = N; i > 0; i--) {
        for(int j = M; j > 0; j--) {
            if(A[i] == B[j])
                reverseLCS[i][j] = reverseLCS[i+1][j+1] + 1;
            else
                reverseLCS[i][j] = max(reverseLCS[i+1][j], reverseLCS[i][j+1]);
        }
    }

    int resultValue = -1;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(aPrefixFitting[i] != -1 && bPrefixFitting[j] != -1) {
                int compareValue = LCS[aPrefixFitting[i]-1][bPrefixFitting[j]-1] + reverseLCS[i+1][j+1] + L;
                resultValue = max(resultValue, compareValue);
            }
        }
    }

    if (L) {
        cout << resultValue << endl;
    } else {
        cout << LCS[N][M] << endl;
    }
    return 0;
}
