#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct passagerVar {
    string country;
    int classNum;
    string surname;
    string name;
};


bool customComparator(const passagerVar &first, const passagerVar &second) {
    if (first.country > second.country) {
        return true;
    } else if (first.country < second.country) {
        return false;
    } else if (first.classNum < second.classNum) {
        return true;
    } else if (first.classNum > second.classNum) {
        return false;
    } else if (first.surname < second.surname) {
        return true;
    } else if (first.surname > second.surname) {
        return false;
    } else if (first.name > second.name) {
        return true;
    } else if (first.name < second.name) {
        return false;
    }
    return false;
}




int main()
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    
    int N;
    cin >> N;
    
    vector<passagerVar> passagerList;
    
    for(int i = 0; i < N; i++) {
        string countryTemp;
        int classNumTemp;
        string surnameTemp;
        string nameTemp;
        
        cin >> countryTemp >> classNumTemp >> surnameTemp >> nameTemp;
        
        passagerVar passagerTemp;
        passagerTemp.country = countryTemp;
        passagerTemp.classNum = classNumTemp;
        passagerTemp.surname = surnameTemp;
        passagerTemp.name = nameTemp;
        
        passagerList.push_back(passagerTemp);
    }
    
    sort(passagerList.begin(), passagerList.end(), customComparator);
    
    for(int i = 0; i < N; i++) {
        cout << passagerList[i].country << " " << passagerList[i].classNum << " " << passagerList[i].surname << " " << passagerList[i].name << endl;
    }

    return 0;
}