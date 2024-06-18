// Gasienica / Sliding Window Technique

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    string S;
    int K;
    cin >> S >> K;

    vector<int> ciezarowkiArray;

    for(int i = 0; i < S.length(); i++) {
        if(S[i] == 'X') {
            ciezarowkiArray.push_back(i);
        }
    }

    double minPath = 200001;

    int endIndex = K-1;
    int startIndex = 0;

    int ciezarowkiAmount = ciezarowkiArray.size();

    while(endIndex < ciezarowkiAmount) {
        double pathTime = ((double(ciezarowkiArray[startIndex]+ciezarowkiArray[endIndex]) / 2)) - double(ciezarowkiArray[startIndex]);
        minPath = min(minPath, pathTime);
        endIndex++;
        startIndex++;
    }

    cout << minPath;


    return 0;
}
