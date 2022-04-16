#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
typedef pair<int, int> P;
const int N = 3e5 + 10;
int head[N], now, dfn[N], low[N], bridge[N << 1], num, n, m;
bool dir[N << 1];
struct edges{
	int to, next;
}edge[N << 1];
void add(int u, int v){ edge[++now] = {v, head[u]}; head[u] = now; }
void tarjan(int x, int in_edge){
	dfn[x] = low[x] = ++num;
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(!dfn[v]){
			dir[i] = 1;
			tarjan(v, i);
			low[x] = min(low[x], low[v]);

			if(low[v] > dfn[x])
				bridge[i] = bridge[i ^ 1] = true;
		}
		else if(i != (in_edge ^ 1)){
			low[x] = min(low[x], dfn[v]);
			if(!dir[i] && !dir[i ^ 1])
				dir[i] = 1;
		}
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
		if(bridge[i]){
			printf("0\n");
			return 0;
		}
	}
	
	for(int i = 2; i < now; i += 2){
		if(dir[i]) printf("%d %d\n", edge[i ^ 1].to, edge[i].to);
		else printf("%d %d\n", edge[i].to, edge[i ^ 1].to);
	}

	return 0;
}


