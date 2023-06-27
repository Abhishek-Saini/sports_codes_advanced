// https://codeforces.com/contest/840/problem/D
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
lld UniqueSorted[lim];

struct WaveletTree {
    vector<vector<int> > M, Pre;
    int n;
	lld ans;
    // n = number of unique elements, tree is zero-indexed
    WaveletTree(int n) : n(n) {
        M.resize((n << 2) + 5);
        Pre.resize((n << 2) + 5);
    }
    void buildTree(int st, int end, int ind){
        if(st == end){
            return ;
        }
        int mid, a, b;
        mid = st+(end-st)/2;
        a = (ind << 1) + 1;
        b = (ind << 1) + 2;
        int sz = M[ind].size();
        Pre[ind].emplace_back(0LL);
		rep(i,0,sz-1) {
            if(A[M[ind][i]] <= UniqueSorted[mid]) {
                M[a].emplace_back(M[ind][i]);
                Pre[ind].emplace_back(Pre[ind].back());
            }
            else {
                M[b].emplace_back(M[ind][i]);
                Pre[ind].emplace_back(Pre[ind].back() + 1LL);
            }
			// Error(i,mn,val);
			// M[ind].emplace_back(curr);
		}
        buildTree(st, mid, a);
        buildTree(mid + 1, end, b);
    }
    lld queryTree(int st, int end, int ind, int l, int r, lld freqThreshold){
        // Error(st, end, ind, l, r, Pre[ind].size());
        // Error(UniqueSorted[st], UniqueSorted[end]);
        // for(auto it : M[ind]) Error(it, A[it]);
        if(st == end) {
            return A[M[ind][0]];
        }
        int mid, a, b;
        lld p1, p2;
        mid = st+(end-st)/2;
		a = (ind << 1) + 1;
        b = (ind << 1) + 2;
        lld rightFreq = Pre[ind][r] - Pre[ind][l - 1];
        lld leftFreq = (r - l + 1) - rightFreq;
        if(leftFreq > freqThreshold) {
            lld p1 = queryTree(st, mid, a, (l - 1 - Pre[ind][l-1]) + 1, r - Pre[ind][r], freqThreshold);
            if(p1 != -1) return p1;
        }
        if(rightFreq > freqThreshold) {
            lld p2 = queryTree(mid + 1, end, b, Pre[ind][l-1]+1, Pre[ind][r], freqThreshold);
            return p2;
        }
        return -1;
    }
    void build(lld numEle) {
        rep(i,1,numEle) M[0].emplace_back(i);
        buildTree(0, n - 1, 0);
    }
    // l and r are 1-indexed
    lld query(int l, int r, int k) {
        lld freqThreshold = (r - l + 1) / k;
        return queryTree(0, n - 1, 0, l, r, freqThreshold);
    }
};


int main(){
    lld numEle = sc(), q = sc();
    rep(i,1,numEle) A[i] = sc();
    rep(i,1,numEle) UniqueSorted[i-1] = A[i];
    sort(UniqueSorted, UniqueSorted + numEle);
    lld uniqueEle = unique(UniqueSorted, UniqueSorted + numEle) - (UniqueSorted);
    WaveletTree T(uniqueEle);
    T.build(numEle);
    while(q--) {
        lld l = sc(), r = sc(), k = sc();
        lld ans = T.query(l, r, k);
        prL(ans);
    }
    return 0;
}
