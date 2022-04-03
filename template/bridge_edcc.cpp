#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 3e5 + 10;
int head[N], now, dfn[N], low[N], bridge[N << 1], num, n, m;
struct edges{
	int to, next;
}edge[N << 1];
void add(int u, int v){ edge[++now] = {v, head[u]}; head[u] = now; }
void tarjan(int x, int in_edge){
	dfn[x] = low[x] = ++num;
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
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
int c[N], dcc;
void dfs(int x){
	c[x] = dcc;
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(c[v] || bridge[i]) continue;
		dfs(v);
	}
}
int main(){
	scanf("%d%d", &n, &m);
	now = 1;
	for(int i = 1; i <= m; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y); add(y, x);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i]) tarjan(i, 0);
	for(int i = 2; i < now; i += 2){
		if(bridge[i])
			printf("%d %d\n", edge[i ^ 1].to, edge[i].to);
	}

	for(int i = 1; i <= n; i++)
		if(!c[i]){
			dcc++;
			dfs(i);
		}
	return 0;
}

