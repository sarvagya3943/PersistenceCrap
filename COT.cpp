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
//#define int long long
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
/*
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
*/
const int N = 111111 ;
map<int,int>rm ;
vector<int>G[N] ;
int n,M,arr[N],depth[N],parent[N] ;
void dfs(int node,int par,int d=0)
{
    depth[node] = d;
    parent[node] = par ;
    for(vector<int>::iterator child = G[node].begin() ; child!=G[node].end() ;child++) {
        if(*child!=par) {
            dfs(*child,node,d+1) ;
        }
    }
}
int P[N][19] ;
void pre()
{
    int i,j;
    for(i=1;i<=n;i++)
    {
        for(j=0; (1<<j) <n;j++)
            P[i][j]=-1;
    }
    //first ancestor is the parent
    for(i=1;i<=n;i++)P[i][0]=parent[i];
    for(j=1;(1<<j) <n;j++)
    {
        for(i=1;i<=n;i++)
        {
            if(P[i][j-1]!=-1)
                P[i][j]=P[P[i][j-1]][j-1];
        }
    }
    return ;
}
int LCA(int p,int q)
{
    int i,temp;
    //p should be deeper
    if(depth[p]<depth[q])
        temp=p,p=q,q=temp;
    //now p is deeper
    //calculate log now
    int log;
    for(log=1; (1<<log) <= depth[p];log++);
    log--;
    //bring p to the same level as q
    for(i=log;i>=0;i--)
    {
        if(depth[p] - (1<<i) >= depth[q])
            p=P[p][i];
    }
    if(p==q)return p;
    //now compute lca using dp table(P)
    for(i=log;i>=0;i--)
    {
        if(P[p][i]!=-1&&P[p][i]!=P[q][i])
            p=P[p][i],q=P[q][i];
    }
    return parent[p];
}
struct node {
    int cnt ;
    node *left , *right ;
    node () {
        this->cnt = 0 ;
        this->left = this->right = NULL ;
    }
    node (int val) {
        this->cnt = val;
        this->left = this->right = NULL ;
    }
    node (node *l,node *r) {
        this->cnt = l->cnt + r->cnt  ;
        this->left = l;this->right = r;
    }
};
node *build(int l,int r)
{
    if(l==r)return new node() ;
    int m = (l+r)/2 ;
    return new node(build(l,m),build(m+1,r));
}
node *Insert(node *Node,int l,int r,int val)
{
    if(l==r)return new node(Node->cnt+1) ;
    int m = (l+r)/2 ;
    if(val <= m)return new node(Insert(Node->left,l,m,val),Node->right) ;
    return new node(Node->left , Insert(Node->right,m+1,r,val)) ;
}
int query(node *u ,node *v , node *lca,node *plca ,int l,int r,int k)
{
    if(l==r)return l;
    int m = (l+r)/2 ;
    int _left = u->left->cnt + v->left->cnt - lca->left->cnt - plca->left->cnt ;
    if(_left >= k)return query(u->left,v->left,lca->left,plca->left,l,m,k) ;
    return query(u->right,v->right,lca->right,plca->right,m+1,r,k-_left);
}
node *root[N] ;

void dfs2(int node,int par)
{
    root[node] = Insert(root[par],1,N,arr[node]) ;
    for(vector<int>::iterator child = G[node].begin() ; child!=G[node].end() ;child++) {
        if(*child!=par) {
            dfs2(*child,node) ;
        }
    }
}
inline void si(int* x)
{
	register char c = getchar_unlocked();
	*x = 0;
	int neg = 0;
	for(; ((c<48 || c>57) && c != '-');c = getchar_unlocked());
	if(c=='-') {
        neg = 1;
        c = getchar_unlocked();
    }
	for(; (c>47)&&(c<58);c = getchar_unlocked())
		*x = (int)((((*x)<<1) + ((*x)<<3)) + c - 48);
    if(neg)
        *x = -*x;
}
inline void plli(long long int a)
{
    char snum[20];
    int i=0;
    char sign='+';
    if(a<0)
    {
        sign='-';
        a*=-1;
    }
    do
    {
        snum[i++]=a%10+48;
        a=a/10;
    }while(a!=0);
    i=i-1;
    if(sign=='-')
        putchar_unlocked(sign);
    while(i>=0)
    putchar_unlocked(snum[i--]);
    putchar_unlocked('\n');
}
int main()
{
   // fast;
   // cin >> n >> M ;
    //rep(i,1,n)cin>>arr[i];
    //openin;
    //scanf("%d%d",&n,&M);
    si(&n);si(&M);
    //rep(i,1,n)scanf("%d",&arr[i]);
    rep(i,1,n)si(&arr[i]);
    set<int>s;
    rep(i,1,n)s.insert(arr[i]);
    map<int,int>m;
    int index=1;
    //for(auto it:s)m[it]=index++;
    for(set<int>::iterator it = s.begin();it!=s.end();it++)m[*it]=index++;
    rep(i,1,n)arr[i]=m[arr[i]];
    //rep(i,1,n)trace(i,arr[i]);
    /*reverse map*/
    for(map<int,int>::iterator it = m.begin();it!=m.end();it++)rm[it->second] = it->first;
    rep(i,2,n)
    {
        int u,v;
        //cin>>u>>v;
        si(&u);si(&v);//scanf("%d%d",&u,&v);
        G[u].pb(v);
        G[v].pb(u);
    }
    dfs(1,0) ;
    pre() ;
    root[0] = build(1,N) ;
    dfs2(1,0) ;
    while(M--)
    {
        int u,v,k;
        //cin >> u >> v >> k ;
        si(&u);si(&v);si(&k);//scanf("%d%d%d",&u,&v,&k);
        int lca = LCA(u,v) ;
        printf("%d\n",rm[query(root[u],root[v],root[lca],root[parent[lca]],1,N,k)]);
    }
    return 0;
}

