#include <iostream>
#include <string>
#include <ctime>

using namespace std;

string getDayOfWeek(int year) {
    if (year < 2010) {
        return "Tak dawno to dinozaury chodzily po ziemi!";
    } else if (year > 2030) {
        return "To zbyt daleka przyszlosc!";
    } else {
        tm time_in = { 0, 0, 0, 1, 5, year - 1900 };
        mktime(&time_in);
        switch (time_in.tm_wday) {
            case 0: return "niedziela";
            case 1: return "poniedzialek";
            case 2: return "wtorek";
            case 3: return "sroda";
            case 4: return "czwartek";
            case 5: return "piatek";
            case 6: return "sobota";
            default: return "Error!";
        }
    }
}

int main() {
    int year;
    cin >> year;
    cout << getDayOfWeek(year) << endl;
    return 0;
}