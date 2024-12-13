#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

struct Edge {
    int U, V, W, edgeNumber;
    Edge(int u, int v, int w, int edgeNum) : U(u), V(v), W(w), edgeNumber(edgeNum) {}
};

inline void putUI(unsigned int n) {
     if(n==0)
     {
         putc_unlocked(48,stdout);
         return;
     }
 
     char tab[12];
     int p = 0;
     while(n != 0) {
        tab[p++] = (n % 10) + 48;
         n /= 10;
     }
     while(p--) 
         putc_unlocked(tab[p], stdout);
}

inline void readINT(int *n)
{
    register char c = 0, 
    znak_liczby=1;
    while (c < 33) c=getc_unlocked(stdin);
    
    if(c==45) {znak_liczby=-1;  c=getc_unlocked(stdin);}
    (*n) = 0;
    
    while (c>32) {(*n)=(*n)*10 + c-48; c=getc_unlocked(stdin);} 
  
    (*n)*=znak_liczby;
}

const int MAX_N = 1e4+1;
const int MOD = 1e9+7;
vector<pair<int,int>> neighbourList[MAX_N];
vector<int> subtreeSize(MAX_N, 0);
vector<pair<ll, int>> edgeMultiplications;
vector<Edge> edges;
vector<pair<double, int>> differencesArray;

void addEdge(int U, int V, int W, int edgeNumber) {
    neighbourList[U].push_back({V, edgeNumber});
    neighbourList[V].push_back({U, edgeNumber});
    edges.emplace_back(U, V, W, edgeNumber);
}

double calculateDifference(int W, int multiplication, double edgeRatio) {
    double reducedEdge = W / edgeRatio;
    double increasedEdge = W - reducedEdge;

    return multiplication * increasedEdge;
}

int DFS(int node, int parent, int N, double edgeRatio) {
    subtreeSize[node] = 1;
    for (auto &neighbour : neighbourList[node]) {
        int nextNode = neighbour.first;
        int edgeNumber = neighbour.second;
        if (nextNode != parent) {
            subtreeSize[node] += DFS(nextNode, node, N, edgeRatio);
            ll multiplication = (ll)subtreeSize[nextNode] * (N - subtreeSize[nextNode]);
            edgeMultiplications.push_back({multiplication, edgeNumber});
            double difference = calculateDifference(edges[edgeNumber-1].W, multiplication, edgeRatio);
            differencesArray.push_back({difference, edgeNumber});
        }
    }
    return subtreeSize[node];
}

int main() {
    int N, K, P, S;
    readINT(&N);
    readINT(&K);
    readINT(&P);
    readINT(&S);

    double edgeRatio = (double)S / P;

    if (N <= 0 || N >= MAX_N) {
        return 1;
    }

    for(int i = 0; i < N-1; i++) {
        int A, B, C;
        readINT(&A);
        readINT(&B);
        readINT(&C);
        A--; B--;
        addEdge(A, B, C, i+1);
    }

    edgeMultiplications.reserve(N - 1);
    differencesArray.reserve(N - 1);
    DFS(0, -1, N, edgeRatio);

    sort(differencesArray.rbegin(), differencesArray.rend());

    for (int i = 0; i < K && i < differencesArray.size(); i++) {
        putUI(differencesArray[i].second);
        putc_unlocked(' ', stdout);
    }

    return 0;
}
