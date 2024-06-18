#include <iostream>
#include <string> 

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    string liczbaNaturalna;
    cin >> liczbaNaturalna;
    
    int liczbaInt = stoll(liczbaNaturalna);
    
    int liczbaCyfr = liczbaNaturalna.length();
    int cyfraNow = liczbaNaturalna[0];
    int znalezioneCyfry = 0;
    while(znalezioneCyfry < 3) {
        string liczbaPrzyklad = "";
        for(int i = 0; i < liczbaCyfr; i++) {
            liczbaPrzyklad += cyfraNow;
        }
        
        if(stoll(liczbaPrzyklad) > liczbaInt) {
            znalezioneCyfry++;
            cout << liczbaPrzyklad << " ";
        } 
        
        if(cyfraNow == '9') {
            cyfraNow = '1';
            liczbaCyfr++;
        }
        else {
            cyfraNow++;   
        }
    }
}
