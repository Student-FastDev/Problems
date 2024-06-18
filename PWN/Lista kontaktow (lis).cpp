#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 1000001;

vector<int> graf[MAX_N];
int odwiedzone[MAX_N];


void dfs(int v, int odw) {
  odwiedzone[v] = odw;
  for(auto i : graf[v]) {
    if(odwiedzone[i] == 0) {
      dfs(i, odw);
    }
  }
}


int main()
{
	int n, m;
  cin >> n >> m;
  
  for(int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    
    graf[a].push_back(b);
    graf[b].push_back(a);
  }
  
  for(int i = 1; i <= n; i++) {
    if(odwiedzone[i] == 0) {
      dfs(i, i);
    }
  }
  
  int z;
  cin >> z;
  for(int i = 0; i < z; i++) {
      int x, y;
      cin >> x >> y;
      if(odwiedzone[x] == odwiedzone[y]) {
          cout << "TAK" << endl;
      }
      else {
          cout << "NIE" << endl;
      }
  }
  
}
