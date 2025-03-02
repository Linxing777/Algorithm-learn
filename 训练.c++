#include<bits/stdc++.h>
using namespace std;
#define ll long long
//高精度*小精度 A*b 
vector<int> mul(vector<int> &A,int b)
{
	vector<int> C;
	int t=0;//进位
	for(int i=0;i<A.size() || t;i++)
	{
		if(i<A.size()) t+=A[i]*b;//将b与A[i]相乘，而不是b的其中一位与A[i]相乘 
		C.push_back(t%10);  //相乘后只取最后一位的数 
		t/=10;    
	} 
	return C;
}

int main()
{
	string a;
	int b;
	cin>>a>>b;//a="123456"
	vector<int> A;
	
	for(int i=a.size()-1;i>=0;i--) A.push_back(a[i]-'0');//A=[6,5,4,3,2,1]
	
	vector<int> C=mul(A,b);
	
	for(int i=C.size()-1;i>=0;i--) cout<<C[i];
	
	return 0;
}

//并查集
int pre[10005];
int rank[10005];
void init(int n){
	for(int i=0;i<n;i++){
		pre[i]=i;
		rank[i]=1;
	}
} 
int find(int x){
	if(pre[x]==x)return x;
	return pre[x]=find(pre[x]);
}
bool join(int x,int y){
	x=find(x);
	y=find(y);
	if(x==y)return false;
	if(rank[x]>rank[y])pre[y]=x;
	else{
		if(rank[x]==rank[y])rank[y]++;
		pre[x]=y;
		}
	return true;	
}
bool isSame(int x, int y)      		
{
    return find(x) == find(y);  	
}
//容斥原理（属于难题应用） 
//1~~n不能被2，3，5整除
//A U B U C==A+B+C-A*B-A*C-B*C+A*B*C 
//A∪B =|A∪B| = |A|+|B| - |A∩B |（奇加偶减） 
void random(){
	int n;
	cin>>n;
	int ans=0;
	ans=n/2+n/3+n/5;
	ans-=n/2*3+n/2*5+n/3*5;
	ans+=n/2*3*5;
	cout<<n-ans;
} 
//快速幂取模
long long quck(long long a,long long b,long long mod){
	long long ans=1;
	a=a%mod;
	while(b){
		if(b&1)ans=(ans*a)%mod;
		b>>=1;
		a=(a*a)%mod;
	}
	return ans;
}
//BFS 八数码 （最短路：只能距离为1才能最短路用bfs） 
int bfs(string s){
	int pv[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
	string end="123804765";
	queue<string> q;
	map<string,int> mp;	
	q.push(s);
	mp[s]=0;
	while(q.size()){
		auto t=q.front();
		q.pop();
		int l=mp[t];
		if(t==end)return l;
		int di=t.find('0');
		int x=di/3,y=di%3;
		for(int i=0;i<4;i++){
			int dx=x+pv[i][0],dy=y+pv[i][1];
			if(dx>=0&&dx<3&&dy>=0&&dy<3){
				swap(t[di],t[dx*3+dy]);
				if(!mp.count(t)){
					mp[t]=l+1;
					q.push(t);
				}
				swap(t[di],t[dx*3+dy]);
			}
		}
	}

} 
 //领接表（有向图）
 //N点的个数，M边
const int N=100005,M=N*2;
int h[N],e[M],en[M],idx;
//----a点指向b点连接 Tree存储 
void add(int a,int b){
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++; 
}
//Tree的深度遍历
bool st[N];
void dfs(int u){
	st[u]=true;//这个点被找过了
	for(int i=h[u];i!=-1;i=ne[i]){
		int j=e[i];
		if(!st[j])dfs(j);
	} 
} 
//Tree的广度遍历（最短路：只能距离为1才能最短路用bfs） 1---n
int bfs(int start){
	queue<int> q;
	int dist[N]={-1};
	dist[1]=0;
	q.push(start);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i = h[u]; i != -1; i = ne[u]){
			int j = e[u];
			if(!dist[u]){
				dist[j] = dist[u] + 1;
				q.push(j);
			}
		}
	}
	return dist[N]; 
	
} 
void MainTree(){
	memset(h,-1, sizeof h);
} 

 



//----数的重心最小值 (深度搜索)
/*给定一颗树，树中包含 n 个结点（编号 1～n）和 n?1 条无向边。
请你找到树的重心，并输出将重心删除后，剩余各个连通块中点数的最大值。*/
//9
//1 2
//1 7
//1 4
//2 8
//2 5
//4 3
//3 9
//4 6

//4
 
int h[N],e[M],ne[M],idx;
bool st[N];
int ans=0;
void add(int a,int b){
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++;
} 
int dfs(int u){
	st[u]=true;
	int sum=1,res=0;
	for(int i=h[u];i!=-1;i=ne[i]){
		int j=e[i];
		if(!st[j]){
			int s = dfs(j);
			sum += s;
			res = max(res,s);
		}
		
	}
	res=max(res,n - sum);
	ans=min(ans,res)
	return ans;
}
void TreeC(){
	int n;
	cin >> n;
	memset(h, -1 , sizeof h);
	for(int i = 0; i < n; i ++ ){
		int a, b;
		cin >> a >>b;
		add(a, b);
		add(b ,a);
	}
	dfs(1);
	cout << ans << endl;
} 
//拓扑序列（只有 有向图  只有广度搜索的应用  必须无环）-------所有的边都是从前指向后的 
int n,m; // 顶点数,题目中最大边数
int d[N]; // 存储每个顶点的入度
queue<int> tp; // 记录q中顶点的出队顺序(拓扑序)
int h[N]; // 存储每个顶点起始边的编号,默认-1表示无边相连
int e[M]; // e[i]:编号为i的边可达的顶点编号
int ne[M]; // ne[i]:编号为i的边的下一条边的编号是ne[i]
int idx; // 边的编号,建边因子

// 链式前向星
void add(int a,int b) {
	e[idx]=b;
	ne[idx]=h[a]; // 头插法思想
	h[a]=idx++;
}

// 拓扑序存储于tp队列中,如果能形成拓扑序返回true
bool tuopu() {
	queue<int> q;
	int temp=0;
	for(int i=1;i<=n;i++) {
		// 如果入度为0则加入队列
		if(d[i]==0) 
			q.push(i);
	}
	while(q.size()) {
		int x=q.front();
		q.pop();
	    temp++;
		tp.push(x); // 出队顺序即拓扑序
		// 遍历x的所有出边
		for(int i=h[x];i!=-1;i=ne[i]) {
			int j=e[i];
			// 如果去掉边(i,j)后j的入度变为0,则加入队列
			if(--d[j]==0) q.push(j);
		}
	}
	return temp==n;
}

int main() {
	cin>>n>>m;
	memset(h,-1,sizeof h); // 链式前向星邻接表初始化
	for(int i=1;i<=m;i++) {
	    int a,b;
	    cin>>a>>b;
	    add(a,b);
	    d[b]++;
	}
	if(tuopu()){
	    while(tp.size()){
	        cout<<tp.front()<<" ";
	        tp.pop();
	    }
	}else cout<<-1;
	return 0;
}

//单源最短路（x节点到n节点的最短路径）
//1.所有边权为正数 n点数，m边数 n<=10^4
//--------Dij算法 n^2 遍很多 （链接矩阵）----重边，环 
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int n,m;
int g[N][N];
int dist[N];
bool st[N];

int dij(int x){
	memset(dist,0x3f,sizeof dist);
	dist[x]=0;
	for(int i=0;i<n;i++){
		int t=-1;
		for(int j=1;j<=n;j++)
			if(!st[j]&&(t==-1||dist[t]>dist[j]))
				t=j;
		
		for(int j=1;j<=n;j++){
			dist[j]=min(dist[j],dist[t]+g[t][j]);
		} 
		st[t]=true;
	}
	if(dist[n]==0x3f3f3f3f)return -1;
	return dist[n]; 
	
}



int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	memset(g,0x3f,sizeof g);
	while(m--){
		int a,b,c;
		cin>>a>>b>>c;
		g[a][b]=min(g[a][b],c);
	}
	int t=dij();
	cout<<t<<endl;
	return 0;
}

//--------堆优Dij算法 mlogn   点很多 n>=10^5 不用担心重边和环 
#include<bits/stdc++.h>
using namespace std;
#define PII pair<int,int> 
const int N=100010;
const int M=N*2;
int n,m;
int h[N],e[M],w[M],ne[M],idx;
int dist[N];
bool st[N];
void add(int a,int b,int c){
	e[idx]=b;
	w[idx]=c;
	ne[idx]=h[a];
	h[a]=idx++;
} 

void dij(){
	memset(dist,0x3f,sizeof dist);
	priority_queue<PII,vector<PII>,greater<PII>> q;
	dist[1]=0;
	q.{0,1};
	while(q.size()){
		auto it=q.top();
		q.pop();
		int v=it.second,d=it.first;
		if(st[v])continue;
		st[v]=true;
		for(int i=h[v];i!=-1;i=ne[i]){
			int u=e[i];
			if(dist[u]>d+w[i]){
				dist[u]=d+w[i];
				q.push({dist[u],u});
			}
		}
	
	}
}


int main(){
	cin>>n>>m>>s;
	memset(h,-1,sizeof h);
	while(m--){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
	}
	dij();
	for(int i=1;i<=n;i++)
		cout<<dist[i]<<' ';
	return 0;
	
	
}


//2.边权可以正 ，负数 
//------Bellman-Ford   nm  (不超过k条边最短)
#include<bist/stdc++.h>
using namespace std;
const int N=10010;
int dist[N],backup[N];
struct Edg{
	int a,b,w;
}edg[N];

int bellman(){
	for(int i=0;i<k;i++){
		memcpy(backup,dist,sizeof dist);
		for(int j=0;j<m;j++){
			dist[edg[j].b]=min(dist[edg[j].b],backup[edg[j].a]+edg[j].w);
		}
	}
	if(dist[n]>0x3f3f3f3f/2)return -1;
	return dist[n];
	
}


int main(){
	cin>>n>>m>>k;
	for(int i=0;i<m;i++){
		int a,b,w;
		cin>>a>>b>>w;
		edg[i]={a,b,w}; 
	}	
	memset(dist,0x3f,sizeof dist);
	int ans=bellman();
	if(t==-1)cout<<"impossible"<<endl;
	else cout<<t<<endl;
	
	
}

//------SPFA   m   ---  nm (所有边最短) 
#include<bits/stdc++.h>
using namespace std;
const int N=330;
const int M=100000;
int n,m;
int h[N],e[M],w[M],ne[M],idx;
bool st[N];
int dist[N];

void add(int a,int b,int c){
	e[idx]=b;
	w[idx]=c;
	ne[idx]=h[a];
	h[a]=idx++;
} 

int spfa(int x){
	memset(dist,0x3f,sizeof dist);
	dist[x]=0;
	st[x]=true;
	queue<int> q;
	q.push(x);
	while(q.size()){
		int v = q.front();
		q.pop();
		st[v] = false;
		for(int i = h[v]; i != -1; i = ne[i]){
			int u = e[i];
			if(dist[u] > dist[v] + w[i]){
				dist[u]  = dist[v] + w[i];
				if(!st[u]){
					q.push(u);
					st[u]=true;
				}
			}
			
		} 
	}
	for(int i = 1; i <= 10; i ++)cout << dist[i] << " ";
	cout << endl;	
	return dist[2];
}
int main(){
	ios :: sync_with_stdio(false);
	cin>>n>>m;
	memset(h,-1,sizeof h);
	for(int i = 1; i <= 10 ; i++){
		for(int j = 1; j <= 10; j++){
			int w;
			cin >> w;
			add(i, j, w);
		} 
	}
	int sum=0;
	for(int i=1; i <= n; i ++){
		for(int j = 1 ;j <= m ; j ++){
			int u;
			cin >> u;
			if(u == 1 || u == -1)continue;
			memset(st,0,sizeof st);
			sum += spfa(u+1); 
		}
	}
	cout << sum << endl;
	return 0;
	
	
}

//多源汇最短路 （多个点到x点的最短路） 
//------Floyd n^3
#include<bits/stdc++.h>
using namespace std;

const int N = 105, INF = 1e9;
int n, m, q;
int d[N][N];

void floyd()
{
	for(int k = 1; k <= n; k ++ )
		for(int i = 1; i <= n; i ++ )
			for(int j = 1; j <= n; j ++ )
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		
}

int main(){
	cin >> n >> m >>q;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j ++ )
			if(i == j) d[i][j] = 0;
			else d[i][j] = INF;
	
	while(m -- )
	{
		int a, b, w;
		cin >> a >> b >>w;
		
		d[a][b] = min(d[a][b], w); 
	}
	
	floyd();
	
	while(q -- )
	{
		int a, b;
		cin >> a >> b;
		cout << d[a][b] << endl;
	}	
	
	return 0;
}
///------最小生成树-----无向图 

//————prim--n^2
#include<bits/stdc++..h>
using namespace std;
const int N = 100010;
int g[N][N];
int dist[N];
bool st[N];
int n, m;
int INF = 0x3f3f3f3f;
int prim(){
	memset(dist, 0x3f, sizeof dist);
	int res = 0;
	for(int i = 0; i < n; i ++ ){
		int t = -1;
		for(int j = 1; j <= n; j ++ )
			if(!st[t] && (t == -1 || dist[t] > dist[j]))
				t = j;
		if(i && dist[t] == INF) return INF;
		if(i) res += dist[t];
		st[t] = true;
		for(int j = 1; j <= n; j ++ )
			dist[j] = min(dist[j], g[t][j]);
	}
	
	return res;
	
}

int main(){
	ios :: sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	memset(g, 0x3f, sizeof g);
	while(m -- ){
		int a, b, c;
		cin >> a >> b >> c;
		g[a][b] = min(g[a][b], c);
	} 
	int ans = prim();
	if(ans == INF) cout << "impossble" << endl;
	else cout << ans <<endl;
}


//Kru ----mlogm 
//(并查集加上排序) 
#include <bits/stdc++.h>

using namespace std;
const int N = 100010, M = N << 1;
const int INF = 0x3f3f3f3f;

int n, m; // n条顶点,m条边
int res;  // 最小生成树的权值和
int cnt;  // 最小生成树的结点数

// Kruskal用到的结构体
struct Node {
    int a, b, c;
    bool const operator<(const Node &t) const {
        return c < t.c; // 边权小的在前
    }
} edge[M]; // 数组长度为是边数

// 并查集
int p[N];
int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

// Kruskal算法
void kruskal() {
    // 1、按边权由小到大排序
    sort(edge, edge + m);
    // 2、并查集初始化
    for (int i = 1; i <= n; i++) p[i] = i;
    // 3、迭代m次
    for (int i = 0; i < m; i++) {
        int a = edge[i].a, b = edge[i].b, c = edge[i].c;
        a = find(a), b = find(b);
        if (a != b)
            p[a] = b, res += c, cnt++; // cnt是指已经连接上边的数量
    }
    // 4、特判是不是不连通
    if (cnt < n - 1) res = INF;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edge[i] = {a, b, c};
    }
    kruskal();
    if (res == INF)
        puts("impossible");
    else
        printf("%d\n", res);
    return 0;
}

//---染色法 ---n+m
#include<bits/stdc++.h>
using namespace std;
const int N = 10010;
const int M = 20010;
int h[N], e[M], ne[M], idx;
int n, m;
int color[N];
void add(int a, int b){
	e[idx] = b, ne[idx]	= h[a], h[a] = idx ++;
}
bool dfs(int u, int c){
	color[u] = c;
	for(int i = h[u]; i != -1; i = ne[i]){
		int v = e[i];
		if(!color[v]){
			if(!dfs(v, 3 - c))return false;	
		}else if(color[v] == c) return false ;
	}
	return true;	
}
int main(){
	cin >> n >> m;
	memset(h, -1, sizeof h);
	while(m -- ){
		int a, b;
		cin >> a >> b;
		add(a, b);
		add(b, a);
	}
	bool f = true;
	for(int i = 1; i <= n; i ++ ){
		if(!color[i]){
			if(!dfs(i, 1)){
				f = false;
				break;
			}
		}
	if(f) cout << "yes" << endl;
	else cout << "no" << endl;
		
	} 
	
	return 0;
}




//匈牙利算法 O() <<<<<mn 
#include<bits/stdc++.h>
using namespace std;
const int N = 10000;
const int M = 100010;
int n1, n2, m;
int h[N], e[M], ne[M], idx;
bool st[N];
int match[N];
void add(int a, int b){
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}
bool dfs(int u){
	for(int i = h[u]; i != -1; i = ne[i]){
		int v = e[i];
		if(!st[v]){
			st[v] = 1;
			if(match[v] == 0 || dfs(match[v])){
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}


int main(){
	cin >> n1 >> n2 >> m;
	while(m -- ){
		int a, b;
		cin >> a >> b;
		add(a, b); 
	}
	int ans = 0;
	for(intl i = 1 ; i <= n1; i ++){
		memset(st, false , sizeof st);
		if(dfs(i))ans++;
	}
	cout << ans << endl;
	return 0;
}
//埃筛  n
#include<bits/stdc++.h>
using namespace std;
#define ll long long
//高精度*小精度 A*b 
vector<int> mul(vector<int> &A,int b)
{
	vector<int> C;
	int t=0;//进位
	for(int i=0;i<A.size() || t;i++)
	{
		if(i<A.size()) t+=A[i]*b;//将b与A[i]相乘，而不是b的其中一位与A[i]相乘 
		C.push_back(t%10);  //相乘后只取最后一位的数 
		t/=10;    
	} 
	return C;
}

int main()
{
	string a;
	int b;
	cin>>a>>b;//a="123456"
	vector<int> A;
	
	for(int i=a.size()-1;i>=0;i--) A.push_back(a[i]-'0');//A=[6,5,4,3,2,1]
	
	vector<int> C=mul(A,b);
	
	for(int i=C.size()-1;i>=0;i--) cout<<C[i];
	
	return 0;
}

//并查集
int pre[10005];
int rank[10005];
void init(int n){
	for(int i=0;i<n;i++){
		pre[i]=i;
		rank[i]=1;
	}
} 
int find(int x){
	if(pre[x]==x)return x;
	return pre[x]=find(pre[x]);
}
bool join(int x,int y){
	x=find(x);
	y=find(y);
	if(x==y)return false;
	if(rank[x]>rank[y])pre[y]=x;
	else{
		if(rank[x]==rank[y])rank[y]++;
		pre[x]=y;
		}
	return true;	
}
bool isSame(int x, int y)      		
{
    return find(x) == find(y);  	
}
//容斥原理（属于难题应用） 
//1~~n不能被2，3，5整除
//A U B U C==A+B+C-A*B-A*C-B*C+A*B*C 
//A∪B =|A∪B| = |A|+|B| - |A∩B |（奇加偶减） 
void random(){
	int n;
	cin>>n;
	int ans=0;
	ans=n/2+n/3+n/5;
	ans-=n/2*3+n/2*5+n/3*5;
	ans+=n/2*3*5;
	cout<<n-ans;
} 
//快速幂取模
long long quck(long long a,long long b,long long mod){
	long long ans=1;
	a=a%mod;
	while(b){
		if(b&1)ans=(ans*a)%mod;
		b>>=1;
		a=(a*a)%mod;
	}
	return ans;
}
//BFS 八数码 （最短路：只能距离为1才能最短路用bfs） 
int bfs(string s){
	int pv[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
	string end="123804765";
	queue<string> q;
	map<string,int> mp;	
	q.push(s);
	mp[s]=0;
	while(q.size()){
		auto t=q.front();
		q.pop();
		int l=mp[t];
		if(t==end)return l;
		int di=t.find('0');
		int x=di/3,y=di%3;
		for(int i=0;i<4;i++){
			int dx=x+pv[i][0],dy=y+pv[i][1];
			if(dx>=0&&dx<3&&dy>=0&&dy<3){
				swap(t[di],t[dx*3+dy]);
				if(!mp.count(t)){
					mp[t]=l+1;
					q.push(t);
				}
				swap(t[di],t[dx*3+dy]);
			}
		}
	}

} 
 //领接表（有向图）
 //N点的个数，M边
const int N=100005,M=N*2;
int h[N],e[M],en[M],idx;
//----a点指向b点连接 Tree存储 
void add(int a,int b){
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++; 
}
//Tree的深度遍历
bool st[N];
void dfs(int u){
	st[u]=true;//这个点被找过了
	for(int i=h[u];i!=-1;i=ne[i]){
		int j=e[i];
		if(!st[j])dfs(j);
	} 
} 
//Tree的广度遍历（最短路：只能距离为1才能最短路用bfs） 1---n
int bfs(int start){
	queue<int> q;
	int dist[N]={-1};
	dist[1]=0;
	q.push(start);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i = h[u]; i != -1; i = ne[u]){
			int j = e[u];
			if(!dist[u]){
				dist[j] = dist[u] + 1;
				q.push(j);
			}
		}
	}
	return dist[N]; 
	
} 
void MainTree(){
	memset(h,-1, sizeof h);
} 

 



//----数的重心最小值 (深度搜索)
/*给定一颗树，树中包含 n 个结点（编号 1～n）和 n?1 条无向边。
请你找到树的重心，并输出将重心删除后，剩余各个连通块中点数的最大值。*/
//9
//1 2
//1 7
//1 4
//2 8
//2 5
//4 3
//3 9
//4 6

//4
 
int h[N],e[M],ne[M],idx;
bool st[N];
int ans=0;
void add(int a,int b){
	e[idx]=b;
	ne[idx]=h[a];
	h[a]=idx++;
} 
int dfs(int u){
	st[u]=true;
	int sum=1,res=0;
	for(int i=h[u];i!=-1;i=ne[i]){
		int j=e[i];
		if(!st[j]){
			int s = dfs(j);
			sum += s;
			res = max(res,s);
		}
		
	}
	res=max(res,n - sum);
	ans=min(ans,res)
	return ans;
}
void TreeC(){
	int n;
	cin >> n;
	memset(h, -1 , sizeof h);
	for(int i = 0; i < n; i ++ ){
		int a, b;
		cin >> a >>b;
		add(a, b);
		add(b ,a);
	}
	dfs(1);
	cout << ans << endl;
} 
//拓扑序列（只有 有向图  只有广度搜索的应用  必须无环）-------所有的边都是从前指向后的 
int n,m; // 顶点数,题目中最大边数
int d[N]; // 存储每个顶点的入度
queue<int> tp; // 记录q中顶点的出队顺序(拓扑序)
int h[N]; // 存储每个顶点起始边的编号,默认-1表示无边相连
int e[M]; // e[i]:编号为i的边可达的顶点编号
int ne[M]; // ne[i]:编号为i的边的下一条边的编号是ne[i]
int idx; // 边的编号,建边因子

// 链式前向星
void add(int a,int b) {
	e[idx]=b;
	ne[idx]=h[a]; // 头插法思想
	h[a]=idx++;
}

// 拓扑序存储于tp队列中,如果能形成拓扑序返回true
bool tuopu() {
	queue<int> q;
	int temp=0;
	for(int i=1;i<=n;i++) {
		// 如果入度为0则加入队列
		if(d[i]==0) 
			q.push(i);
	}
	while(q.size()) {
		int x=q.front();
		q.pop();
	    temp++;
		tp.push(x); // 出队顺序即拓扑序
		// 遍历x的所有出边
		for(int i=h[x];i!=-1;i=ne[i]) {
			int j=e[i];
			// 如果去掉边(i,j)后j的入度变为0,则加入队列
			if(--d[j]==0) q.push(j);
		}
	}
	return temp==n;
}

int main() {
	cin>>n>>m;
	memset(h,-1,sizeof h); // 链式前向星邻接表初始化
	for(int i=1;i<=m;i++) {
	    int a,b;
	    cin>>a>>b;
	    add(a,b);
	    d[b]++;
	}
	if(tuopu()){
	    while(tp.size()){
	        cout<<tp.front()<<" ";
	        tp.pop();
	    }
	}else cout<<-1;
	return 0;
}

//单源最短路（x节点到n节点的最短路径）
//1.所有边权为正数 n点数，m边数 n<=10^4
//--------Dij算法 n^2 遍很多 （链接矩阵）----重边，环 
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int n,m;
int g[N][N];
int dist[N];
bool st[N];

int dij(int x){
	memset(dist,0x3f,sizeof dist);
	dist[x]=0;
	for(int i=0;i<n;i++){
		int t=-1;
		for(int j=1;j<=n;j++)
			if(!st[j]&&(t==-1||dist[t]>dist[j]))
				t=j;
		
		for(int j=1;j<=n;j++){
			dist[j]=min(dist[j],dist[t]+g[t][j]);
		} 
		st[t]=true;
	}
	if(dist[n]==0x3f3f3f3f)return -1;
	return dist[n]; 
	
}



int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	memset(g,0x3f,sizeof g);
	while(m--){
		int a,b,c;
		cin>>a>>b>>c;
		g[a][b]=min(g[a][b],c);
	}
	int t=dij();
	cout<<t<<endl;
	return 0;
}

//--------堆优Dij算法 mlogn   点很多 n>=10^5 不用担心重边和环 
#include<bits/stdc++.h>
using namespace std;
#define PII pair<int,int> 
const int N=100010;
const int M=N*2;
int n,m;
int h[N],e[M],w[M],ne[M],idx;
int dist[N];
bool st[N];
void add(int a,int b,int c){
	e[idx]=b;
	w[idx]=c;
	ne[idx]=h[a];
	h[a]=idx++;
} 

void dij(){
	memset(dist,0x3f,sizeof dist);
	priority_queue<PII,vector<PII>,greater<PII>> q;
	dist[1]=0;
	q.{0,1};
	while(q.size()){
		auto it=q.top();
		q.pop();
		int v=it.second,d=it.first;
		if(st[v])continue;
		st[v]=true;
		for(int i=h[v];i!=-1;i=ne[i]){
			int u=e[i];
			if(dist[u]>d+w[i]){
				dist[u]=d+w[i];
				q.push({dist[u],u});
			}
		}
	
	}
}


int main(){
	cin>>n>>m>>s;
	memset(h,-1,sizeof h);
	while(m--){
		int a,b,c;
		cin>>a>>b>>c;
		add(a,b,c);
	}
	dij();
	for(int i=1;i<=n;i++)
		cout<<dist[i]<<' ';
	return 0;
	
	
}


//2.边权可以正 ，负数 
//------Bellman-Ford   nm  (不超过k条边最短)
#include<bist/stdc++.h>
using namespace std;
const int N=10010;
int dist[N],backup[N];
struct Edg{
	int a,b,w;
}edg[N];

int bellman(){
	for(int i=0;i<k;i++){
		memcpy(backup,dist,sizeof dist);
		for(int j=0;j<m;j++){
			dist[edg[j].b]=min(dist[edg[j].b],backup[edg[j].a]+edg[j].w);
		}
	}
	if(dist[n]>0x3f3f3f3f/2)return -1;
	return dist[n];
	
}


int main(){
	cin>>n>>m>>k;
	for(int i=0;i<m;i++){
		int a,b,w;
		cin>>a>>b>>w;
		edg[i]={a,b,w}; 
	}	
	memset(dist,0x3f,sizeof dist);
	int ans=bellman();
	if(t==-1)cout<<"impossible"<<endl;
	else cout<<t<<endl;
	
	
}

//------SPFA   m   ---  nm (所有边最短) 
#include<bits/stdc++.h>
using namespace std;
const int N=330;
const int M=100000;
int n,m;
int h[N],e[M],w[M],ne[M],idx;
bool st[N];
int dist[N];

void add(int a,int b,int c){
	e[idx]=b;
	w[idx]=c;
	ne[idx]=h[a];
	h[a]=idx++;
} 

int spfa(int x){
	memset(dist,0x3f,sizeof dist);
	dist[x]=0;
	st[x]=true;
	queue<int> q;
	q.push(x);
	while(q.size()){
		int v = q.front();
		q.pop();
		st[v] = false;
		for(int i = h[v]; i != -1; i = ne[i]){
			int u = e[i];
			if(dist[u] > dist[v] + w[i]){
				dist[u]  = dist[v] + w[i];
				if(!st[u]){
					q.push(u);
					st[u]=true;
				}
			}
			
		} 
	}
	for(int i = 1; i <= 10; i ++)cout << dist[i] << " ";
	cout << endl;	
	return dist[2];
}
int main(){
	ios :: sync_with_stdio(false);
	cin>>n>>m;
	memset(h,-1,sizeof h);
	for(int i = 1; i <= 10 ; i++){
		for(int j = 1; j <= 10; j++){
			int w;
			cin >> w;
			add(i, j, w);
		} 
	}
	int sum=0;
	for(int i=1; i <= n; i ++){
		for(int j = 1 ;j <= m ; j ++){
			int u;
			cin >> u;
			if(u == 1 || u == -1)continue;
			memset(st,0,sizeof st);
			sum += spfa(u+1); 
		}
	}
	cout << sum << endl;
	return 0;
	
	
}

//多源汇最短路 （多个点到x点的最短路） 
//------Floyd n^3
#include<bits/stdc++.h>
using namespace std;

const int N = 105, INF = 1e9;
int n, m, q;
int d[N][N];

void floyd()
{
	for(int k = 1; k <= n; k ++ )
		for(int i = 1; i <= n; i ++ )
			for(int j = 1; j <= n; j ++ )
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		
}

int main(){
	cin >> n >> m >>q;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j ++ )
			if(i == j) d[i][j] = 0;
			else d[i][j] = INF;
	
	while(m -- )
	{
		int a, b, w;
		cin >> a >> b >>w;
		
		d[a][b] = min(d[a][b], w); 
	}
	
	floyd();
	
	while(q -- )
	{
		int a, b;
		cin >> a >> b;
		cout << d[a][b] << endl;
	}	
	
	return 0;
}
///------最小生成树-----无向图 

//————prim--n^2
#include<bits/stdc++..h>
using namespace std;
const int N = 100010;
int g[N][N];
int dist[N];
bool st[N];
int n, m;
int INF = 0x3f3f3f3f;
int prim(){
	memset(dist, 0x3f, sizeof dist);
	int res = 0;
	for(int i = 0; i < n; i ++ ){
		int t = -1;
		for(int j = 1; j <= n; j ++ )
			if(!st[t] && (t == -1 || dist[t] > dist[j]))
				t = j;
		if(i && dist[t] == INF) return INF;
		if(i) res += dist[t];
		st[t] = true;
		for(int j = 1; j <= n; j ++ )
			dist[j] = min(dist[j], g[t][j]);
	}
	
	return res;
	
}

int main(){
	ios :: sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	memset(g, 0x3f, sizeof g);
	while(m -- ){
		int a, b, c;
		cin >> a >> b >> c;
		g[a][b] = min(g[a][b], c);
	} 
	int ans = prim();
	if(ans == INF) cout << "impossble" << endl;
	else cout << ans <<endl;
}


//Kru ----mlogm 
//(并查集加上排序) 
#include <bits/stdc++.h>

using namespace std;
const int N = 100010, M = N << 1;
const int INF = 0x3f3f3f3f;

int n, m; // n条顶点,m条边
int res;  // 最小生成树的权值和
int cnt;  // 最小生成树的结点数

// Kruskal用到的结构体
struct Node {
    int a, b, c;
    bool const operator<(const Node &t) const {
        return c < t.c; // 边权小的在前
    }
} edge[M]; // 数组长度为是边数

// 并查集
int p[N];
int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

// Kruskal算法
void kruskal() {
    // 1、按边权由小到大排序
    sort(edge, edge + m);
    // 2、并查集初始化
    for (int i = 1; i <= n; i++) p[i] = i;
    // 3、迭代m次
    for (int i = 0; i < m; i++) {
        int a = edge[i].a, b = edge[i].b, c = edge[i].c;
        a = find(a), b = find(b);
        if (a != b)
            p[a] = b, res += c, cnt++; // cnt是指已经连接上边的数量
    }
    // 4、特判是不是不连通
    if (cnt < n - 1) res = INF;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edge[i] = {a, b, c};
    }
    kruskal();
    if (res == INF)
        puts("impossible");
    else
        printf("%d\n", res);
    return 0;
}

//---染色法 ---n+m
#include<bits/stdc++.h>
using namespace std;
const int N = 10010;
const int M = 20010;
int h[N], e[M], ne[M], idx;
int n, m;
int color[N];
void add(int a, int b){
	e[idx] = b, ne[idx]	= h[a], h[a] = idx ++;
}
bool dfs(int u, int c){
	color[u] = c;
	for(int i = h[u]; i != -1; i = ne[i]){
		int v = e[i];
		if(!color[v]){
			if(!dfs(v, 3 - c))return false;	
		}else if(color[v] == c) return false ;
	}
	return true;	
}
int main(){
	cin >> n >> m;
	memset(h, -1, sizeof h);
	while(m -- ){
		int a, b;
		cin >> a >> b;
		add(a, b);
		add(b, a);
	}
	bool f = true;
	for(int i = 1; i <= n; i ++ ){
		if(!color[i]){
			if(!dfs(i, 1)){
				f = false;
				break;
			}
		}
	if(f) cout << "yes" << endl;
	else cout << "no" << endl;
		
	} 
	
	return 0;
}




//匈牙利算法 O() <<<<<mn 
#include<bits/stdc++.h>
using namespace std;
const int N = 10000;
const int M = 100010;
int n1, n2, m;
int h[N], e[M], ne[M], idx;
bool st[N];
int match[N];
void add(int a, int b){
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}
bool dfs(int u){
	for(int i = h[u]; i != -1; i = ne[i]){
		int v = e[i];
		if(!st[v]){
			st[v] = 1;
			if(match[v] == 0 || dfs(match[v])){
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}


int main(){
	cin >> n1 >> n2 >> m;
	while(m -- ){
		int a, b;
		cin >> a >> b;
		add(a, b); 
	}
	int ans = 0;
	for(intl i = 1 ; i <= n1; i ++){
		memset(st, false , sizeof st);
		if(dfs(i))ans++;
	}
	cout << ans << endl;
	return 0;
}
//欧拉筛 
#include <bits/stdc++.h>

using namespace std;

// 欧拉筛
const int N = 1e6 + 10;
int primes[N], cnt; // primes[]存储所有素数
int st[N];          // st[x]存储x是否被筛掉

void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] * i <= n; j++) { // 捋着质数数组来
            st[primes[j] * i] = 1;                 // 质数因子的i倍被干掉
            if (i % primes[j] == 0) break;         // 只被它的最小质因子筛选一次
        }
    }
}

int main() {
    int n;
    cin >> n;
    get_primes(n);
    printf("%d\n", cnt);
    return 0;
}
//
// * 功能：分解质因数
// * @param x 待分解的质数因数
// */
void divide(int x) {
    for (int i = 2; i <= x / i; i++)
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) x /= i, s++;
            cout << i << ' ' << s << endl;
        }
    //如果还没有除开，就是还需要写一个
    if (x > 1) cout << x << ' ' << 1 << endl;
    cout << endl;
}
// 求所有约数
void get_divisors(int x) {
    for (int i = 1; i <= x / i; i++) // 枚举到sqrt即可
        if (x % i == 0) {
            nums.push_back(i);
            if (i != x / i) nums.push_back(x / i); // 如果 i==x/i 只存储一个，比如 5*5=25
        }
    sort(nums.begin(), nums.end()); // 排序输出
}
//一个数的约数个数 ----(r1+1)(r2+1)...(rk+1)
//r是这个数的质因数个数 
#include <bits/stdc++.h>

using namespace std;
#define int long long
typedef pair<int, int> PII;

const int N = 110;
const int MOD = 1e9 + 7;

unordered_map<int, int> primes;
int n;

signed main() {
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        for (int i = 2; i <= x / i; i++)
            while (x % i == 0) {
                x /= i;
                primes[i]++;
            }
        if (x > 1) primes[x]++;
    }

    int res = 1;
    for (auto p : primes) res = res * (p.second + 1) % MOD;

    printf("%lld\n", res);
}
//一个数的约数之和---(p1^0+p1^1+p1^2+...+p1^r1)(p2)..(pk)
//p是质因数,r是个数 
#include <bits/stdc++.h>

using namespace std;
#define int long long
typedef pair<int, int> PII;
const int N = 110;
const int MOD = 1e9 + 7;
unordered_map<int, int> primes;
int n;

signed main() {
    cin >> n;
    while (n--) {
        int x;
        cin >> x;
        for (int i = 2; i <= x / i; i++)
            while (x % i == 0) {
                x /= i;
                primes[i]++;
            }
        if (x > 1) primes[x]++;
    }

    int res = 1;
    for (auto p : primes) {
        int a = p.first, b = p.second; // 质数，几个
        int t = 1;
        while (b--) t = (t * a + 1) % MOD;//(p1^0+p1^1+p1^2+...+p1^r1)算这个 
        res = res * t % MOD;
    }
    printf("%lld\n", res);
}













































































































































































































































































































































































































































































































































































































































































































































































































































































