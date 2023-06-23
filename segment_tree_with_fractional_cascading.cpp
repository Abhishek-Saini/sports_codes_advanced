// https://codeforces.com/contest/893/problem/F
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
lld A[lim], Depth[lim];
vector<lld> G[lim];

template<typename StoreType>
struct SegmentTreeTemplate {
    void MergeNodes(int a, int b, int ind) {
        int i, j, k, n1, n2;
        n1 = M[a].size();
        n2 = M[b].size();
        i = j = 0;
        int lastLeft = 0, lastRight = 0;
        // Safe because no call to merge if zero element in one child 
        StoreType lastLeftVal = min(M[a][0], M[b][0]), lastRightVal = min(M[a][0], M[b][0]);
        StoreType lastVal = INT_MAX;
        while(i < n1 && j < n2) {
            if(M[a][i] < M[b][j]) {
                M[ind].emplace_back(M[a][i]);
                lastVal = min(lastVal, Pre[a][i]);
                Pre[ind].emplace_back(lastVal);
                LeftSubtreePointer[ind].emplace_back(-1);
                if(lastLeftVal < M[a][i]) {
                    fill(LeftSubtreePointer[ind].begin() + lastLeft, LeftSubtreePointer[ind].end() - 1, i);
                    lastLeft = LeftSubtreePointer[ind].size() - 1;
                    lastLeftVal = M[a][i];
                }
                RightSubtreePointer[ind].emplace_back(-1);
                i++;
            }
            else {
                M[ind].emplace_back(M[b][j]);
                lastVal = min(lastVal, Pre[b][j]);
                Pre[ind].emplace_back(lastVal);
                LeftSubtreePointer[ind].emplace_back(-1);
                RightSubtreePointer[ind].emplace_back(-1);
                if(lastRightVal < M[b][j]) {
                    fill(RightSubtreePointer[ind].begin() + lastRight, RightSubtreePointer[ind].end() - 1, j);
                    lastRight = RightSubtreePointer[ind].size() - 1;
                    lastRightVal = M[b][j];
                }
                j++;
            }
        }
        while(i < n1) {
            M[ind].emplace_back(M[a][i]);
            lastVal = min(lastVal, Pre[a][i]);
            Pre[ind].emplace_back(lastVal);
            LeftSubtreePointer[ind].emplace_back(-1);
            if(lastLeftVal < M[a][i]) {
                fill(LeftSubtreePointer[ind].begin() + lastLeft, LeftSubtreePointer[ind].end() - 1, i);
                lastLeft = LeftSubtreePointer[ind].size() - 1;
                lastLeftVal = M[a][i];
            }
            RightSubtreePointer[ind].emplace_back(-1);
            i++;
        }
        while(j < n2) {
            M[ind].emplace_back(M[b][j]);
            lastVal = min(lastVal, Pre[b][j]);
            Pre[ind].emplace_back(lastVal);
            LeftSubtreePointer[ind].emplace_back(-1);
            RightSubtreePointer[ind].emplace_back(-1);
            if(lastRightVal < M[b][j]) {
                fill(RightSubtreePointer[ind].begin() + lastRight, RightSubtreePointer[ind].end() - 1, j);
                lastRight = RightSubtreePointer[ind].size() - 1;
                lastRightVal = M[b][j];
            }
            j++;
        }
    }
    vector<vector<StoreType> > M, Pre, LeftSubtreePointer, RightSubtreePointer;
    int n;
    StoreType* A;
    SegmentTreeTemplate(int n, StoreType TempA[]) : n(n) {
        M.resize((n << 2) + 5);
        Pre.resize((n << 2) + 5);
        LeftSubtreePointer.resize((n << 2) + 5);
        RightSubtreePointer.resize((n << 2) + 5);
        A = TempA;
    }
    void buildTree(int st, int end, int ind){
        if(st == end){
            // change here to initialize
            M[ind].emplace_back(Depth[st]);
            Pre[ind].emplace_back(A[st]);
            LeftSubtreePointer[ind].emplace_back(-1);
            RightSubtreePointer[ind].emplace_back(-1);
            return ;
        }
        int mid, a, b;
        mid = st+(end-st)/2;
        a = (ind << 1) + 1;
        b = (ind << 1) + 2;
        buildTree(st, mid, a);
        buildTree(mid + 1, end, b);
        MergeNodes(a, b, ind);
    }
    StoreType queryTree(int st, int end, int ind, int l, int r, int preInd){
        if(preInd == -1) preInd = Pre[ind].size();
        if(preInd == 0) return INT_MAX;
        if(st == l && end == r) {
            return Pre[ind][preInd-1];
        }
        int mid;
        StoreType p1, p2;
        mid = st+(end-st)/2;
        if(r <= mid) return queryTree(st, mid, (ind << 1) + 1, l, r, LeftSubtreePointer[ind][preInd-1]);
        if(l > mid) return queryTree(mid + 1, end, (ind << 1) + 2, l, r, RightSubtreePointer[ind][preInd-1]);
        p1 = queryTree(st, mid, (ind << 1) + 1, l, mid, LeftSubtreePointer[ind][preInd-1]);
        p2 = queryTree(mid + 1, end, (ind << 1) + 2, mid + 1, r, RightSubtreePointer[ind][preInd-1]);
        return min(p1, p2);
    }
    void build() {
        buildTree(0, n - 1, 0);
    }
    StoreType query(int l, int r, int neededDepth) {
        int preInd = upper_bound(M[0].begin(), M[0].end(), neededDepth) - M[0].begin();
        return queryTree(0, n - 1, 0, l, r, preInd);
    }
};

using SegmentTree = SegmentTreeTemplate<lld>;

int main(){
    lld n = sc(), root = sc() - 1;
    vector<lld> Org(n);
    rep(i,0,n-1) Org[i] = sc();
    rep(i,1,n-1){
        lld u = sc() - 1, v = sc() - 1;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    auto dfsNumbering = [&](lld root){
        vector<lld> left(n, -1), right(n, -1), depth(n, -1);
        lld dfsCounter = 0;
        function<void(lld, lld)> dfs = [&](lld u, lld d){
            left[u] = dfsCounter++;
            depth[u] = d;
            for(auto v : G[u]) if(left[v] == -1) dfs(v, d + 1);
            right[u] = dfsCounter - 1;
        };
        dfs(root, 0);
        return make_tuple(left, right, depth);
    };
    vector<lld> left, right, depth;
    tie(left, right, depth) = dfsNumbering(root);
    rep(i,0,n-1) A[left[i]] = Org[i];
    rep(i,0,n-1) Depth[left[i]] = depth[i];
    SegmentTree ST(n, A);
    ST.build();
    lld q = sc();
    lld ans = 0;
    while(q--) {
        lld p = sc(), q = sc();
        lld node = (p + ans) % n, k = (q + ans) % n;
        lld l = left[node], r = right[node];
        lld neededDepth = depth[node] + k;
        ans = ST.query(l, r, neededDepth);
        prL(ans);
    }
    return 0;
}
