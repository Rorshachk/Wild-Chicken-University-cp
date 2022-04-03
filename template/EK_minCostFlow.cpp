// EK, minCost max flow
#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;
#define ll long long
const int N = 5050, M = 50050;
const int INF = 1e9;
int head[N], now, pre[N];
struct edges{
	int to, next, limit, cost;
}edge[M << 1];
void add(int u, int v, int w, int c){
	edge[++now] = {v, head[u], w, c};
	head[u] = now;
}
int n, m, s, t;
ll ans, maxflow, incf[N], d[N];
bool vis[N];
bool spfa(){
	queue<int> q;
	for(int i = 1; i <= n; i++) d[i] = 1e18;
	memset(vis, 0, sizeof(vis));
	q.push(s); d[s] = 0; vis[s] = 1;
	incf[s] = 1e18;
	while(!q.empty()){
		int x = q.front(); vis[x] = 0; q.pop();
		for(int i = head[x]; i; i = edge[i].next){
			int v = edge[i].to;
			if(!edge[i].limit) continue;
			if(d[v] > d[x] + edge[i].cost){
				d[v] = d[x] + edge[i].cost;
				incf[v] = min(incf[x], 1LL * edge[i].limit);
				pre[v] = i;
				if(!vis[v]) vis[v] = 1, q.push(v);
			}
		}
	}
	if(d[t] > 1e9) return 0;
	return 1;
}
void update(){
	int x = t;
	while(x != s){
		int i = pre[x];
		edge[i].limit -= incf[t];
		edge[i ^ 1].limit += incf[t];
		x = edge[i ^ 1].to;
	}
	maxflow += incf[t];
	ans += d[t] * incf[t];
}
int main(){
	scanf("%d%d%d%d", &n, &m, &s, &t);
	now = 1;
	for(int i = 1; i <= m; i++){
		int x, y, z1, z2;
		scanf("%d%d%d%d", &x, &y, &z1, &z2);
		add(x, y, z1, z2);
		add(y, x, 0, -z2);
	}
	while(spfa()) update();
	cout<<maxflow<<" "<<ans<<endl;
	return 0;
}
