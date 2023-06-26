// https://codeforces.com/contest/438/problem/D
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
lld A[lim];

template<typename StoreType>
struct SegmentTreeTemplate {
    vector<StoreType> M, Sum;
    int n;
    StoreType* A;
    SegmentTreeTemplate(int n, StoreType TempA[]) : n(n) {
        M.resize((n << 2) + 5);
        Sum.resize((n << 2) + 5);
        A = TempA;
    }
    void buildTree(int st, int end, int ind){
        if(st == end){
            // change here to initialize
            M[ind] = A[st];
            Sum[ind] = A[st];
            return ;
        }
        int mid, a, b;
        mid = st+(end-st)/2;
        a = (ind << 1) + 1;
        b = (ind << 1) + 2;
        buildTree(st, mid, a);
        buildTree(mid + 1, end, b);
        M[ind] = max(M[a], M[b]);
        Sum[ind] = Sum[a] + Sum[b];
    }

    void updateTree(int st, int end, int ind, int updateInd, StoreType val){
        if(st == updateInd && end == updateInd){
            // change here to update
            M[ind] = val;
            Sum[ind] = val;
            return ;
        }
        int mid, a, b;
        mid = st + (end-st)/2;
        a = (ind << 1) + 1;
        b = (ind << 1) + 2;
        if(updateInd <= mid) updateTree(st, mid, a, updateInd, val);
        else updateTree(mid + 1, end, b, updateInd, val);
        M[ind] = max(M[a], M[b]);
        Sum[ind] = Sum[a] + Sum[b];
    }
    void modTree(int st, int end, int ind, int updateLeftInd, int updateRightInd, StoreType modX) {
        if(updateLeftInd > updateRightInd) return;
        if(M[ind] < modX) return; // Beats Beats
        if(st == end) {
            // change here to update
            M[ind] = M[ind] % modX;
            Sum[ind] = Sum[ind] % modX;
            return ;
        }
        int mid, a, b;
        mid = st + (end-st)/2;
        a = (ind << 1) + 1;
        b = (ind << 1) + 2;
        modTree(st, mid, a, updateLeftInd, min(mid, updateRightInd), modX);
        modTree(mid + 1, end, b, max(mid + 1, updateLeftInd), updateRightInd, modX);
        M[ind] = max(M[a], M[b]);
        Sum[ind] = Sum[a] + Sum[b];
    }
    StoreType queryTree(int st, int end, int ind, int l, int r){
        if(st == l && end == r) return Sum[ind];
        int mid;
        StoreType p1, p2;
        mid = st+(end-st)/2;
        if(r <= mid) return queryTree(st, mid, (ind << 1) + 1, l, r);
        if(l > mid) return queryTree(mid + 1, end, (ind << 1) + 2, l, r);
        p1 = queryTree(st, mid, (ind << 1) + 1, l, mid);
        p2 = queryTree(mid + 1, end, (ind << 1) + 2, mid + 1, r);
        return p1 + p2;
    }
    void build() {
        buildTree(0, n - 1, 0);
    }
    void update(int updateInd, StoreType val) {
        updateTree(0, n - 1, 0, updateInd, val);
    }
    void mod(int l, int r, StoreType modX) {
        modTree(0, n - 1, 0, l, r, modX);
    }
    StoreType query(int l, int r) {
        return queryTree(0, n - 1, 0, l, r);
    }
};

using SegmentTree = SegmentTreeTemplate<lld>;

int main(){
    lld n = sc(), m = sc();
    rep(i,0,n-1) A[i] = sc();
    SegmentTree segTree(n, A);
    segTree.build();
    while(m--) {
        lld type = sc();
        if(type == 1) {
            lld l = sc() - 1, r = sc() - 1;
            prL(segTree.query(l, r));
        }
        else if(type == 3) {
            lld l = sc() - 1, x = sc();
            segTree.update(l, x);
        }
        else {
            lld l = sc() - 1, r = sc() - 1, x = sc();
            segTree.mod(l, r, x);
        }
    }
    return 0;
}
