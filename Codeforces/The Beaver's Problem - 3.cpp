// Catling
#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
auto operator<<(auto&o,auto p)->decltype(p.first,o){return o<<'('<<p.first<<", "<<p.second <<')';}
auto operator<<(auto&o,auto x)->decltype(x.end(),o){o<<'{';int i=2;for(auto e:x)o<<(", ")+i<<e,i=0;return o<<'}';}
#define LOG(x...)cerr<<"["#x"]: ",[](auto...$){((cerr<<$<<"; "),...)<<endl;}(x);
#else
#define LOG(x...)(void)0
#endif

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#define all(x)  (x).begin(),(x).end()
#define endl    '\n'
#define size(x)  x.size()

const ll INF = 9223372036854775806;
const ll MAX_N = 1e9+1;
const ll MOD = 1e9+7; 

unordered_map<string, vector<int>> dictionary;

string k1 = "algorithm app application array backup bandwidth binary bit bitmap block blog bluetooth boolean boot bot broadband browser buffer bug bus byte cache chip class client cloud code coding command compile compiler compression compute computer computing config configure connect connection console constant constructor cookie core cpu crash crypto cyber data database debug debugger decimal decode decrypt default define delete demo design desktop developer device digital directory disk display dns document domain download drive driver dump dynamic email encode encryption engine error ethernet exception execute exploit export extension external fail failure feed field file firewall firmware flash float floppy folder font format framework freeware function gateway gigabyte git gpu graphic gui hack hacker hardware hash heap hex host hosting html http hypervisor icon ide image import index info infrastructure input install instance instruction integer interface internet interpreter io ip java javascript kernel keyboard keyword lan language laptop latency library link linux list load localhost log logic login loop machine macro mail mainframe malware map mask matrix media megabyte memory menu meta method microchip microsoft middleware modem module monitor motherboard mouse multimedia namespace native net network node null object offline online opcode open source operand operator optimize option oracle os output overflow overload packet page panel parallel parameter parity parse password patch path pattern pc performance peripheral perl permission php pixel platform pointer polymorphism port portal power procedure process processor program programmer programming protocol proxy python query queue ram random read reboot record recursion register release remote render repository request resolution resource restore root router routine routing runtime safety save scalar scanner schedule schema scope screen script scroll scsi sdk search secure security segment select semantic semaphore serial server service servlet session set shareware shell shift short shutdown signal signature silicon simulation site size socket software solution sort source spam spec specification spider spool sql ssl stack standard state statement static status storage stream string struct structure subroutine subscription supercomputer support surf switch symbol sync syntax sysadmin system table tag tape task tcp tech technology telnet template terminal test text thread throughput token tool topology trace traffic transaction transfer translation tree trigger trojan type ui unix update upgrade upload uri url usb user utility validation value variable vector version video view virtual virus visual void volati volume vpn wan web website wifi window windows wireless wizard word workstation write www xml zip";

string k2 = "abs acceleration accessory accident aerodynamic airbag alarm alloy alternator ambulance auto automobile automotive axle battery bearing belt bench bentley benz bike body bolt bonnet brake brand breakdown bumper bus cab cabin cadillac caliper camshaft car carburetor chassis chauffeur chevrolet chrome clutch cockpit combustion component convertible cooler coupe crank crankshaft crash cruise cylinder damper dashboard dealer dealership diesel differential door drag drift drive driver driving dumper dust dynamo electric emission engine exhaust fast fender ferrari fiat filter ford formula fuel garage gas gasoline gauge gear gearbox gearstick grille grip handle hatchback headlight highway honda hood horn horsepower hose hybrid hyundai ignition indicator industry inflate insurance jaguar jeep kit labor lamborghini lane lever lexus license lift light limousine litre lorry lube lubricant luxury machine maintenance make manifold manual mazda mechanic mechanical mechanism mercedes metal meter mileage mirror mitsubishi mobile model motor motorbike motorcycle motorsport muffler nissan noise nut octane odometer oil opel overtake pad paint panel parking passenger pedal petrol peugeot piston plug porsche power pressure pump puncture race racing radiator rally range rear reflector renault rental repair rev reverse ride rim road roadster rolls royce rover rpm rubber safety saloon seat sedan sensor service shaft shift shock show skid speed speedometer speedway spoiler sport sprint start station steer steering stop street subaru supercar supercharger suspension suzuki switch tachometer tank taxi test throttle tire torque toyota track traction tractor traffic transmission transport trip truck trunk tube tune tunnel turbo turn tyre unit upholster valve van vehicle vent volkswagen volvo wagon wash wax wheel winch windshield wing wiper workshop yamaha zone";

string k3 = "accounting acquisition advantage advertise agent agreement amortize analyze annual arbitrage asset atm auction audit balance bank bankruptcy bargain barter bear benchmark benefit bid bill board bond bonus boom borrow boss brand broker budget bull business buy buyer capital cash central ceo charge chart cheap check commerce commercial commission commodity company compensation competition competitor conglomerate consumer consumption contract corporation cost coupon credit crisis currency current customer cut cycle data deal dealer debt debtor decision deficit deflation delivery demand deposit depreciation depression derivative discount distribution dividend dollar domestic dow downturn due duty earn earnings economic economics economy efficiency elastic employee employer enterprise entrepreneur equity estate estimate euro exchange executive expense expensive export factor factory fall fee figure finance financial firm fiscal fixed fluctuation forecast foreign fortune forum franchise fund future gain gdp global goal gold goods graph gross growth hedge high hire holding house import incentive income index indicator industrial industry inflation infrastructure innovation institution insurance interest inventory invest investment investor invoice job labor law lease ledger legal liability license liquidity loan logistics loss low macro management manager margin market marketing maturity merchandise merger micro money monopoly mortgage nafta nasdaq negotiation net niche note offer office offset offshore operation opportunity option order organization output outsource overhead owner partner pay payment payroll pension percent percentage performance period plan policy portfolio position poverty price private product production profession profit promotion property proposal prosperity protect public purchase purchasing quality quota quote rally rate ratio real recession recommendation recovery recruit refund regulation rent report reserve resource retail retire return revenue rich rise risk salary sale sales save saving scarcity sector secure security sell service share shareholder shortage slump speculation spending stability stake standard statistics stock store strategy strike structure subsidy success sum supply surplus swap target tariff tax team term thrift ticker trade trader trading transaction transfer treasury trend turnover unemployment union unit utility valuation value vat venture wage wall wealth welfare wholesale worker world yield zone";

void buildDictionary() {
    auto process = [&](string& s, int idx) {
        stringstream ss(s);
        string word;
        while(ss >> word) {
            if(dictionary.find(word) == dictionary.end()) {
                dictionary[word].resize(4, 0);
            }
            dictionary[word][idx]++;
        }
    };
    process(k1, 1);
    process(k2, 2);
    process(k3, 3);
}

void solveTestCase() {
    int id;
    if(!(cin >> id)) return;
    string dummy; 
    getline(cin, dummy); 
    
    string name;
    getline(cin, name);
    
    string text;
    string line;
    while(getline(cin, line)) {
        text += line + " ";
    }
    
    for(char &c : name) if(!isalpha(c)) c = ' '; else c = tolower(c);
    for(char &c : text) if(!isalpha(c)) c = ' '; else c = tolower(c);
    
    vector<double> scores(4, 0.0);
    
    auto analyze = [&](const string& s, double weight) {
        stringstream ss(s);
        string word;
        while(ss >> word) {
            if(dictionary.count(word)) {
                for(int i = 1; i <= 3; ++i) {
                    if(dictionary[word][i] > 0) scores[i] += weight;
                }
            } else {
                if(size(word) > 3 && word.back() == 's') {
                    string sub = word.substr(0, size(word) - 1);
                    if(dictionary.count(sub)) {
                        for(int i = 1; i <= 3; ++i) {
                             if(dictionary[sub][i] > 0) scores[i] += weight;
                        }
                    }
                }
            }
        }
    };
    
    analyze(name, 5.0); // Give more weight to title
    analyze(text, 1.0);
    
    int best = 1;
    if(scores[2] > scores[best]) best = 2;
    if(scores[3] > scores[best]) best = 3;
    
    cout << best << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    buildDictionary();

    int T = 1;
    // cin >> T; 

    while(T--) {
        solveTestCase();
    }
    return 0;
}