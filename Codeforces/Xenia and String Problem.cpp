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
const ll MAX_N = 100005; 
const ll MOD1 = 1e9+7;
const ll MOD2 = 1e9+9;

string T;
int N;
ll bonus[MAX_N][26];
ll diffLoss[MAX_N];
bool isGray[20][MAX_N];
int pref[26][MAX_N];

ll pow1[MAX_N], pow2[MAX_N];
ll h1[MAX_N], h2[MAX_N];
ll base1, base2;

void initHash() {
    base1 = uniform_int_distribution<ll>(300, 5000)(rng);
    base2 = uniform_int_distribution<ll>(300, 5000)(rng);
    pow1[0] = 1; pow2[0] = 1;
    for(int i=1; i<=N; ++i) {
        pow1[i] = (pow1[i-1] * base1) % MOD1;
        pow2[i] = (pow2[i-1] * base2) % MOD2;
    }
    h1[0] = 0; h2[0] = 0;
    for(int i=0; i<N; ++i) {
        h1[i+1] = (h1[i] * base1 + T[i]) % MOD1;
        h2[i+1] = (h2[i] * base2 + T[i]) % MOD2;
    }
}

pair<ll, ll> getHash(int l, int r) { // 0-based [l, r]
    if (l > r) return {0, 0};
    ll val1 = (h1[r+1] - h1[l] * pow1[r-l+1]) % MOD1;
    if(val1 < 0) val1 += MOD1;
    ll val2 = (h2[r+1] - h2[l] * pow2[r-l+1]) % MOD2;
    if(val2 < 0) val2 += MOD2;
    return {val1, val2};
}

int getLCP(int i, int j) {
    int l = 0, r = N - max(i, j);
    int ans = 0;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(mid == 0) {
            l = 1; continue;
        }
        if(getHash(i, i+mid-1) == getHash(j, j+mid-1)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int countChar(int c, int l, int r) {
    if (l > r) return 0;
    return pref[c][r+1] - pref[c][l];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    if (!(cin >> T)) return 0;
    N = size(T);
    
    initHash();
    
    for(int j=0; j<26; ++j) {
        pref[j][0] = 0;
        for(int i=0; i<N; ++i) {
            pref[j][i+1] = pref[j][i] + (T[i] == (char)('a'+j));
        }
    }
    
    for(int i=0; i<=N; ++i) {
        for(int j=0; j<26; ++j) bonus[i][j] = 0;
        diffLoss[i] = 0;
    }
    
    for(int i=0; i<N; ++i) isGray[1][i] = true;
    ll globalBase = N; 
    
    int maxK = 0;
    while((1<<(maxK+1)) - 1 <= N) maxK++;
    
    for(int k=2; k<=maxK; ++k) {
        int len = (1 << k) - 1;
        int half = (1 << (k-1)) - 1;
        
        for(int i=0; i <= N - len; ++i) {
            int mid = i + half;
            int L_start = i;
            int R_start = mid + 1;
            
            bool LGray = isGray[k-1][L_start];
            bool RGray = isGray[k-1][R_start];
            
            if(!LGray && !RGray) {
                isGray[k][i] = false;
                continue; 
            }
            
            int lcp1 = getLCP(L_start, R_start);
            int d = 0;
            if(lcp1 >= half) {
                d = 0;
            } else {
                int lcp2 = getLCP(L_start + lcp1 + 1, R_start + lcp1 + 1);
                if(lcp1 + 1 + lcp2 >= half) d = 1;
                else d = 2;
            }
            
            int mCharIdx = T[mid] - 'a';
            bool mInL = (countChar(mCharIdx, L_start, L_start + half - 1) > 0);
            
            ll val = (ll)len * len;
            isGray[k][i] = false; 
            
            if(d == 0) {
                if(LGray && RGray && !mInL) {
                    isGray[k][i] = true;
                    globalBase += val;
                    diffLoss[i] += val;
                    diffLoss[i+len] -= val;
                    
                    for(int c=0; c<26; ++c) {
                        if(countChar(c, L_start, L_start + half - 1) == 0) {
                            bonus[mid][c] += val;
                        }
                    }
                } else if(LGray && RGray && mInL) {
                    for(int c=0; c<26; ++c) {
                        if(countChar(c, L_start, L_start + half - 1) == 0) {
                            bonus[mid][c] += val;
                        }
                    }
                }
            } else if(d == 1) {
                int off = lcp1;
                int posL = L_start + off;
                int posR = R_start + off;
                
                if(RGray) {
                    int charR = T[posR] - 'a';
                    if(countChar(mCharIdx, R_start, R_start + half - 1) == 0) {
                        bonus[posL][charR] += val;
                    }
                }
                
                if(LGray) {
                    int charL = T[posL] - 'a';
                    if(!mInL) {
                        bonus[posR][charL] += val;
                    }
                }
            }
        }
    }
    
    ll currentLoss = 0;
    ll maxVal = globalBase;
    
    for(int i=0; i<N; ++i) {
        currentLoss += diffLoss[i];
        for(int c=0; c<26; ++c) {
            if(c == (T[i] - 'a')) {
                maxVal = max(maxVal, globalBase);
            } else {
                maxVal = max(maxVal, globalBase - currentLoss + bonus[i][c]);
            }
        }
    }
    
    cout << maxVal << endl;

    return 0;
}