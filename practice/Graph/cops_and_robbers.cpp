// http://codeforces.com/gym/101982 E
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
#define ll long long
const int N = 50010, M = 300010, inf = 1e9;
int head[N], now, d[N], cur[N], T, cost[N];
int n, m, s, t, tot;
struct edges{
	int to, next, w;
}edge[M << 1];
void add(int u, int v, int w){
// 	if(w) printf("%d %d %d\n", u, v, w);
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
char mp[31][31];
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
int toPoint(int x, int y, int dep){
	return (x - 1) * m + y + dep * n * m;
}
int main(){
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &m, &n, &T);
	for(int i = 1; i <= n; i++)
		scanf("%s", mp[i] + 1);
	for(int i = 0; i < T; i++)
	  scanf("%d", &cost[i]);
	
	s = 2 * n * m + 1, t = 2 * n * m + 2;
	now = 1;
	for(int i = 1; i <= n; i++)
	  for(int j = 1; j <= m; j++){
		  for(int k = 0; k < 4; k++){
			  int tx = i + dx[k], ty = j + dy[k];
			  if(tx < 1 || tx > n || ty < 1 || ty > m) continue;
			  add(toPoint(i, j, 1), toPoint(tx, ty, 0), inf);
			  add(toPoint(tx, ty, 0), toPoint(i, j, 1), 0);
		  }
		  if(mp[i][j] >= 'a' && mp[i][j] <= 'z'){
			  add(toPoint(i, j, 0), toPoint(i, j, 1), cost[mp[i][j] - 'a']);
			  add(toPoint(i, j, 1), toPoint(i, j, 0), 0);
		  }else{
			  add(toPoint(i, j, 0), toPoint(i, j, 1), inf);
			  add(toPoint(i, j, 1), toPoint(i, j, 0), 0);
		  }

		  if(mp[i][j] == 'B'){
			  add(s, toPoint(i, j, 0), inf);
			  add(toPoint(i, j, 0), s, 0);
		  }
		  if(i == 1 || i == n || j == 1 || j == m){
			  add(toPoint(i, j, 1), t, inf);
			  add(t, toPoint(i, j, 1), 0);
		  }
	  }
	
	ll flow, maxflow = 0;
	while(bfs()){
		while(flow = dinic(s, inf)) maxflow += flow;
	}
	
	if(maxflow >= inf) puts("-1");
	else printf("%d\n", maxflow);
	return 0;
}
