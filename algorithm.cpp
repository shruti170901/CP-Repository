struct UnionFind 
{
	vector<int> data;
	void init(int n) { data.assign(n, -1); }
	bool unionSet(int x, int y) 
	{
		x = root(x); y = root(y);
		if(x != y) 
		{
			if(data[y] < data[x]) swap(x, y);
			data[x] += data[y]; data[y] = x;
		}
		return x != y;
	}
	bool findSet(int x, int y) { return root(x) == root(y); }
	int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
	int size(int x) { return -data[root(x)]; }
};

___________________________________________________________________________

struct FenwickTree 
{
	typedef ll T;
	vector<T> v;
	FenwickTree(int n): v(n, 0) {}
	void add(int i, T x) {
		for(; i < (int)v.size(); i |= i+1) v[i] += x;
	}
	T sum(int i) {	//[0, i)
		T r = 0;
		for(-- i; i >= 0; i = (i & (i+1)) - 1) r += v[i];
		return r;
	}
	T sum(int left, int right) {	//[left, right)
		return sum(right) - sum(left);
	}
};

_____________________________________________________________________________
//https://www.codechef.com/viewsolution/3296495
vector<int> longestIncreaseSequence(const vector<int>& a) 
{
	const int n = a.size();
	vector<int> A(n, INF);
	vector<int> id(n);
	for(int i = 0; i < n; ++i) {
		id[i] = lower_bound(all(A), a[i]) - A.begin();
		A[id[i]] = a[i];
	}
	int m = *max_element(id.begin(), id.end());
	vector<int> b(m+1);
	for(int i = n-1; i >= 0; --i)
		if(id[i] == m) b[m--] = a[i];
	return b;
}

_______________________________________________________________________________
vector<int> mobiusMu;
void calcMobiusMu(int n) 
{
	mobiusMu.assign(n+1, 1);
	for(int i = 2; i <= n; i ++) if(isprime[i]) 
	{
		if((ll)i * i <= n) {
			for(int j = i * i; j <= n; j += i * i)
				mobiusMu[j] = 0;
		}
		for(int j = i; j <= n; j += i)
			mobiusMu[j] *= -1;
	}
}

________________________________________________________________________________

struct SegTree
{
	vector<int> Tree;
	void init(int Arr[],int N) { Tree.assign(4*N,0); Build(Arr,1,N,1); }
	void Build(int Arr[],int L,int R,int POS)
	{
	   if(L==R)  {   Tree[POS]=Arr[L]; return; }
	   int Mid=(L+R)/2;
	   Build(Arr,L,Mid,2*POS); Build(Arr,Mid+1,R,2*POS+1);
	   Tree[POS]=max(Tree[POS*2],Tree[POS*2+1]);
	}
 
	int Query(int L,int R,int QL,int QR,int POS)
	{
	    if(QL<=L && QR>=R) return Tree[POS];
	    if (QL>R || QR<L)  return -1;
	    int Mid=(L+R)/2;   return max(   Query(  L,  Mid  , QL,QR ,  2*POS), Query(Mid+1 ,R   , QL,QR ,  2*POS+1) );
	}
 
	void Update(int L,int R,int QL,int QR,int POS,int VALUE)
	{
	    if(L>R || QL>R || QR<L) { return; }  if(L==R)   { if(QL==L && QR==R) Tree[POS]=VALUE; return;  }
	    int Mid=(L+R)/2;  Update(L,Mid,QL,QR,2*POS,VALUE);  Update(Mid+1,R,QL,QR,2*POS+1,VALUE);
	    Tree[POS]=max(Tree[POS*2],Tree[POS*2+1]);
	}
};

_______________________________________________________________________________________________________________________

2
6 7
2 5 8 10 3 44
1 2 6
0 2 3
1 2 6
0 4 6
1 1 6
0 1 6
1 4 6
6 7
2 5 8 10 3 44
1 2 6
0 2 3
1 2 6
0 4 6
1 1 6
0 1 6
1 4 6

//Segment Tree, lazy propagataion [Range Min/Max,[sum in range],[product in range],[range updates],[point updates]
//

#include <stdio.h>
#include <iostream>
#define ll long long
using namespace std;
const int N = 100005;
const ll mod = (ll) 1e9 + 7;
int n,q,a[N];
int seg[4*N],lazy1[4*N],lazy2[4*N],lazy3[4*N];
void build(int id,int l,int r){
    lazy1[id] = 0; lazy2[id] = 1; lazy3[id] = -1;
    if (l == r){ seg[id] = a[l]; return; }
    build(2*id,l,(l+r)/2);
    build(2*id+1,(l+r)/2+1,r);
    seg[id] = (seg[2*id] + seg[2*id+1]) % mod;
}

void _lazy(int id,int l,int r){
    if (lazy3[id] != -1){
        seg[id] = (r-l+1) * lazy3[id] % mod;
        seg[id] = (seg[id] * lazy2[id]) % mod;
        seg[id] = (seg[id] + lazy1[id] * (r-l+1)) % mod;
        if (l != r){
            lazy1[2*id] = lazy1[2*id+1] = lazy1[id],
            lazy2[2*id] = lazy2[2*id+1] = lazy2[id],
            lazy3[2*id] = lazy3[2*id+1] = lazy3[id];
        }
        lazy1[id] = 0;
        lazy2[id] = 1;
        lazy3[id] = -1;
    }
    else{
        seg[id] = (seg[id] * lazy2[id]) % mod;
        seg[id] = (seg[id] + lazy1[id] * (r-l+1)) % mod;
        if (l != r)
            lazy1[2*id]   = (lazy1[2*id] * lazy2[id]) % mod,
            lazy2[2*id]   = (lazy2[2*id] * lazy2[id]) % mod,
            lazy1[2*id+1] = (lazy1[2*id+1] * lazy2[id]) % mod,
            lazy2[2*id+1] = (lazy2[2*id+1] * lazy2[id]) % mod,
            lazy1[2*id]   = (lazy1[2*id] + lazy1[id]) % mod,
            lazy1[2*id+1] = (lazy1[2*id+1] + lazy1[id]) % mod;
        lazy1[id] = 0;
        lazy2[id] = 1;
    }
}
void upd(int type,int id,int l,int r,int u,int v,ll val){
    _lazy(id,l,r);
    if (r < u || v < l) return;
    if (u <= l && r <= v){
        if (type == 1){
            seg[id] = (seg[id] + (r-l+1) * val) % mod;
            if (l != r)
                lazy1[2*id]   = (lazy1[2*id] + val) % mod,
                lazy1[2*id+1] = (lazy1[2*id+1] + val) % mod;
            return;
        }
        else if (type == 2){
            seg[id] = (seg[id] * val) % mod;
            if (l != r)
                lazy1[2*id]   = (lazy1[2*id] * val) % mod,
                lazy2[2*id]   = (lazy2[2*id] * val) % mod,
                lazy1[2*id+1] = (lazy1[2*id+1] * val) % mod,
                lazy2[2*id+1] = (lazy2[2*id+1] * val) % mod;
            return;
        }
        else{
            seg[id] = (r-l+1) * val % mod;
            if (l != r)
                lazy1[2*id] = lazy1[2*id+1] = 0,
                lazy2[2*id] = lazy2[2*id+1] = 1,
                lazy3[2*id] = lazy3[2*id+1] = val;
            return;
        }
    }
    upd(type,2*id,l,(l+r)/2,u,v,val);
    upd(type,2*id+1,(l+r)/2+1,r,u,v,val);
    seg[id] = (seg[2*id] + seg[2*id+1]) % mod;
}
ll get(int id,int l,int r,int u,int v){
    _lazy(id,l,r);
    if (r < u || v < l) return 0;
    if (u <= l && r <= v) return seg[id];
    return (get(2*id,l,(l+r)/2,u,v) + get(2*id+1,(l+r)/2+1,r,u,v))%mod;
}
int main(){
    //freopen("test.inp","r",stdin);
    //freopen("ans.out","w",stdout);
    scanf("%lld %lld",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    build(1,1,n);
    while(q--){
        ll type,x,y,v;
        scanf("%lld",&type);
        if (type == 4){
            scanf("%lld %lld",&x,&y),
            printf("%lld\n",get(1,1,n,x,y));
        }
        else
            scanf("%lld %lld %lld",&x,&y,&v),
            upd(type,1,1,n,x,y,v);
    }
}


_______________________________________________________________________________________________________________________
#include<bits/stdc++.h>
using namespace std;
 
typedef long long int ll;
 
#define pb push_back
#define mp make_pair
 
#define rep(i,n)	for(int i=0;i<(n);i++)
#define rep1(i,n)	for(int i=1;i<=(n);i++)
 
#define maxn 100009
 
const int mod = 1e9+7;
 
int A[maxn];
 
struct segment
{
	int subtree_size,addition,multiplication,sum_in_subtree,reset;
	bool change;
	segment(int _subtree_size=0,int _addition=0 , int _multiplication=1 , int _sum_in_subtree=0 , int _reset=0 , bool _change=false){
		subtree_size = _subtree_size;
		addition = _addition;
		multiplication = _multiplication;
		sum_in_subtree = _sum_in_subtree;
		reset = _reset ;
		change = _change ;
	}
}seg[1<<18];
 
void merge(int node)
{
	int x = node*2;
	int y = node*2+1;
	seg[node].sum_in_subtree = (seg[x].sum_in_subtree + seg[y].sum_in_subtree)%mod;
}
 
void init(int s,int e,int node)
{
	if( s==e ){
		seg[node] = segment(1,0,1,A[s],0,false);
		return;
	}
	init(s,(s+e)/2,node*2);
	init((s+e)/2+1,e,node*2+1);
	seg[node] = segment(seg[node*2].subtree_size + seg[node*2+1].subtree_size , 0,1,(seg[node*2].sum_in_subtree + seg[node*2+1].sum_in_subtree)%mod , 0, false ) ;
}
 
void lazy(int node)
{
	int x = node*2;
	int y = x+1;
 
	int add = seg[node].addition;
	int mul = seg[node].multiplication;
	int sizex = seg[x].subtree_size;
	int sizey = seg[y].subtree_size;
 
	if( seg[node].change ){
		int change_to = seg[node].reset;
		seg[node] = segment(seg[node].subtree_size , 0 , 1, seg[node].sum_in_subtree , 0,false);
		seg[x] = segment(sizex ,0,1, ((ll)change_to*(ll)sizex)%mod , change_to , true );
		seg[y] = segment(sizey ,0,1, ((ll)change_to*(ll)sizey)%mod , change_to , true );
		return;
	}
 
	if( seg[node].addition == 0 && seg[node].multiplication == 1 )	return;
 
	seg[node] = segment(seg[node].subtree_size , 0 , 1, seg[node].sum_in_subtree , 0, false );
	seg[x] = segment ( sizex , ((ll)mul*(ll)seg[x].addition + (ll)add)%mod , ((ll)seg[x].multiplication*(ll)mul)%mod , ((ll)seg[x].sum_in_subtree*(ll)mul + (ll)add*(ll)sizex)%mod ,((ll)seg[x].reset*(ll)mul+(ll)add)%mod , seg[x].change);
	seg[y] = segment ( sizey , ((ll)mul*(ll)seg[y].addition + (ll)add)%mod , ((ll)seg[y].multiplication*(ll)mul)%mod , ((ll)seg[y].sum_in_subtree*(ll)mul + (ll)add*(ll)sizey)%mod ,((ll)seg[y].reset*(ll)mul+(ll)add)%mod , seg[y].change);
}
 
void Update(int s,int e,int i,int j,int node,int v,int op)
{
	if( j < s || e < i )	return ;
	if ( i<=s && e<=j ) {
		if (op == 0)	//addition
			seg[node] = segment ( seg[node].subtree_size , (seg[node].addition + v)%mod , seg[node].multiplication , ((ll)seg[node].sum_in_subtree + (ll)v*(ll)seg[node].subtree_size)%mod , ((ll)seg[node].reset + (ll)v)%mod, seg[node].change );
		else if ( op == 1)	// multiplication
			seg[node] = segment ( seg[node].subtree_size , ((ll)seg[node].addition*(ll)v)%mod , ((ll)seg[node].multiplication*(ll)v)%mod , ((ll)seg[node].sum_in_subtree*(ll)v)%mod , ((ll)seg[node].reset*(ll)v)%mod, seg[node].change );
		else if ( op == 2)	//reset Query
			seg[node] = segment(seg[node].subtree_size , 0,1,((ll)v*(ll)seg[node].subtree_size)%mod , v, true);
		return ;
	}
	lazy(node);
	Update(s,(s+e)/2,i,j,node*2,v,op);
	Update((s+e)/2+1,e,i,j,node*2+1,v,op);
	merge(node);
}
 
int Query(int s,int e,int i,int j,int node)
{
	if( j<s || e<i )	return 0;
	if( i<=s  && e<=j )	return seg[node].sum_in_subtree ;
	lazy(node);
	return (Query(s,(s+e)/2, i, j, node*2) + Query((s+e)/2+1,e, i,j, node*2+1))%mod;
}
 
void solve()
{
	int N,Q,op,x,y,v;
	scanf("%d%d",&N,&Q);
	rep1(i,N)	scanf("%d",&A[i]),A[i] %= mod;
	init(1,N,1);
	while(Q--){
		scanf("%d%d%d",&op,&x,&y);
		op--;
		if( op <3 ){
			scanf("%d",&v);
			v %= mod;
			Update(1,N, x,y,1,v, op);
		}
		else if ( op == 3 ){
			printf("%d\n",Query(1,N,x,y,1));
		}
	}
}
 
int main()
{
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}


//-SEGMENT TREE WITH LAZY PROPAGATION IMPLEMENTATION FOR LARGE NUMBER OF RANGE QUERIES-//
 
//-------PROBLEM INCLUDES FOLLOWING QUERIES : ---------------------------------//
//-------1) ADDING ELEMENTS OF A RANGE [L,R] WITH AN INT VALUE-----------------//
//-------2) MULTIPLYING ELEMENTS OF A RANGE [L,R] WITH AN INT VALUE------------//
//-------3) SETTING ELEMENTS OF A RANGE [L,R] WITH AN INT VALUE----------------//
//-------4) SUM OF A GIVEN RANGE [L,R].----------------------------------------//
 
//------------PROBLEM LINK : http:/codechef.com/problems/addmul/ --------------//
 
 
#include<stdio.h>
 
#define R_MAX 100005
#define gc getchar_unlocked
#define MOD 1000000007
 
typedef long long int LLI;
 

//------------------------STRUCTURE OF NODES FOR THE SEGMENT TREE---------------------//
 
typedef struct					
{
	int add;				//add carries the lazy info about previous range additions,
	int mul;				//mul carries the lazy info about previous range multiplications,
	int sum;				//sum carries the sum of the range.
}Node;
 
int a[R_MAX];
Node st[4*R_MAX];
int n;
 
//--------------UTILITY FUNCTIONS FOR PUSHING DOWN LAZYNESS AND RETURNING SUM----------//
 
int down_add(int node, int tl, int tr, int value)	//passing the lazyness to the children
{												//and return the sum of that range.
	if(tl<1)  tl = 1;
	if(tr>n)  tr = n;
	if(tl>tr) return 0;
	st[node].add = st[node].add + value;
	return ((tr-tl+1)* st[node].add + st[node].sum* st[node].mul);
}
 
int down_mul(int node, int tl, int tr, int value)
{
	if(tl<1) tl = 1;
	if(tr>n) tr = n;
	if(tl>tr) return 0;
	st[node].add = st[node].add*value;
	st[node].mul = st[node].mul*value;
	return 	(tr-tl+1)*st[node].add + st[node].sum*st[node].mul ;
}
 
int down_set(int node, int tl, int tr, int value)
{
	if(tl<1) tl = 1;
	if(tr>n) tr = n;
	if(tl>tr) return 0;
	st[node].add = value;
	st[node].sum = 0;
	st[node].mul = 0;	//mul = 0, to detect the lazyness due to range set
	return (tr-tl+1)*st[node].add;
}
 
int GetSum(int node, int tl, int tr, int l, int r)
{
	if(l>r) return 0;
	if(l == tl && r == tr)
		return (tr-tl+1)*st[node].add + st[node].sum*st[node].mul;
	int mid = (tl+ tr)/2;
	int index = 2*node;
	if(st[node].mul > 1){
		st[node].sum = addMod( down_mul(index, tl, mid, st[node].mul), down_mul(index+1, mid+1, tr, st[node].mul));
		st[node].mul = 1;
	}
 
	else if(st[node].mul == 0)
	{
		st[node].sum = addMod( down_set(index, tl, mid, st[node].add), down_set(index+1, mid+1, tr, st[node].add) );
		st[node].add = 0;
		st[node].mul = 1;
	}
 
	return addMod( addMod( GetSum(index, tl, mid, l, min(r,mid)), GetSum(index+1, mid+1, tr, max(l,mid+1), r)), 
											mulMod( (r-l+1), st[node].add)); 
}
 
//----------------------------FUNCTION FOR QUERY NUMBER 1, RANGE ADDITION----------------------------------//
 
int
update_add(int node, int tl, int tr, int l, int r, int value)
{
	if(l>r)
		return 0;
 
	if(tl == l && tr==r)
	{
		st[node].add = addMod(st[node].add, value);
		return mulMod( (tr-tl+1), value);
	}
	else
	{
		int s;
		int mid = getMid(tl, tr);
		int index = twice(node);
		if(st[node].mul > 1)
		{	
			st[node].sum = addMod( down_mul(index, tl, mid, st[node].mul), down_mul(index+1, mid+1, tr, st[node].mul) );
			st[node].mul = 1;
		}
 
		else if(st[node].mul == 0)
		{
			st[node].sum = addMod( down_set(index, tl, mid, st[node].add), down_set(index+1, mid+1, tr, st[node].add) );
			st[node].add = 0;
			st[node].mul = 1;
		}	
		s = addMod( update_add(index, tl, mid, l, min(r,mid), value), update_add(index+1, mid+1, tr, max(l,mid+1), r, value) ); 
		
		st[node].sum = addMod(st[node].sum, s);
 
		return s;
		
	}
}
 
//-------------------------------FUNCTION FOR QUERY NUMBER 3, RANGE SET--------------------------------------//
 
int 
update_set(int node, int tl, int tr, int l, int r, int value)
{
	if(l>r)
		return 0;
 
	if(tl==l && tr==r)
	{
		int delta = subMod( mulMod( subMod(value,st[node].add), (tr-tl+1) ), mulMod( st[node].sum, st[node].mul) );
		st[node].add = value;
		st[node].sum = 0;
		st[node].mul = 0;
		return delta;
	}
	else 
	{
		int mid = getMid(tl, tr);
		int index = twice(node);
 
		if(st[node].mul > 1) 
		{
			st[node].sum = addMod(down_mul(index,  tl,  mid,st[node].mul)
							  ,down_mul(index+1,mid+1,tr,st[node].mul));
			st[node].mul=1;
		}
		else if(st[node].mul == 0) 
		{
			st[node].sum = addMod(down_set(index,  tl,  mid, st[node].add)
							  ,down_set(index+1,mid+1,tr,st[node].add));
			st[node].add=0;
			st[node].mul=1;
		}
		if(st[node].add != 0) 
		{
			st[node].sum = addMod(down_add(index,  tl,  mid,st[node].add)
							  ,down_add(index+1, mid+1,tr,st[node].add));
			st[node].add=0;
		}
		int s = addMod( update_set(index, tl, mid,   l, min(r, mid), value)
				      , update_set(index+1, mid+1, tr, max(l, mid+1),r, value));
 
		st[node].sum = addMod(st[node].sum,s);
 
		return s;
	}
}
 
//----------------------FUNCTION FOR QUERY NUMBER 2, RANGE MULTIPLICATION----------------------------------//
 
int 
update_mul(int node, int tl, int tr, int l, int r, int value)
{
	if(r<l)
		return 0;
 
	if(l == tl && r == tr) 
	{
		int delta = mulMod(addMod(mulMod((tr-tl+1),st[node].add),mulMod(st[node].sum,st[node].mul)), (value-1));
 
		st[node].add = mulMod( st[node].add, value );
		st[node].mul = mulMod( st[node].mul, value );
		return delta; 
	}
	else 
	{
		int mid = getMid(tl, tr); 
		int index = twice(node);
		int s;
 
		if(st[node].mul > 1) 
		{
			st[node].sum = addMod(down_mul(index,  tl, mid, st[node].mul), down_mul(index+1, mid+1, tr, st[node].mul));
 
			st[node].mul=1;
		}
		else if(st[node].mul == 0) 
		{
			st[node].sum = addMod( down_set(index, tl, mid, st[node].add) ,down_set(index+1, mid+1, tr, st[node].add));
 
			st[node].add=0;
			st[node].mul=1;
		}
 
		if(st[node].add != 0) 
		{
			st[node].sum = addMod(down_add(index, tl, mid, st[node].add), down_add(index+1, mid+1, tr, st[node].add));
			st[node].add=0;
		}
 
		s = addMod( update_mul(index, tl, mid, l, min(r,mid), value)
				  , update_mul(index+1, mid+1, tr, max(l, mid+1), r, value));
 
		st[node].sum = addMod(st[node].sum,s);
 
		return s;
	}
}
	
 
 
//-----------------------------------BUILDING THE SEGMENT TREE---------------------------------------------//
 
void
BuildST(int node, int tl, int tr)
{
 
	if(tl == tr)								//LEAF NODES
	{
		st[node].sum = a[tl];
		st[node].add = 0;
		st[node].mul = 1;
	}
	else
	{
		int mid = getMid(tl, tr);					//DIVIDE
		int index = twice(node);
 
		BuildST( index, tl, mid);					//RECURSIVE CALLS
		BuildST( index+1, mid+1, tr);					//CONQUER
 
		st[node].add = 0;
		st[node].mul = 1;
 
		st[node].sum = addMod( st[index].sum , st[index+1].sum);	//ADDING CHILDREN (COMBINE STEP)
	}
}
				
int main()
{
 
	int i, q;
 
	n = scan_f();
	q = scan_f();
 
	for(i=1; i<=n; ++i)
		a[i] = scan_f();
 
	BuildST(1, 1, n);
 
	while(q--)
	{
		int qtype, l, r, v;					
 
		qtype = scan_f();
		l = scan_f();
		r = scan_f();
		if(qtype == 1)						//RANGE ADDITION
		{
			v = scan_f();
			update_add(1,1,n,l,r,v);
		}
		else if(qtype == 2)					//RANGE MULTIPLICATION
		{
			v = scan_f();
			update_mul(1,1,n,l,r,v);
		}
		else if(qtype == 3)					//RANGE SET
		{
			v = scan_f();
			update_set(1,1,n,l,r,v);
		}
		else if(qtype == 4)					//RANGE SUM
		{
			printf("%d\n",GetSum(1,1,n,l,r));
			
		}
	}
	return 0;
}
	
		 	
//----THE TREE IS MADE BY PRECOMPUTATION AND TAKES N*LOG(N) TIME,--------//
//----EACH OF THE RANGE UPDATE OF ANY KIND IS PERFORMED IN LOG(N) TIME,--//
//----SUM QUERY TAKES LOG(N) TIME.---------------------------------------//
 
//----THEREFORE, THE TOTAL COMPLEXITY IS N*LOG(N) + M*LOG(N)-------------//		
//----THE NAIVE APPROACH TAKES N*M TIME----------------------------------//
 
//-THIS PROBLEM WAS SOLVED BY TAKING HELP FROM ANOTHER USER'S SOLUTION AND ONLINE RESOURCES-//
// http://se7so.blogspot.in/2012/12/segment-trees-and-lazy-propagation.html // 


#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4;
ll MOD;

void Copy(ll A[N][N],ll B[N][N])
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            A[i][j]=B[i][j];
}

void Mul(ll A[N][N],ll B[N][N])
{
    ll C[N][N];
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            C[i][j]=0;
            for(int k=0;k<N;k++)
            {
                C[i][j]=(C[i][j]+(ll)A[i][k]*(ll)B[k][j])%MOD;
            }
        }
    }
    Copy(A,C);
}

void Power(ll A[N][N],int Exp)
{
    ll Ans[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};

    while(Exp)
    {
        if(Exp&1)
        {
            Mul(Ans,A);
        }
        Mul(A,A);
        Exp=Exp>>1;
    }
    Copy(A,Ans);
}

ll Solve(int K)
{
    if(K==0)
        return 0;
    if(K==1)
        return 1;
    if(K==2)
        return 2;

     ll A[4][4]={{1,1,1,0},{1,0,0,0},{0,0,1,1},{0,0,0,1}};
    Power(A,K-1);

    return (  (A[0][0]*1+A[0][1]*0+A[0][2]*1+A[0][3]*1)  %MOD);

}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int N,M;
        scanf("%d %d",&N,&M);
        MOD = M;
        printf("%lld\n",Solve(N));
    }
    return 0;
}


EXTENDED EUCLID:
#include < iostream >

int d, x, y;
void extendedEuclid(int A, int 😎 {
    if(B == 0) {
        d = A;
        x = 1;
        y = 0;
    }
    else {
        extendedEuclid(B, A%B);
        int temp = x;
        x = y;
        y = temp - (A/B)*y;
    }
}
φ(pk) = pk − pk−1 = pk−1(p − 1)G
C
D
(
A
,
B
)
==
1
GCD(A,B)==1 then 
T
o
t
i
eThe sum of all values of Totient Function of all divisors of 
N
N is equal to 
N
N.
n
t
(
A
)
×
T
o
t
i
e
n
t
(
B
)
Totient(A)×Totient(B) = 
T
o
t
i
e
n
t
(
A
⋅
B
)
Totient(A⋅B).
int main( ) {
•	The sum of all values of Totient Function of all divisors of NN is equal to NN.
•	The value of Totient function for a certain prime PP will always be P−1P−1 as the number PP will always have a GCDGCD of 11 with all numbers less than or equal to it except itself.
•	For 2 number A and B, if GCD(A,B)==1GCD(A,B)==1 then Totient(A)×Totient(B)Totient(A)×Totient(B) = Totient(AxB)Totient(AxB).________________________________________________

return 0;   
}

MOD MULTIPLICATIVE INVERSE:(IF M is composite)
int d,x,y;
int modInverse(int A, int M)
{
    extendedEuclid(A,M);
    return (x%M+M)%M;    //x may be negative
}

MOD MULTIPLICATIVE INVERSE:(IF M is prime):
int modInverse(int A,int M)
{
    return modularExponentiation(A,M-2,M);
}



PRIMS(ADDING VERTICES-SPANNING TREE)--(O(V+E)logV):
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <utility>

using namespace std;
const int MAX = 1e4 + 5;
typedef pair<long long, int> PII;
bool marked[MAX];
vector <PII> adj[MAX];

long long prim(int x){
    priority_queue<PII, vector<PII>, greater<PII> > Q;
    int y;
    long long minimumCost = 0;
    PII p;
    Q.push(make_pair(0, x));
    while(!Q.empty())    {
        // Select the edge with minimum weight
        p = Q.top();
        Q.pop();
        x = p.second;
        // Checking for cycle
        if(marked[x] == true)
            continue;
        minimumCost += p.first;
        marked[x] = true;
        for(int i = 0;i < adj[x].size();++i)
        {
            y = adj[x][i].second;
            if(marked[y] == false)
                Q.push(adj[x][i]);
        }
    }
    return minimumCost;
}

int main(){
    int nodes, edges, x, y;
    long long weight, minimumCost;
    cin >> nodes >> edges;
    for(int i = 0;i < edges;++i){
        cin >> x >> y >> weight;
        adj[x].push_back(make_pair(weight, y));
        adj[y].push_back(make_pair(weight, x));
    }
    // Selecting 1 as the starting node
    minimumCost = prim(1);
    cout << minimumCost << endl;
    return 0;
}

// finds all solutions to ax = b (mod n)
VI modular_linear_equation_solver(int a, int b, int n) {
  int x, y;
  VI solutions;
  int d = extended_euclid(a, n, x, y);
  if (!(b%d)) {
    x = mod (x*(b/d), n);
    for (int i = 0; i < d; i++)
      solutions.push_back(mod(x + i*(n/d), n));
  }
  return solutions;
}
// Chinese remainder theorem (special case): find z such that
// z % x = a, z % y = b.  Here, z is unique modulo M = lcm(x,y).
// Return (z,M).  On failure, M = -1.
PII chinese_remainder_theorem(int x, int a, int y, int b) {
  int s, t;
  int d = extended_euclid(x, y, s, t);
  if (a%d != b%d) return make_pair(0, -1);
  return make_pair(mod(s*b*x+t*a*y,x*y)/d, x*y/d);
}


// Chinese remainder theorem: find z such that
// z % x[i] = a[i] for all i.  Note that the solution is
// unique modulo M = lcm_i (x[i]).  Return (z,M).  On 
// failure, M = -1.  Note that we do not require the a[i]'s
// to be relatively prime.
PII chinese_remainder_theorem(const VI &x, const VI &a) {
  PII ret = make_pair(a[0], x[0]);
  for (int i = 1; i < x.size(); i++) {
    ret = chinese_remainder_theorem(ret.first, ret.second, x[i], a[i]);
    if (ret.second == -1) break;
  }
  return ret;
}

// computes x and y such that ax + by = c; on failure, x = y =-1
void linear_diophantine(int a, int b, int c, int &x, int &y) {
  int d = gcd(a,b);
  if (c%d) {
    x = y = -1;
  } else {
    x = c/d * mod_inverse(a/d, b/d);
    y = (c-a*x)/b;
  }
}

points :
// struct point_i { int x, y; }; // basic raw form, minimalist mode
struct point_i { int x, y; // whenever possible, work with point_i
      point_i() { x = y = 0; } // default constructor
      point_i(int _x, int _y) : x(_x), y(_y) {}
}; // user-defined
struct point { double x, y; // only used if more precision is needed
            point() { x = y = 0.0;
      } // default constructor
      point(double _x, double _y) : x(_x), y(_y) {}
}; // user-defined
sort points
struct point { double x, y;
      point() { x = y = 0.0; }
      point(double _x, double _y) : x(_x), y(_y) {}
      bool operator < (point other) const { // override less than operator
      if (fabs(x - other.x) > EPS) // useful for sorting
      return x < other.x; // first criteria , by x-coordinate
      return y < other.y; }
}; // second criteria, by y-coordinate
// in int main(), assuming we already have a populated vector<point> P
sort(P.begin(), P.end()); // comparison operator is defined above
//testing equal points
//Euclidean distance between two points

double dist(point p1, point p2) { // Euclidean distance

// hypot(dx, dy) returns sqrt(dx * dx + dy * dy)

return hypot(p1.x - p2.x, p1.y - p2.y); } // return double

//rotate point by degrees

// rotate p by theta degrees CCW w.r.t origin (0, 0)

point rotate(point p, double theta) {

11

double rad = DEG_to_RAD(theta); // multiply theta with PI / 180.0

return point(p.x * cos(rad) - p.y * sin(rad),

p.x * sin(rad) + p.y * cos(rad)); }

struct line { double a, b, c; }; //line equation

// the answer is stored in the third parameter (pass by reference)

void pointsToLine(point p1, point p2, line &l) {

if (fabs(p1.x - p2.x) < EPS) { // vertical line is fine

l.a = 1.0; l.b = 0.0; l.c = -p1.x; // default values

} else {

l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);

l.b = 1.0; // IMPORTANT: we fix the value of b to 1.0

l.c = -(double)(l.a * p1.x) - p1.y;

} }

//parallel and same lines

bool areParallel(line l1, line l2) { // check coefficients a & b

return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }

bool areSame(line l1, line l2) { // also check coefficient c

return areParallel(l1 ,l2) && (fabs(l1.c - l2.c) < EPS);}

//intersection point of two lines

// returns true (+ intersection point) if two lines are intersect

bool areIntersect(line l1, line l2, point &p) {

if (areParallel(l1, l2)) return false; // no intersection

// solve system of 2 linear algebraic equations with 2 unknowns

p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);

// special case: test for vertical line to avoid division by zero

if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);

else p.y = -(l2.a * p.x + l2.c);

return true; }

//distance between line and point

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

// returns the distance from p to the line defined by

// two points a and b (a and b must be different)

// the closest point is stored in the 4th parameter (byref)

double distToLine(point p, point a, point b, point &c) {

// formula: c = a + u * ab

vec ap = toVec(a, p), ab = toVec(a, b);

double u = dot(ap, ab) / norm_sq(ab);

c = translate(a, scale(ab, u)); // translate a to c

return dist(p, c); } // Euclidean distance between p and c

//distance between point and line segment

// returns the distance from p to the line segment ab defined by

// two points a and b (still OK if a == b)

// the closest point is stored in the 4th parameter (byref)

12

double distToLineSegment(point p, point a, point b, point &c) {

vec ap = toVec(a, p), ab = toVec(a, b);

double u = dot(ap, ab) / norm_sq(ab);

if (u < 0.0) { c = point(a.x, a.y); // closer to a

return dist(p, a); } // Euclidean distance between p and a

if (u > 1.0) { c = point(b.x, b.y); // closer to b

return dist(p, b); } // Euclidean distance between p and b

return distToLine(p, a, b, c); } // run distToLine as above

//Intersection of line segments

// line segment from c to d

bool SegmentsIntersect(PT a, PT b, PT c, PT d) {

if (LinesCollinear(a, b, c, d)) {

if (dist2(a, c) < EPS || dist2(a, d) < EPS ||dist2(b, c) < EPS || dist2(b, d) < EPS)

return true;

if (dot(c‐a, c‐b) > 0 && dot(d‐a, d‐b) > 0 && dot(c‐b, d‐b) > 0)

return false;

return true;

}

if (cross(d‐a, b‐a) * cross(c‐a, b‐a) > 0) return false;

if (cross(a‐c, d‐c) * cross(b‐c, d‐c) > 0) return false;

return true;

}

//point inside, outside or on the circle

int insideCircle(point_i p, point_i c, int r) { // all integer version

int dx = p.x - c.x, dy = p.y - c.y;

int Euc = dx * dx + dy * dy, rSq = r * r; // all integer

return Euc < rSq ? 0 : Euc == rSq ? 1 : 2; } //inside/border/outside

bool circle2PtsRad(point p1, point p2, double r, point &c) {

double d2 = (p1.x - p2.x) * (p1.x - p2.x) +(p1.y - p2.y) * (p1.y - p2.y);

double det = r * r / d2 - 0.25;

if (det < 0.0) return false;

double h = sqrt(det);

c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;

c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;

return true; } // to get the other center, reverse p1 and p2

//incircle of triangle

double rInCircle(double ab, double bc, double ca) {

return area(ab, bc, ca) / (0.5 * perimeter(ab, bc, ca)); }

double rInCircle(point a, point b, point c) {

return rInCircle(dist(a, b), dist(b, c), dist(c, a)); }

//circumcirlce of triangle

double rCircumCircle(double ab, double bc, double ca) {

return ab * bc * ca / (4.0 * area(ab, bc, ca)); }

double rCircumCircle(point a, point b, point c) {

return rCircumCircle(dist(a, b), dist(b, c), dist(c, a)); }

13

//Area of polygon

// returns the area, which is half the determinant

double area(const vector<point> &P) {

double result = 0.0, x1, y1, x2, y2;

for (int i = 0; i < (int)P.size()-1; i++) {

x1 = P[i].x; x2 = P[i+1].x;

y1 = P[i].y; y2 = P[i+1].y;

result += (x1 * y2 - x2 * y1);

}

return fabs(result) / 2.0; }

//point inside or outside polygon

// returns true if point p is in either convex/concave polygon P

bool inPolygon(point pt, const vector<point> &P) {

if ((int)P.size() == 0) return false;

double sum = 0; // assume the first vertex is equal to the last vertex

for (int i = 0; i < (int)P.size()-1; i++) {

if (ccw(pt, P[i], P[i+1]))

sum += angle(P[i], pt, P[i+1]); // left turn/ccw

else sum -= angle(P[i], pt, P[i+1]); } // right turn/cw

return fabs(fabs(sum) - 2*PI) < EPS; }


points :
// struct point_i { int x, y; }; // basic raw form, minimalist mode
struct point_i { int x, y; // whenever possible, work with point_i
      point_i() { x = y = 0; } // default constructor
      point_i(int _x, int _y) : x(_x), y(_y) {}
}; // user-defined
struct point { double x, y; // only used if more precision is needed
            point() { x = y = 0.0;
      } // default constructor
      point(double _x, double _y) : x(_x), y(_y) {}
}; // user-defined
sort points
struct point { double x, y;
      point() { x = y = 0.0; }
      point(double _x, double _y) : x(_x), y(_y) {}
      bool operator < (point other) const { // override less than operator
      if (fabs(x - other.x) > EPS) // useful for sorting
      return x < other.x; // first criteria , by x-coordinate
      return y < other.y; }
}; // second criteria, by y-coordinate
// in int main(), assuming we already have a populated vector<point> P
sort(P.begin(), P.end()); // comparison operator is defined above
//testing equal points


//testing equal points

struct point { 
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	// use EPS (1e-9) when testing equality of two floating points
	bool operator == (point other) const {
	return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); 
} };


//LCA
const int max_nodes, log_max_nodes;
int num_nodes, log_num_nodes, root;
vector<int> children[max_nodes]; // children[i] contains the children of node i
int A[max_nodes][log_max_nodes+1]; // A[i][j] is the 2^j‐th ancestor of node i, or ‐1 if that ancest
//or does not exist
int L[max_nodes]; // L[i] is the distance between node i and the root
// floor of the binary logarithm of n
int lb(unsigned int n){
	if(n==0)
		return ‐1;
	int p = 0;
	if (n >= 1<<16) { n >>= 16; p += 16; }
	if (n >= 1<< 8) { n >>= 8; p += 8; }
	if (n >= 1<< 4) { n >>= 4; p += 4; }
	if (n >= 1<< 2) { n >>= 2; p += 2; }
	if (n >= 1<< 1) { p += 1; }
	return p;
}
void DFS(int i, int l){
	L[i] = l;
	for(int j = 0; j < children[i].size(); j++)
		DFS(children[i][j], l+1);
}

int LCA(int p, int q){
	// ensure node p is at least as deep as node q
	if(L[p] < L[q])
		swap(p, q);
	// "binary search" for the ancestor of node p situated on the same level as q
	for(int i = log_num_nodes; i >= 0; i‐‐)
		if(L[p] ‐ (1<<i) >= L[q])
			p = A[p][i];
		if(p == q)
			return p;
	// "binary search" for the LCA
	for(int i = log_num_nodes; i >= 0; i‐‐)
		if(A[p][i] != ‐1 && A[p][i] != A[q][i])	{
			p = A[p][i];
			q = A[q][i];
		}
	return A[p][0];
}

int main(int argc,char* argv[])
{
// read num_nodes, the total number of nodes
log_num_nodes=lb(num_nodes);
for(int i = 0; i < num_nodes; i++)
{
	int p;
	// read p, the parent of node i or ‐1 if node i is the root
	A[i][0] = p;
	if(p != ‐1)

		children[p].push_back(i);
	else
		root = i;
}
// precompute A using dynamic programming
for(int j = 1; j <= log_num_nodes; j++)
	for(int i = 0; i < num_nodes; i++)
		if(A[i][j‐1] != ‐1)
			A[i][j] = A[A[i][j‐1]][j‐1];
		else
			A[i][j] = ‐1;
	// precompute L
	DFS(root, 0);
	return 0;
}

//LCA using RMQ LCA(U,V) = MIN(E[H[U]....H[V])
int L[2*MAX_N], E[2*MAX_N], H[MAX_N], idx;
void dfs(int cur, int depth) {
	H[cur] = idx;
	E[idx] = cur;
	L[idx++] = depth;
	for (int i = 0; i < children[cur].size(); i++) {
		dfs(children[cur][i], depth+1);
		E[idx]= cur; // backtrack to current node
		L[idx++]= depth;
	}
}
void buildRMQ(){
	idx= 0;
	memset(H,-1, sizeof H);
	dfs(0, 0); // we assume that the root is at index 0
}

int LCSubStr(char *X, char *Y, int m, int n){
    // Create a table to store lengths of longest common suffixes of
    // substrings.   Notethat LCSuff[i][j] contains length of longest
    // common suffix of X[0..i-1] and Y[0..j-1]. The first row and
    // first column entries have no logical meaning, they are used only
    // for simplicity of program
    int LCSuff[m+1][n+1];
    int result = 0;  // To store length of the longest common substring
 
    /* Following steps build LCSuff[m+1][n+1] in bottom up fashion. */
    for (int i=0; i<=m; i++)
    {
        for (int j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
                LCSuff[i][j] = 0;
 
            else if (X[i-1] == Y[j-1])
            {
                LCSuff[i][j] = LCSuff[i-1][j-1] + 1;
                result = max(result, LCSuff[i][j]);
            }
            else LCSuff[i][j] = 0;
        }
    }
    return result;
}
