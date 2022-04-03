#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 1e5 + 10;
#define ll long long
int n, m;
ll val[N], w[N], fa[N], dp[N], dis[N], cnt[N], tot_w;
int head[N], now;
struct edges{
	int to, next, w;
}edge[N << 1];
void add(int u, int v, int w){ edge[++now] = {v, head[u], w}; head[u] = now; }
void dfs1(int x){
	dp[x] = 0;
	w[x] = val[x];
	cnt[x] = 1;
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(fa[x] == v) continue;
		fa[v] = x;
		dfs1(v);
		w[x] += w[v];
		cnt[x] += cnt[v];
		dis[x] += (dis[v] + edge[i].w * cnt[v]);
		dp[x] += (dp[v] + w[v] * edge[i].w);
	}
}
void dfs2(int x, int in_w){
	if(fa[x] != 0){
		dis[x] = dis[x] + (dis[fa[x]] - dis[x] - in_w * cnt[x]) + in_w * (n - cnt[x]);
		dp[x] = dp[x] + (dp[fa[x]] - dp[x] - in_w * w[x]) + in_w *(tot_w - w[x]);
	}
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(fa[x] == v) continue;
		dfs2(v, edge[i].w);
	}
}
int main(){
	// freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &val[i]), tot_w += val[i];
	for(int i = 1; i < n; i++){
		int x, y, z; scanf("%d%d%d", &x, &y, &z);
		add(x, y, z); add(y, x, z);
	}

	dfs1(1);
	dfs2(1, 0);
	// cout<<dp[1]<<" "<<dis[1]<<" "<<val[1]<<endl;
	for(int i = 1; i <= n; i++){
		printf("%lld\n", dp[i] + dis[i] * val[i]);
	}
	return 0;
}
