/*
ye mera template hai
apna khud likho bc =_=
*/

/*
Author : Sarvagya Agarwal
*/

#include<bits/stdc++.h>
using namespace std;

//defines
#define openin freopen("input.txt","r",stdin)
#define openout freopen("output.txt","w",stdout)
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define ll long long
#define int long long
#define mod 1000000007
#define rep(i,a,n) for(__typeof(n) i=a;i<=n;++i)
#define all(c) (c).begin(),(c).end()
#define ff first
#define ss second
#define pb push_back
#define mp make_pair

//gcd
int gcd(int a,int b)
{
    return __gcd(a,b);
}
//lcm
int lcm(int a,int b)
{
    int g = gcd(a,b);
    return a*(b/g);
}
//power
int power(int a,int b)
{
    int ans = 1;
    while(b)
    {
        if(b&1)
        {
            ans = (ans*a)%mod;
        }
        a=(a*a)%mod;
        b/=2;
    }
    return ans ;
}

//debug
#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
		cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
		const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

// DOBARA OVERFLOW KI GALTI HUI TO TU CHUTIYA HAI BC
// update : TU CHUTIYA HAI BC

const int N = 100001 ;
vector<int>occ[N] ;
struct node {
    int cnt ;
    node *left ,*right ;
    node () {
        this->cnt = 0 ;
        this->left = this->right = NULL ;
    }
    node (int val) {
        this->cnt = val ;
        this->left = this->right = NULL ;
    }
    node (node *l,node *r) {
        this->cnt = l->cnt + r->cnt ;
        this->left = l ;
        this->right = r ;
    }
};
node *build(int l,int r)
{
    if(l==r)return new node() ;
    int m = (l+r)/2;
    return new node(build(l,m),build(m+1,r));
}
node *Insert(node *Node,int l,int r,int val) {
    if(l==r)return new node(Node->cnt+1) ;
    int m = (l+r)/2 ;
    if(val<=m)return new node(Insert(Node->left,l,m,val),Node->right) ;
    return new node(Node->left,Insert(Node->right,m+1,r,val)) ;
}
int query(node *a,int l,int r,int k)
{
    if(l==r)return l ;
    int m = (l+r)/2 ;
    int co = a->left->cnt ;
    if(co>=k)return query(a->left,l,m,k);
    return query(a->right,m+1,r,k-co);
}
node *root[N+1] ;
int arr[N] ;
int32_t main()
{
    fast;
    int n,q ;
    cin >> n >> q ;
    rep(i,1,n) {
        int x ;
        cin >> x ;
        arr[i] = x ;
        occ[x].pb(i) ;
    }
    root[N] = build(1,N) ;
    for(int i=100000;i>=1;i--) {
        if(occ[i].empty()) {
            root[i] = root[i+1] ;
        }
        else {
            root[i] = root[i+1] ;
            for(auto j : occ[i]) {
                root[i] = Insert(root[i],1,N,j) ;
            }
        }
    }
    while(q--)
    {
        int L,K;
        cin >> L >> K ;
        cout << arr[query(root[L],1,N,K)] << '\n' ;
    }
    return 0;
}
