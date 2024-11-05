#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    
    string  S;
    cin >> S;
    
    string firstText = "";
    string secondText = "";
    string thirdText = "";
    
    int nowNumber = 0;
    for(int i = 0; i < S.length(); i++) {
        if(i == nowNumber) {
            firstText += S[i];
            nowNumber += 4;
        }
        else {
            firstText += '.';
        }
    }
    
    nowNumber = 1;
    for(int i = 0; i < S.length(); i++) {
        if(i == nowNumber) {
            secondText += S[i];
            nowNumber += 2;
        }
        else {
            secondText += '.';
        }
    }
    
    nowNumber = 2;
    for(int i = 0; i < S.length(); i++) {
        if(i == nowNumber) {
            thirdText += S[i];
            nowNumber += 4;
        }
        else {
            thirdText += '.';
        }
    }
    
    cout << firstText << endl;
    cout << secondText << endl;
    cout << thirdText << endl;
    
    return 0;
}
