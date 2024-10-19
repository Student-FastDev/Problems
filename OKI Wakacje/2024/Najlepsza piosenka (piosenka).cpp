#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct songVar {
    int views;
    string name;
    int length;
};

class compareSong {
    public:
       bool operator()(songVar first, songVar second){
           if (first.views != second.views){
               return first.views < second.views;
           }
           else if (first.name != second.name) {
               return first.name > second.name;
           }
           else if (first.length != second.length) {
               return first.length < second.length;
           }
           return false;
      }
};

int main()
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0);
    cout.tie(0);
    
    int N;
    cin >> N;
    
    priority_queue<songVar, vector<songVar>, compareSong> songList;
    
    for(int i = 0; i < N; i++) {
        char S;
        cin >> S;
        
        if(S == '+') {
            int tempViews;
            string tempName;
            int tempLength;
            cin >> tempViews >> tempName >> tempLength;
            
            songVar tempSong;
            tempSong.views = tempViews;
            tempSong.name = tempName;
            tempSong.length = tempLength;
            
            songList.push(tempSong);
        }
        else if(S == '?') {
            cout << songList.top().name << " " << songList.top().length << endl;
        }
        else if(S == '-') {
            songList.pop();
        }
    }

    return 0;
}