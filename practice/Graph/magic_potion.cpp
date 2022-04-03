// https://codeforces.com/gym/101981 I 
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 10010, M = 50050, inf = 1e9;
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
int dinic(int x, int flow){
	if(x == t) return flow;
	int i;
	int rest = flow;
	for(i = cur[x]; i && rest; i = edge[i].next){
		int v = edge[i].to;
		if(edge[i].w != 0 && d[v] == d[x] + 1){
			int k = dinic(v, min(rest, edge[i].w));
			if(!k) d[v] = 0;
			edge[i].w -= k;
			edge[i ^ 1].w += k;
			rest -= k;
		}
	}
	cur[x] = i;
	return flow - rest;
}
int T;
int main(){
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &n, &m, &T);
	s = n + m + 1, t = n + m + 2;
	int s1 = n + m + 3;
	now = 1;
	add(s, s1, T); add(s1, s, 0);

	for(int i = 1; i <= n; i++){
		add(s1, i, 1); add(i, s1, 0);
		add(s, i, 1); add(i, s, 0);
	}
	for(int i = 1; i <= m; i++){
		add(i + n, t, 1);
		add(t, i + n, 0);
	}

	for(int i = 1; i <= n; i++){
		int num, x; scanf("%d", &num);
		while(num--){
			scanf("%d", &x);
			add(i, x + n, 1);
			add(x + n, i, 0);
		}
	}

	int flow = 0, maxflow = 0;
	while(bfs()){
		while(flow = dinic(s, inf)) maxflow += flow;
	}
	cout<<maxflow<<endl;
	return 0;
}
