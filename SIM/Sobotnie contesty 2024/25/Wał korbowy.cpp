#include <iostream>
using namespace std;

int main() {
	int N, A, B;
	cin >> N >> A >> B;
	
	int sumAmount = A + B;
	int finalScore = -1;
	
	for(int i = 0; i < N; i++) {
		int tempNumber;
		cin >> tempNumber;
		
		if(tempNumber == sumAmount) {
			finalScore = i;
		} 
	}
	
	cout << finalScore+1 << endl;
	
	
	return 0;
}