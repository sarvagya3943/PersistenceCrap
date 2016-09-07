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

/* F.R.I.E.N.D.S version */

const int CHANDLER = 30001 ;
pair<int,int> phoebe[CHANDLER] ;
int joey[CHANDLER] ;
struct node {
    int ugly_naked_guy ;
    node *left , *right ;
    node() {
        this->left = this->right = NULL ;
        this->ugly_naked_guy = 0 ;
    }
    node(int val) {
        this->left = this->right = NULL ;
        this->ugly_naked_guy = val ;
    }
    node(node *l,node *r) {
        this->left = l ;
        this->right = r ;
        this->ugly_naked_guy = l->ugly_naked_guy + r->ugly_naked_guy ;
    }
};
node *I_KNOW(int l,int r)
{
    if(l==r)return new node() ;
    int m = (l+r)/2 ;
    return new node(I_KNOW(l,m),I_KNOW(m+1,r)) ;
}
node *HOW_YOU_DOIN(node *Node,int l,int r,int val)
{
    if(l==r)return new node(Node->ugly_naked_guy + 1) ;
    int m = (l+r)/2 ;
    if(val <= m)return new node(HOW_YOU_DOIN(Node->left,l,m,val),Node->right) ;
    return new node(Node->left,HOW_YOU_DOIN(Node->right,m+1,r,val)) ;
}
int Smelly_Cat(node *Rachel , node *Monica ,int l,int r,int s,int e)
{
    if(l>e || r<s)return 0;
    if(l>=s && r<=e)return Rachel->ugly_naked_guy - Monica->ugly_naked_guy ;
    int m = (l+r)/2 ;
    return Smelly_Cat(Rachel->left,Monica->left,l,m,s,e) + Smelly_Cat(Rachel->right,Monica->right,m+1,r,s,e) ;
}
node *friends[CHANDLER] ;
int32_t main()
{
    fast;
    int n ;
    cin >> n ;
    rep(i,1,n)cin>>phoebe[i].ff;
    /*can use a map for this too */
    rep(i,1,n)phoebe[i].ss = i ;
    sort(phoebe+1,phoebe+1+n) ;
    joey[phoebe[1].ss] = CHANDLER ; // N works as infinity here
    rep(i,2,n)
    {
        joey[phoebe[i].ss] = CHANDLER ;
        if(phoebe[i].ff == phoebe[i-1].ff) {
            joey[phoebe[i-1].ss] = phoebe[i].ss ;
        }
    }
    friends[0] = I_KNOW(1,CHANDLER) ;
    rep(i,1,n)
    {
        friends[i] = HOW_YOU_DOIN(friends[i-1],1,CHANDLER,joey[i]) ;
    }
    int m ;
    cin >> m ;
    while(m--)
    {
        int L,R ;
        cin >> L >> R ;
        cout << R-L+1 - Smelly_Cat(friends[R],friends[L-1],1,CHANDLER,1,R) << '\n' ;
    }
    return 0;
}
