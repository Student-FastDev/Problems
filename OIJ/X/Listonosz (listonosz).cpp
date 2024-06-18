#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);


    long long N, M;
    cin >> N >> M;
    
    vector<pair<long long,long long>> citiesArray(N);
    vector<long long> listArray(M);
    
    long long distance = 0;
    
    for(long long i = 0; i < N; i++) {
        long long A, B;
        cin >> A >> B;
        citiesArray[i] = make_pair(A, B);
    }
    
    for(long long i = 0; i < M; i++) {
        long long A;
        cin >> A;
        
        listArray[i] = A - 1;
    }
    
    for(long long i = 0; i < M-1; i++) {
        distance += abs(citiesArray[listArray[i]].first - citiesArray[listArray[i+1]].first) + 
                    abs(citiesArray[listArray[i]].second - citiesArray[listArray[i+1]].second);
    }
    
    distance += abs(citiesArray[listArray[M-1]].first - citiesArray[listArray[0]].first) + 
                 abs(citiesArray[listArray[M-1]].second - citiesArray[listArray[0]].second);

    cout << distance << endl;

    return 0;
}
