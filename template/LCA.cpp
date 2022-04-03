#include<bits/stdc++.h>
using namespace std;
const int N=500050;
struct edge{
	int to,next;
}edge[N<<1];
int head[N],n,m,root,now,fa[N][40],dep[N];
void add(int x,int y){
	edge[++now]={y,head[x]};
	head[x]=now;
}
void dfs(int x, int father){
	fa[x][0] = father;
	for(int i = head[x]; i; i=edge[i].next){
		int v = edge[i].to;
		if(v != father){
			dep[v] = dep[x] + 1;
			dfs(v, x);
		}
	}
}
int lca(int u, int v){
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
	scanf("%d%d%d",&n, &m, &root);
	int x,y;
	for(int i = 1;i < n; i++){
		scanf("%d%d",&x, &y);
		add(x, y); add(y, x);
	}
	dfs(root, root);
	for(int j = 0; j <= 20; j++)
	  for(int i = 1; i <= n; i++)
	    fa[i][j + 1] = fa[fa[i][j]][j];
	while(m--){
		scanf("%d%d",&x, &y);
		printf("%d\n", lca(x, y));
	}
	return 0;
}
