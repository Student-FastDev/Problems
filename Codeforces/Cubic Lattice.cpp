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
const ll MOD = 1e9+7; // 998244353

typedef __int128_t int128;

ll mul(ll a, ll b, ll m) {
    return (ll)((int128)a * b % m);
}

ll power(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = mul(res, base, mod);
        base = mul(base, base, mod);
        exp >>= 1;
    }
    return res;
}

bool millerRabin(ll n, int iterations=5) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (int i = 0; i < iterations; i++) {
        ll a = 2 + rng() % (n - 3);
        ll x = power(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mul(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

ll pollardRho(ll n) {
    if (n == 1) return 1;
    if (n % 2 == 0) return 2;
    ll x = 2 + rng() % (n - 2);
    ll y = x;
    ll c = 1 + rng() % (n - 1);
    ll d = 1;
    while (d == 1) {
        x = (mul(x, x, n) + c) % n;
        y = (mul(y, y, n) + c) % n;
        y = (mul(y, y, n) + c) % n;
        d = __gcd(abs(x - y), n);
        if (d == n) return pollardRho(n);
    }
    return d;
}

map<ll, int> primeFactors;
void factorize(ll n) {
    if (n == 1) return;
    if (millerRabin(n)) {
        primeFactors[n]++;
        return;
    }
    ll d = pollardRho(n);
    factorize(d);
    factorize(n / d);
}

struct Point {
    ll x, y, z;
    ll normSq() const { return x*x + y*y + z*z; }
    Point operator+(const Point& o) const { return {x+o.x, y+o.y, z+o.z}; }
    Point operator-(const Point& o) const { return {x-o.x, y-o.y, z-o.z}; }
    Point operator*(ll k) const { return {x*k, y*k, z*k}; }
    ll dot(const Point& o) const { return x*o.x + y*o.y + z*o.z; }
    Point cross(const Point& o) const { return {y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x}; }
    bool operator==(const Point& o) const { return x==o.x && y==o.y && z==o.z; }
};

vector<Point> basisVectors; 

void runLLL() {
    int dim = 3;
    for (int iter = 0; iter < 100; ++iter) {
        bool changed = false;
        for (int i = 0; i < dim; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                long double dotProd = (long double)basisVectors[i].dot(basisVectors[j]);
                long double normVal = (long double)basisVectors[j].normSq();
                if (normVal < 1e-9) continue;
                long double mu = dotProd / normVal;
                ll coeff = round(mu);
                if (coeff != 0) {
                    basisVectors[i] = basisVectors[i] - basisVectors[j] * coeff;
                    changed = true;
                }
            }
        }
        
        for (int i = 0; i < dim - 1; ++i) {
             if (basisVectors[i+1].normSq() < basisVectors[i].normSq() * 0.7) { 
                 swap(basisVectors[i], basisVectors[i+1]);
                 changed = true;
                 break; 
             }
        }
        if (!changed) break;
    }
}

void intersectConstraint(Point constraintVec, ll modulus) {
    Point dots = { basisVectors[0].dot(constraintVec), basisVectors[1].dot(constraintVec), basisVectors[2].dot(constraintVec) };
    
    vector<vector<ll>> transformMatrix(4, vector<ll>(4, 0));
    for(int i=0;i<4;++i) transformMatrix[i][i] = 1;
    vector<ll> rowResidues = {dots.x, dots.y, dots.z, modulus};
    
    for (int i = 0; i < 3; ++i) {
        while (true) {
            int pivot = -1;
            for (int j = i; j < 4; ++j) {
                if (rowResidues[j] != 0) {
                    if (pivot == -1 || abs(rowResidues[j]) < abs(rowResidues[pivot])) pivot = j;
                }
            }
            if (pivot == -1) break;
            
            if (pivot != i) {
                swap(rowResidues[i], rowResidues[pivot]);
                for(int r=0; r<4; ++r) swap(transformMatrix[r][i], transformMatrix[r][pivot]);
            }
            
            bool done = true;
            for (int j = i + 1; j < 4; ++j) {
                if (rowResidues[j] != 0) {
                    ll q = rowResidues[j] / rowResidues[i];
                    rowResidues[j] %= rowResidues[i];
                    for (int r = 0; r < 4; ++r) transformMatrix[r][j] -= q * transformMatrix[r][i];
                    if (rowResidues[j] != 0) done = false;
                }
            }
            if (done) break;
        }
    }
    
    vector<Point> kernelVectors(3);
    for (int j = 0; j < 3; ++j) {
        kernelVectors[j] = {transformMatrix[0][j+1], transformMatrix[1][j+1], transformMatrix[2][j+1]};
    }
    
    vector<Point> nextBasis(3);
    for (int j = 0; j < 3; ++j) {
        nextBasis[j] = basisVectors[0] * kernelVectors[j].x + basisVectors[1] * kernelVectors[j].y + basisVectors[2] * kernelVectors[j].z;
    }
    basisVectors = nextBasis;
    runLLL();
}

void solveTestCase() {
    int N;
    cin >> N;
    vector<Point> inputVectors(N);
    for (int i = 0; i < N; ++i) cin >> inputVectors[i].x >> inputVectors[i].y >> inputVectors[i].z;

    int128 commonGCD = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            int128 dotProd = (int128)inputVectors[i].x * inputVectors[j].x + (int128)inputVectors[i].y * inputVectors[j].y + (int128)inputVectors[i].z * inputVectors[j].z;
            if (dotProd < 0) dotProd = -dotProd;
            if (commonGCD == 0) commonGCD = dotProd;
            else commonGCD = __gcd(commonGCD, dotProd);
        }
    }

    primeFactors.clear();
    factorize((ll)commonGCD); 

    ll targetNormSq = 1;
    for (auto p : primeFactors) {
        int exponent = p.second;
        for (int i = 0; i < exponent / 2; ++i) targetNormSq *= p.first * p.first;
    }
    ll targetNorm = (ll)sqrt(targetNormSq + 0.5);

    basisVectors = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    
    vector<int> perm(N);
    iota(all(perm), 0);
    shuffle(all(perm), rng);
    
    Point result1 = {0,0,0}, result2 = {0,0,0}, result3 = {0,0,0};
    int processedCount = 0;
    int coordLimit = 2;
    
    while (true) {
        vector<Point> candidates;
        
        for (int x = -coordLimit; x <= coordLimit; ++x) {
            for (int y = -coordLimit; y <= coordLimit; ++y) {
                for (int z = -coordLimit; z <= coordLimit; ++z) {
                    if (x==0 && y==0 && z==0) continue;
                    Point potentialVec = basisVectors[0]*x + basisVectors[1]*y + basisVectors[2]*z;
                    if (potentialVec.normSq() == targetNormSq) {
                        candidates.push_back(potentialVec);
                    }
                }
            }
        }
        
        bool found = false;
        for (Point cand : candidates) {
            bool ok = true;
            for (int i = 0; i < N; ++i) {
                if (cand.dot(inputVectors[i]) % targetNormSq != 0) {
                    intersectConstraint(inputVectors[i], targetNormSq);
                    coordLimit = 2;
                    ok = false;
                    break; 
                }
            }
            if (ok) {
                result1 = cand;
                found = true;
                break;
            }
            break; 
        }
        
        if (found) break;
        if (candidates.empty()) {
            if (processedCount < N) {
                intersectConstraint(inputVectors[perm[processedCount++]], targetNormSq);
                coordLimit = 2;
            } else {
                 coordLimit++; 
                 if (coordLimit > 5) break; 
            }
        }
    }
    
    intersectConstraint(result1, 0); 
    
    while (true) {
        vector<Point> candidates;
        int limit2 = 3;
        for (int x = -limit2; x <= limit2; ++x) {
            for (int y = -limit2; y <= limit2; ++y) {
                for (int z = -limit2; z <= limit2; ++z) {
                    if (x==0 && y==0 && z==0) continue;
                    Point potentialVec = basisVectors[0]*x + basisVectors[1]*y + basisVectors[2]*z;
                    if (potentialVec.normSq() == targetNormSq) {
                        candidates.push_back(potentialVec);
                    }
                }
            }
        }
        
        bool found = false;
        for (Point cand : candidates) {
            if (cand.dot(result1) != 0) continue; 
            bool ok = true;
            for (int i = 0; i < N; ++i) {
                if (cand.dot(inputVectors[i]) % targetNormSq != 0) {
                    ok = false; break;
                }
            }
            if (ok) {
                result2 = cand;
                found = true;
                break;
            }
        }
        
        if (found) break;
        break; 
    }
    
    result3 = result1.cross(result2);
    result3.x /= targetNorm; result3.y /= targetNorm; result3.z /= targetNorm;
    
    cout << targetNormSq << endl;
    cout << result1.x << " " << result1.y << " " << result1.z << endl;
    cout << result2.x << " " << result2.y << " " << result2.z << endl;
    cout << result3.x << " " << result3.y << " " << result3.z << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int T;
    // cin >> T;
    T = 1;

    while(T--) {
        solveTestCase();
    }
    return 0;
}