#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 52;
int mp[N][N];
int head[N * N], now;
struct edges{
	int to, next, w;
}edge[N * N * N * N];
void add(int u, int v, int w){ edge[++now] = {v, head[u], w}; head[u] = now; }
int n, K, dis[N * N];
int ID(int x, int y){
	return (x - 1) * n + y;
}
typedef pair<int, int> P;
void dij(int s){
	priority_queue<P, vector<P>, greater<P>> pq;
	memset(dis, 0x3f, sizeof(dis));
	pq.push(P(0, s)); dis[s] = 0;
	while(!pq.empty()){
		P tp = pq.top(); pq.pop();
		int x = tp.second;
		if(dis[x] != tp.first) continue;
		for(int i = head[x]; i; i = edge[i].next){
			int v = edge[i].to;
			if(dis[v] > dis[x] + edge[i].w){
				dis[v] = dis[x] + edge[i].w;
				pq.push(P(dis[v], v));
			}
		}
	}
}
int main(){
	scanf("%d%d", &n, &K);
	for(int i = 1; i <= n; i++)
	  for(int j = 1; j <= n; j++)
		scanf("%d", &mp[i][j]);
	for(int i1 = 1; i1 <= n; i1++)
	  for(int j1 = 1; j1 <= n; j1++)
		for(int i2 = 1; i2 <= n; i2++)
		  for(int j2 = 1; j2 <= n; j2++){
			  if((i1 == i2 && j1 == j2) || mp[i1][j1] + 1 != mp[i2][j2]) continue;
			  add(ID(i1, j1), ID(i2, j2), abs(i2 - i1) + abs(j2 - j1));
		  }

	int s = n * n + 1;
	for(int i = 1; i <= n; i++)
	  for(int j = 1; j <= n; j++)
		if(mp[i][j] == 1)
		  add(s, ID(i, j), 0);
	dij(s);
	int ans = 1e8;
	for(int i = 1; i <= n; i++)
	  for(int j = 1; j <= n; j++)
		if(mp[i][j] == K)
		  ans = min(ans, dis[ID(i, j)]);
	if(ans == 1e8) puts("-1");
	else printf("%d\n", ans);
	return 0;
}
