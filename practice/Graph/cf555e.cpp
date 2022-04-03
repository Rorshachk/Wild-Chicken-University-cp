#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 3e5 + 10;
int head1[N], now1, dfn[N], low[N], bridge[N << 1], num;
int bel[N], num_bel, rt[N], n, m;
struct edges{
	int to, next;
}edge1[N << 1];
void add1(int u, int v){ edge1[++now1] = {v, head1[u]}; head1[u] = now1; }
void tarjan(int x, int in_edge){
	dfn[x] = low[x] = ++num;
	bel[x] = num_bel;
	for(int i = head1[x]; i; i = edge1[i].next){
		int v = edge1[i].to;
		if(!dfn[v]){
			tarjan(v, i);
			low[x] = min(low[x], low[v]);

			if(low[v] > dfn[x])
				bridge[i] = bridge[i ^ 1] = true;
		}
		else if(i != (in_edge ^ 1))
			low[x] = min(low[x], dfn[v]);
	}
}
int bel_dcc[N], dcc;
void dcc_dfs(int x){
	bel_dcc[x] = dcc;
	for(int i = head1[x]; i; i = edge1[i].next){
		int v = edge1[i].to;
		if(bel_dcc[v] || bridge[i]) continue;
		dcc_dfs(v);
	}
}
int head2[N], now2, dep[N], fa[N][25], dif1[N], dif2[N], w1[N], w2[N];
edges edge2[N << 1];
void add2(int u, int v){ edge2[++now2] = {v, head2[u]}; head2[u] = now2; }
void dep_dfs(int x, int father){
	fa[x][0] = father;
	for(int i = head2[x]; i; i=edge2[i].next){
		int v = edge2[i].to;
		if(v != father){
			dep[v] = dep[x] + 1;
			dep_dfs(v, x);
		}
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
void work_dfs(int x, int fa){
	w1[x] = dif1[x]; w2[x] = dif2[x];
	for(int i = head2[x]; i; i = edge2[i].next){
		int v = edge2[i].to;
		if(v == fa) continue;
		work_dfs(v, x);
		w1[x] += w1[v];
		w2[x] += w2[v];
	}
}
int main(){
	// freopen("input.txt", "r", stdin);
	int Q;
	scanf("%d%d%d", &n, &m, &Q);
	now1 = 1;
	for(int i = 1; i <= m; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		add1(x, y); add1(y, x);
	}
	for(int i = 1; i <= n; i++)
	  if(!dfn[i]){
		  num_bel++;
		  rt[num_bel] = i;
		  tarjan(i, 0);
	  }
	
	for(int i = 1; i <= n; i++)
		if(!bel_dcc[i]){
			++dcc;
			dcc_dfs(i);
		}

	now2 = 1;
	for(int i = 2; i <= now1; i++){
		int x = edge1[i ^ 1].to, y = edge1[i].to;
		if(bel_dcc[x] == bel_dcc[y]) continue;
		add2(bel_dcc[x], bel_dcc[y]);
	}

	for(int i = 1; i <= num_bel; i++)
	  dep_dfs(bel_dcc[rt[i]], bel_dcc[rt[i]]);

	for(int j = 0; j <= 20; j++)
	  for(int i = 1; i <= n; i++)
	    fa[i][j + 1] = fa[fa[i][j]][j];

	while(Q--){
		int x, y; scanf("%d%d", &x, &y);
		x = bel_dcc[x], y = bel_dcc[y];
		if(x == y) continue;
		if(bel[x] != bel[y]){
			puts("No");
			return 0;
		}

		int lca = LCA(x, y);
		dif1[x]++; dif1[lca]--;
		dif2[y]++; dif2[lca]--;
	}

	for(int i = 1; i <= num_bel; i++)
	  work_dfs(bel_dcc[rt[i]], bel_dcc[rt[i]]);
	for(int i = 1; i <= dcc; i++){
		if(w1[i] > 0 && w2[i] > 0){
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	return 0;
}


