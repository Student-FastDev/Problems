#include <iostream>
using namespace std;

bool canWin(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'P') return true;
        if (board[i][0] == 'X' && board[i][1] == 'P' && board[i][2] == 'X') return true;
        if (board[i][0] == 'P' && board[i][1] == 'X' && board[i][2] == 'X') return true;
        
        if (board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'P') return true;
        if (board[0][i] == 'X' && board[1][i] == 'P' && board[2][i] == 'X') return true;
        if (board[0][i] == 'P' && board[1][i] == 'X' && board[2][i] == 'X') return true;
    }
    if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'P') return true;
    if (board[0][0] == 'X' && board[1][1] == 'P' && board[2][2] == 'X') return true;
    if (board[0][0] == 'P' && board[1][1] == 'X' && board[2][2] == 'X') return true;
    
    if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'P') return true;
    if (board[0][2] == 'X' && board[1][1] == 'P' && board[2][0] == 'X') return true;
    if (board[0][2] == 'P' && board[1][1] == 'X' && board[2][0] == 'X') return true;
    
    return false;
}

int main() {
    char board[3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> board[i][j];
        }
    }
    
    if (canWin(board)) {
        cout << "TAK" << endl;
    } else {
        cout << "NIE" << endl;
    }
    
    return 0;
}