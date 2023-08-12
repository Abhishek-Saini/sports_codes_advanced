// https://oj.uz/problem/view/APIO14_palindrome
#include <bits/stdc++.h>
#include <stdlib.h>
#include <time.h> 
 
using namespace std;
long long mod = 1e9 + 7;
double EPS = 1e-12;
typedef long long int lld;
typedef pair<lld,lld> PA;
long double tick(){static clock_t oldt; clock_t newt=clock();
    long double diff=1.0L*(newt-oldt)/CLOCKS_PER_SEC; oldt = newt; return diff; }
#define rep(i,a,n) for(long long int i = (a); i <= (n); ++i)
#define repI(i,a,n) for(int i = (a); i <= (n); ++i)
#define repD(i,a,n) for(long long int i = (a); i >= (n); --i)
#define repDI(i,a,n) for(int i = (a); i >= (n); --i)
inline lld sc() { lld a; scanf("%lld", &a); return a; }
inline int scd() { int a; scanf("%d", &a); return a; }
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

#define lim 300010
#define lim2 200010
// unordered_map<lld,lld>::iterator it; // Ab :)
// std::ios::sync_with_stdio(false);

lld A[lim];

struct Node{
    int len;
    Node *suffixLink;
    vector<Node*> palinEdges;
    int freq = 0;
    Node(int len){
        this->len = len;
        this->suffixLink = nullptr;
        this->palinEdges.resize(26, nullptr);
        this->freq = 1;
    }
};
vector<Node*> AllNodes;

int main(){
    string S;
    cin >> S;
    Node *zero = new Node(0);
    Node *negOne = new Node(-1);
    zero->suffixLink = negOne;
    negOne->suffixLink = negOne;
    Node *last = zero;

    // Build the Eer Tree
    int n = S.size();
    for(int idx = 0; idx < n; ++idx) {
        while(true) {
            int curLen = last->len;
            if(idx - curLen - 1 >= 0 && S[idx] == S[idx - curLen - 1]) break;
            last = last->suffixLink;
        }
        if(last->palinEdges.at(S[idx] - 'a') != nullptr) {
            last = last->palinEdges.at(S[idx] - 'a');
            last->freq++;
            continue;
        }
        Node *newNode = new Node(last->len + 2);
        AllNodes.push_back(newNode);
        last->palinEdges.at(S[idx] - 'a') = newNode;
        // palinEdges computed
        // Error(idx, S[idx], newNode->len, last->len);

        if(last == negOne) {
            newNode->suffixLink = zero;
            last = newNode;
            continue;
        }
        // Compute suffix link
        last = last->suffixLink;
        while(true) {
            int curLen = last->len;
            if(idx - curLen - 1 >= 0 && S[idx] == S[idx - curLen - 1]) break;
            last = last->suffixLink;
        }
        // set to zero if no suffix palindrome found
        // Error(last->len, last->palinEdges.at(S[idx] - 'a')->len);
        newNode->suffixLink = last->palinEdges.at(S[idx] - 'a');
        // Error(newNode->suffixLink->len);
        last = newNode;
    }

    // Problem Specific Logic
    lld ans = 1;
    int sz = AllNodes.size();
    for(int idx = sz - 1; idx >= 0; --idx) {
        Node *cur = AllNodes[idx];
        ans = max(ans, 1LL * cur->freq * cur->len);
        cur->suffixLink->freq += cur->freq;
    }
    prL(ans);
    return 0;
}
