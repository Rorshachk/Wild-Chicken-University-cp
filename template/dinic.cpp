// https://www.luogu.com.cn/problem/P3376
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
#define ll long long
const int N = 50010, M = 300010;
const ll inf = 1e18;
int head[N], now, d[N], cur[N];
int n, m, s, t;
struct edges{
	int to, next, w;
}edge[M << 1];
void add(int u, int v, int w){
	edge[++now] = {v, head[u], w};
	head[u] = now;
}
bool bfs(){
	memset(d, 0, sizeof(d));
	queue<int> q;
	q.push(s); d[s] = 1; cur[s] = head[s];
	while(!q.empty()){
		int x = q.front(); q.pop();
		for(int i = head[x]; i; i = edge[i].next){
			int v = edge[i].to;
			if(edge[i].w != 0 && !d[v]){
				q.push(v);
				cur[v] = head[v];
				d[v] = d[x] + 1;
				if(v == t) return 1;
			}
		}
	}
	return 0;
}
ll dinic(int x, ll flow){
	if(x == t) return flow;
	int i;
	ll rest = flow;
	for(i = cur[x]; i && rest; i = edge[i].next){
		int v = edge[i].to;
		if(edge[i].w != 0 && d[v] == d[x] + 1){
			ll k = dinic(v, min(rest, 1LL * edge[i].w));
			if(!k) d[v] = 0;
			edge[i].w -= k;
			edge[i ^ 1].w += k;
			rest -= k;
		}
	}
	cur[x] = i;
	return flow - rest;
}
int main(){
	scanf("%d%d", &n, &m);
	scanf("%d%d", &s, &t);
	now = 1;
	for(int i = 1; i <= m; i++){
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z); add(y, x, 0);
	}

	ll flow = 0, maxflow = 0;
	while(bfs()){
		while(flow = dinic(s, inf)) maxflow += flow;
	}
	cout<<maxflow<<endl;
	return 0;
}
