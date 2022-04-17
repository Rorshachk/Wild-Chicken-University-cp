#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1010;
int head[N], now;
struct edges{
	int to, next;
}edge[N << 1];
void add(int u, int v){ edge[++now] = {v, head[u]}; head[u] = now; }
int n, m, w[N], in_deg[N], out_deg[N], fa[N];
int get(int x){ return x == fa[x] ? x : fa[x] = get(fa[x]); }
void Merge(int x, int y){
	int tx = get(x), ty = get(y);
	if(tx != ty) fa[ty] = tx;
}
int dep[N], pre[N][20];
vector<int> leaves;
void dfs(int x, int f){
	pre[x][0] = f;
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		w[v] += w[x];
		dep[v] = dep[x] + 1;
		dfs(v, x);
	}
}
int LCA(int u, int v){
	if(dep[u] < dep[v]) swap(u, v);
	int k = dep[u] - dep[v];
	for(int i = 0; i <= 14; i++)
	  if((1 << i) & k) u = pre[u][i];
	if(u == v) return u;
	for(int i = 14; i >= 0; i--)
	  if(pre[u][i] != pre[v][i])
	    u = pre[u][i], v = pre[v][i];
	return pre[u][0];
}
int calc(int x, int y){
	if(get(x) != get(y)) return w[x] + w[y];
	int lca = LCA(x, y);
	return w[x] + w[y] - w[lca];
}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &w[i]), fa[i] = i;
	for(int i = 1; i <= m; i++){
		int x, y; scanf("%d%d", &x, &y);
		add(x, y); in_deg[y]++; out_deg[x]++;
		Merge(x, y);
	}
	for(int i = 1; i <= n; i++){
		if(in_deg[i] == 0) 
			dfs(i, i);
		if(out_deg[i] == 0)
			leaves.push_back(i);
	}

	for(int j = 0; j <= 14; j++)
	  for(int i = 1; i <= n; i++)
	    pre[i][j + 1] = pre[pre[i][j]][j];

	int ans = 1e9;
	for(int i = 0; i < leaves.size(); i++)
		for(int j = i + 1; j < leaves.size(); j++){
			ans = min(ans, calc(leaves[i], leaves[j]));
		}
	cout<<ans<<endl;
	return 0;
}
