#include <bits/stdc++.h>
using namespace std;

const int MAXN = 700;
typedef bitset<MAXN> bitsetArray;

vector<bitsetArray> multiplyFunction(const vector<bitsetArray>& A, const vector<bitsetArray>& B) {
    int N = A.size();
    vector<bitsetArray> C(N);
    for (int i = 0; i < N; ++i) {
        bitsetArray row;
        for (int k = 0; k < N; ++k) {
            if (A[i][k]) {
                row ^= B[k];
            }
        }
        C[i] = row;
    }
    return C;
}

vector<bitsetArray> matrixPower(vector<bitsetArray> M, long long power) {
    int N = M.size();
    vector<bitsetArray> result(N);
    for (int i = 0; i < N; ++i) {
        result[i].reset();
        result[i].set(i);
    }
    while (power > 0) {
        if (power % 2 == 1) {
            result = multiplyFunction(result, M);
        }
        M = multiplyFunction(M, M);
        power /= 2;
    }
    return result;
}

string applyFunction(const vector<bitsetArray>& md, const string& S) {
    int N = S.size();
    bitsetArray x;
    for (int i = 0; i < N; ++i) {
        x[i] = (S[i] == '1');
    }
    string resolveArray(N, '0');
    for (int i = 0; i < N; ++i) {
        resolveArray[i] = ((md[i] & x).count() % 2 == 1) ? '1' : '0';
    }
    return resolveArray;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N;
    long long D;
    string S;
    cin >> N >> D >> S;

    if (D == 0) {
        cout << S << endl;
        return 0;
    }

    vector<bitsetArray> M(N);
    for (int i = 0; i < N-1; ++i) {
        M[i].reset();
        M[i].set(i + 1);
    }
    M[N-1].reset();
    M[N-1].set(0);
    M[N-1].set(1);

    auto mArray = matrixPower(M, D);
    string resolveArray = applyFunction(mArray, S);
    cout << resolveArray << endl;
    return 0;
}
