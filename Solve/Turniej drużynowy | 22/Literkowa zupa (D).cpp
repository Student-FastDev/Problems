#include <bits/stdc++.h>
#define ll long long;

const int MAXN = 1e9+7;
const int MOD = 1e9+7; 

using namespace std;

string a;
char zupa[3][3];
bool wynik = false;

int takCzyNie(vector<vector<bool>> v, int i, int x, int y)
{
    if(i == 8)
    {
        wynik = true;
        return 0;
    }
    if(x != 2)
    {
        if(zupa[x+1][y] == a[i+1] && v[x+1][y] == false)
        {;
            v[x+1][y] == true;
            takCzyNie(v, i+1, x+1, y);
        }
    }

    if(y != 2)
    {
        if(zupa[x][y+1] == a[i+1] && v[x][y+1] == false)
        {
            v[x][y+1] == true;
            takCzyNie(v, i+1, x, y + 1);
        }
    }

    if(y != 0)
    {
        if(zupa[x][y-1] == a[i+1] && v[x][y-1] == false)
        {
            v[x][y-1] == true;
            takCzyNie(v, i+1, x, y - 1);
        }
    }

    if(x != 0)
    {
        if(zupa[x-1][y] == a[i+1] && v[x-1][y] == false)
        {
            v[x-1][y] == true;
            takCzyNie(v, i+1, x-1, y);
        }
    }
    return 0;   
}

int main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> a;
    
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 3; x++)
        {
            cin >> zupa[x][y];
        }
    }

    if(zupa[0][0] != a[0])
    {
        cout << "NIE";
        return 0;
    }

    vector<vector<bool>> v(3, vector<bool>(3, false));

    takCzyNie(v, 0, 0, 0);

    if(wynik == true)
        cout << "TAK";
    else
        cout << "NIE";
}