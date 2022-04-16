#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 4e5 + 10;
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
			tarjan(v, i);
			low[x] = min(low[x], low[v]);

			if(low[v] > dfn[x])
				bridge[i] = bridge[i ^ 1] = true;
			else {
				dir[i] = 1;
			}
		}
		else if(i != (in_edge ^ 1)){
			low[x] = min(low[x], dfn[v]);
			if(!dir[i] && !dir[i ^ 1])
			dir[i] = 1;
		}
	}
}
int c[N], dcc, cnt[N];
void dfs(int x){
	c[x] = dcc;
	cnt[dcc]++;
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(c[v] || bridge[i]) continue;
		dfs(v);
	}
}

typedef pair<int, int> P;
vector<P> to[N];
void dfs2(int x, int fa){
	for(auto v:to[x]){
		if(v.first == fa) continue;
		dir[v.second ^ 1] = 1;
		dfs2(v.first, x);
	}
}
int main(){
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	now = 1;
	for(int i = 1; i <= m; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y); add(y, x);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i]) tarjan(i, 0);

	for(int i = 1; i <= n; i++)
		if(!c[i]){
			dcc++;
			dfs(i);
		}
	int ans_val = 0, rt;
	for(int i = 1; i <= dcc; i++){
		if(cnt[i] > ans_val) rt = i;
		ans_val = max(ans_val, cnt[i]);
	}
	for(int i = 2; i <= now; i += 2){
		if(bridge[i] || bridge[i ^ 1]){
			to[c[edge[i ^ 1].to]].push_back({c[edge[i].to], i});
			to[c[edge[i].to]].push_back({c[edge[i ^ 1].to], i ^ 1});
		}
	}
	dfs2(rt, 0);

	printf("%d\n", ans_val);
	for(int i = 2; i <= now; i++){
		if(dir[i])
			printf("%d %d\n", edge[i ^ 1].to, edge[i].to);
	}

	return 0;
}
