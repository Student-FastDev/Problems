#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int M, P, N;
    cin >> M >> P >> N;
    vector<vector<int>> snackArray(M + 1, vector<int>(M + 1, -1));
    for(int i = 0; i < P; i++){
        int W, K, C;
        cin >> W >> K >> C;
        snackArray[W][K] = C;
    }
 
    vector<vector<int>> whereArray(M + 1, vector<int>(M + 1, -1));
 
    deque<pair<int,int>> snakeArray;
    vector<int> colorsArray;
 
    int moveVariable = 0;
    snakeArray.push_back({1,1});
    colorsArray.push_back(0);
    whereArray[1][1] = ++moveVariable;
 
    for (int i = 0; i < N; i++){
        char commandType;
        cin >> commandType;
        if(commandType=='G' || commandType=='D' || commandType=='L' || commandType=='P'){
            pair<int, int> headValue = snakeArray.back();
            int Nr = headValue.first, Nc = headValue.second;
            if(commandType=='G') Nr--;
            else if (commandType=='D') Nr++;
            else if (commandType=='L') Nc--;
            else if (commandType=='P') Nc++;
 
            snakeArray.push_back({Nr, Nc});
            if(snackArray[Nr][Nc] != -1){
                colorsArray.push_back(snackArray[Nr][Nc]);
                snackArray[Nr][Nc] = -1;
            } else {
                pair<int, int> tail = snakeArray.front();
                snakeArray.pop_front();
                whereArray[tail.first][tail.second] = -1;
            }
            whereArray[Nr][Nc] = ++moveVariable;
        }
        else if(commandType=='Z'){
            int W, K;
            cin >> W >> K;
            if(whereArray[W][K] == -1){
                cout << -1 << "\n";
            } else {
                int differenceValue = moveVariable - whereArray[W][K];
                int indexValue = (int) colorsArray.size() - 1 - differenceValue;
                cout << colorsArray[indexValue] << "\n";
            }
        }
    }
 
    return 0;
}
