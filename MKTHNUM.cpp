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
	int cnt ;
	node *left,*right ;
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
node *build(int l, int r)
{
	if(l==r)return new node() ;
	int m = (l+r)/2 ;
	return new node(build(l,m),build(m+1,r)) ;
}
node *insert(node *Node , int l,int r,int val) {
	if(l==r)return new node(Node->cnt+1) ;
	int m = (l+r)/2 ;
	if(val<=m)return new node(insert(Node->left,l,m,val),Node->right) ;
	return new node(Node->left , insert(Node->right,m+1,r,val)) ;
}
int query(node *a,node *b,int l,int r,int k)
{
	if(l==r)return l;
	int m = (l+r)/2 ;
	int left_ = a->left->cnt - b->left->cnt ;
	//cout << left_ << '\n' ;
	if(left_ >= k) {
		return query(a->left,b->left,l,m,k);
	}
	return query(a->right,b->right,m+1,r,k-left_) ;
}
node *root[100005] ;
int N = 100001 ;
map<int,int> rm ;
int32_t main()
{
    fast;
	int n,q ;
	cin >> n >> q ;
	rep(i,1,n)cin>>arr[i];
	/*compress*/
	set<int>s ;
	rep(i,1,n)s.insert(arr[i]) ;
	map<int,int>m;
	int index = 1 ;
	for(auto it : s)m[it]=index++;
	rep(i,1,n)arr[i]=m[arr[i]] ;
	for(auto it : m)rm[it.ss] = it.ff ;
	//for(auto it : rm)cout << it.ff << " " << it.ss << '\n' ;
	//rep(i,1,n)cout<<arr[i]<<" ";cout<<'\n';
	root[0] = build(1,N) ;
	rep(i,1,n) {
		root[i] = insert(root[i-1],1,N,arr[i]) ;
	}
	while(q--)
	{
		int L,R,K ;
		cin >> L >> R >> K ;
		cout << rm[query(root[R],root[L-1],1,N,K)] << "\n";
	}
    return 0;
}
