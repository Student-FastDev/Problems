#include <bits/stdc++.h>
using namespace std;

bool compareItems(int a, int b) {
    return a > b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int height, width, numItems, status = 2;
    double P = 18.3575575068582;
    cin >> height >> width >> numItems;
    
    double itemsArray[numItems];
    for (int i = 0; i < numItems; i++) {
        cin >> itemsArray[i];
    }
    
    sort(itemsArray, itemsArray + numItems, compareItems);
    
    for (int i = 0; i < numItems; i++) {
        itemsArray[i] = (itemsArray[i] * 2.54) / P;
        
        if (itemsArray[i] * 9 <= height && itemsArray[i] * 16 <= width) {
            cout << (itemsArray[i] / 2.54) * P;
            status = 1;
            return 0;
        }
    }
    
    if (status == 2) {
        cout << "NIE";
    }
    return 0;
}
