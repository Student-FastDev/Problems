// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;

pii validConfigurations[43];

void precomputeConfigurations() {
    for(int i = 0; i <= 42; ++i) validConfigurations[i] = {-1, -1};
    for(int countSeven = 0; countSeven <= 6; ++countSeven) {
        for(int countFour = 0; countFour + countSeven <= 6; ++countFour) {
            int currentSum = countFour * 4 + countSeven * 7;
            validConfigurations[currentSum] = {countFour, countSeven};
        }
    }
}

string stringN;
vector<int> digitsOfN;
int memoizationTable[25][10];
pii reconstructionPath[25][10];

bool findSolution(int index, int carry) {
    if (index == (int)size(digitsOfN)) {
        return carry == 0;
    }
    if (memoizationTable[index][carry] != -1) return memoizationTable[index][carry];

    bool isPossible = false;
    for(int nextCarry = 0; nextCarry <= 4; ++nextCarry) {
        int neededSum = digitsOfN[index] + 10 * nextCarry - carry;
        
        if (neededSum >= 0 && neededSum <= 42 && validConfigurations[neededSum].first != -1) {
            if (findSolution(index + 1, nextCarry)) {
                reconstructionPath[index][carry] = validConfigurations[neededSum];
                isPossible = true;
                break; 
            }
        }
    }
    return memoizationTable[index][carry] = isPossible;
}

void solveTestCase() {
    cin >> stringN;
    digitsOfN.clear();
    for(int i = (int)size(stringN) - 1; i >= 0; --i) {
        digitsOfN.push_back(stringN[i] - '0');
    }

    for(int i = 0; i <= (int)size(digitsOfN); ++i) {
        for(int j = 0; j < 10; ++j) memoizationTable[i][j] = -1;
    }

    if (findSolution(0, 0)) {
        vector<string> answerStrings(6, "");
        int carry = 0;
        for(int i = 0; i < (int)size(digitsOfN); ++i) {
            auto countsPair = reconstructionPath[i][carry];
            int countFour = countsPair.first;
            int countSeven = countsPair.second;
            int countZero = 6 - countFour - countSeven;
            
            int numberIndex = 0;
            for(int k = 0; k < countFour; ++k) answerStrings[numberIndex++] += '4';
            for(int k = 0; k < countSeven; ++k) answerStrings[numberIndex++] += '7';
            for(int k = 0; k < countZero; ++k) answerStrings[numberIndex++] += '0';

            int currentSum = countFour * 4 + countSeven * 7;
            carry = (currentSum + carry) / 10;
        }

        for(int i = 0; i < 6; ++i) {
            reverse(all(answerStrings[i]));
            string outputString = "";
            bool isLeading = true;
            for(char c : answerStrings[i]) {
                if (c != '0') isLeading = false;
                if (!isLeading) outputString += c;
            }
            if (outputString == "") outputString = "0";
            cout << outputString << (i == 5 ? "" : " ");
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    precomputeConfigurations();
    int T;
    cin >> T;
    while(T--) {
        solveTestCase();
    }
    return 0;
}