/*
ye mera template hai
apna khud likho bc :P
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

int power(int a , int b)
{
    int res = 1 ;
    while(b)
    {
        if(b%2) {
            res = (res * a)%mod ;
        }
        b/=2 ;
        a = (a*a)%mod ;
    }
    return res ;
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
int arr[100005] ;
struct node {
    int sum , lazy ;
    node *left,*right ;
    node (int _sum = 0 ,int _lazy = 0 , node *_left = NULL , node *_right = NULL) {
        sum = _sum ;
        lazy = _lazy ;
        left = _left ;
        right = _right ;
    }
    node *build(int l,int r)
    {
        if(l==r) {
            sum = arr[l] ;
            return this ;
        }
        int mid = (l+r)/2 ;
        left = new node() ;
        right = new node () ;
        left = left->build(l,mid) ;
        right = right->build(mid+1,r) ;
        sum = left->sum + right->sum ;
        return this ;
    }
    node *update(int l,int r,int ql,int qr,int val) {
        if(l > qr || r < ql) {
            return this ;
        }
        if(l>=ql && r<=qr) {
            return new node(sum,lazy+val,left,right) ;
        }
        int mid = (l+r)/2 ;
        return new node(sum + val * (min(r,qr) - max(l,ql) + 1),lazy , left->update(l,mid,ql,qr,val) , right->update(mid+1,r,ql,qr,val)) ;
    }
    int query(int l,int r,int ql,int qr,int val)
    {
        if(l > qr || r < ql) {
            return 0 ;
        }
        val += lazy ;
        if(l>=ql && r<=qr) {
            return sum + val * (r-l+1) ;
        }
        int mid = (l+r)/2 ;
        return left->query(l,mid,ql,qr,val) + right->query(mid+1,r,ql,qr,val) ;
    }
};
node *root[100003] ;
int32_t main()
{
    fast;
    //openin;
    int n,m ;
    cin >> n >> m ;
    rep(i,1,n)cin >> arr[i] ;
    root[0] = new node() ;
    root[0] = root[0] -> build(1,n) ;
    int cur = 0 ;
    while(m--)
    {
        char c ;
        int l,r,d;
        cin >> c ;
        if(c=='C') {
            cur++ ;
            cin >> l >> r >> d ;
            root[cur] = root[cur-1] -> update(1,n,l,r,d) ;
        }
        else if(c=='Q') {
            cin >> l >> r ;
            cout << root[cur]->query(1,n,l,r,0) << '\n' ;
        }
        else if(c=='H') {
            cin >> l >> r >> d ;
            cout << root[d]->query(1,n,l,r,0) << '\n' ;
        }
        else {
            cin >> d ;
            cur = d ;
        }
    }
    return 0;
}
