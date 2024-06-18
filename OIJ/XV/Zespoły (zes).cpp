#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
        
    int N;
    cin >> N;
    
    vector<int> personList;
    
    for(int i = 0; i < N; i++) {
        int placeholderPerson;
        cin >> placeholderPerson;
        personList.push_back(placeholderPerson);
    }
    
    sort(personList.begin(), personList.end());
    
    int groupAmount = 0;
    for(int i = 0; i < N-2; i++) {
        if(personList[i+2] - personList[i] <= 1) {
            groupAmount++;
            i += 2;
            
        }
    }
    cout << groupAmount;

    return 0;
}
