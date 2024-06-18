using namespace std;
#include <iostream>

int NWD(int a, int b) {
    int pom;
	while(b!=0) {
		pom = b;
		b = a%b;
		a = pom;	
	}
    return a;
}


int main()
{
    int N;
    cin >> N;
    
    for(int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        
        while(NWD(a, b) != 1) {
            a = a / NWD(a, b);
        }
        
        int score = (a == 1);
        
        if(score) {
            cout << "TAK" << endl;
        }
        else {
            cout << "NIE" << endl;
        }
    }

    return 0;
}
