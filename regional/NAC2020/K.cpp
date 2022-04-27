#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 2e5 + 10;
int head[N], now;
struct edges{
	int to, next;
}edge[N << 1];
void add(int u, int v){ edge[++now] = {v, head[u]}; head[u] = now; }
int n, fa[N][22], dep[N];
void dfs(int x){
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(v == fa[x][0]) continue;
		fa[v][0] = x;
		dep[v] = dep[x] + 1;
		dfs(v);
	}
}
int LCA(int u, int v){
	if(dep[u] < dep[v]) swap(u, v);
	int k = dep[u] - dep[v];
	for(int i = 0; i <= 20; i++)
	  if((1 << i) & k) u = fa[u][i];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--)
	  if(fa[u][i] != fa[v][i])
	    u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
int main(){
	int Q;
	scanf("%d%d", &n, &Q);
	for(int i = 1; i < n; i++){
		int x, y; scanf("%d%d", &x, &y);
		add(x, y); add(y, x);
	}
	dep[1] = 1;
	dfs(1);
	for(int j = 0; j <= 20; j++)
	  for(int i = 1; i <= n; i++)
	    fa[i][j + 1] = fa[fa[i][j]][j];
	while(Q--){
		int x, y;
		scanf("%d%d", &x, &y);
		int lca = LCA(x, y);
		int k = dep[x] + dep[y] - 2 * dep[lca] + 1;
		printf("%lld\n", 1LL * k * (k + 1) / 2 + n - k);

	}
	return 0;
}
