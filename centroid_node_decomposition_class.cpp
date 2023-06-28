// https://codeforces.com/contest/342/problem/E
#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;
long long mod = 1e9 + 7;
long long INF = 1e7;
double EPS = 1e-12;
typedef long long int lld;
long double tick(){static clock_t oldt; clock_t newt=clock();
    long double diff=1.0L*(newt-oldt)/CLOCKS_PER_SEC; oldt = newt; return diff; }
#define rep(i,a,n) for(long long int i = (a); i <= (n); ++i)
#define repI(i,a,n) for(int i = (a); i <= (n); ++i)
#define repD(i,a,n) for(long long int i = (a); i >= (n); --i)
#define repDI(i,a,n) for(int i = (a); i >= (n); --i)
inline lld sc() { lld a; scanf("%lld", &a); return a; }
inline int scd() { int a; scanf("%d", &a); return a; }
inline double scf() { double a; scanf("%lf",&a); return a; }
#define prL(a) printf("%lld\n",a)
#define prS(a) printf("%lld ",a)
#define prdL(a) printf("%d\n",a)
#define prdS(a) printf("%d ",a)
#define all(c) (c).begin(), (c).end()
#define sz(a) ((int)a.size())

#ifdef LOCAL_RUN
#define Error(x...) { cout << "(" << #x << ")" << " = ( "; printIt(x); }
#define errorpair(a) cout<<#a<<" = ( "<<((a).first)<<" , "<<((a).second)<<" )\n";
#else
#define Error(x...) 42
#define errorpair(a) 42
#endif

template <typename T1> void printIt(T1 t1) { cout << t1 << " )" << endl; }
template <typename T1, typename... T2>
void printIt(T1 t1, T2... t2) { cout << t1 << " , "; printIt(t2...); }
#define mset(a, v) memset(a, v, sizeof(a))
#define popcount __builtin_popcountll

typedef pair<lld,lld> PA;

lld powP(lld x, lld y) {
    lld ans = 1, po = x % mod;
    while(y > 0) {
        if(y & 1) ans = ans * po % mod;
        y >>= 1; po = po * po % mod;
    }
    return ans;
}
 
bool bitSet(lld n, lld bit){
    if((n & (1LL << bit)) != 0) return true;
    else return false;
}
 
lld findGcd(lld a, lld b){
    while(a != 0) { lld temp = b % a; b = a; a = temp; }
    return b;
}

#define lim 300010
#define lim2 200010
#define qqqqqq 210
// Ab :)
// inline lld sqr(lld x) { return x * x; }
// unordered_map<lld,lld>::iterator it;
// std::ios::sync_with_stdio(false);
// priority_queue<PA> Q;
// lld dp[1<<18];

// string S[lim];
vector<int> G[lim];
vector<pair<int,int> > V[lim];

// Uses G[lim] for edges to build itself
struct CentroidDecomposition {
    vector<int> Parent;
    vector<int> Sz;
    vector<bool> Alive;
    int currNodesRem;
    CentroidDecomposition(int n) {
        Parent.resize(n + 3);
        Sz.resize(n + 3);
        Alive.resize(n + 3, true);
    }
    // intial call with root, parent sth like (1,-1) to build
    void build(int x, int par) {
        findSz(x, par);
        currNodesRem = Sz[x];
        int centroid =  findCentriod(x, par);
        Parent[centroid] = par;
        Alive[centroid] = false;

        // do sth with the centroid
        // Problem Specific Section Start
        currRoot = centroid;
        saveDis(centroid, par, 0);

        // Problem Specific Section End

        for(auto c : G[centroid]) {
            if(Alive[c]) build(c, centroid);
        }
    }

    void findSz(int x, int par) {
        Sz[x] = 1;
        for(auto c : G[x]) {
            if(c != par and Alive[c]) {
                findSz(c, x);
                Sz[x] += Sz[c];
            }
        }
    }

    int findCentriod(int x, int par) {
        for(auto c : G[x]) {
            if(c != par and Alive[c]) {
                if(Sz[c] > currNodesRem / 2) return findCentriod(c, x);
            }
        }
        return x;
    }

    // Problem Specific Variables and Functions

    int currRoot;
    void saveDis(int x, int par, int dis) {
        V[x].push_back({currRoot, dis});
        for(auto c : G[x]) {
            if(c != par and Alive[c]) saveDis(c, x, dis + 1);
        }
    }
};


int Ans[lim];

void PaintNode(int x) {
    for(const auto& t : V[x]) {
        Ans[t.first] = min(Ans[t.first], t.second);
    }
}

int findMinDis(int x) {
    int val = INF;
    for(const auto& t : V[x]) {
        val = min(val, Ans[t.first] + t.second);
    }
    return val;
}

int main(){
    int n = scd(), m = scd();
    repI(i,1,n-1) {
        int a = scd(), b = scd();
        G[a].push_back(b);
        G[b].push_back(a);
    }
    CentroidDecomposition CD(n);
    CD.build(1,-1);
    repI(i,1,n) Ans[i] = INF;
    PaintNode(1);
    while(m--) {
        int a = scd(), b = scd();
        if(a == 1) PaintNode(b);
        else prdL(findMinDis(b));
    }
    return 0;
}
