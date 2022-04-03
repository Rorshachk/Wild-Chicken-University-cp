#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std; 
const int N = 500, M = 100000;
int head[N], now, d[N], cur[N];
int n, m, s, t, tot, tim;
const int inf = 1e9;
struct edges{
	int to, next, w;
}edge[M << 1];
void add(int u, int v, int w){
	// if(w != 0)
	//	printf("add edge: %d %d %d\n", u, v, w);
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
int toPoint(int x, int y, int z){ return (x - 1) * n + y + z * n * n; }
char mp1[N][N], mp2[N][N];
int dis1[N][N], dis2[N][N];
typedef pair<int, int> P;
const int dx[] = {0, 0, -1, 1}, dy[] = {1, -1, 0, 0};
void bfs2(int sx, int sy, int dis[N][N]){
	queue<P> q;
	q.push(P(sx, sy));
	for(int i = 1; i <= n; i++)
	  for(int j = 1; j <= n; j++)
		dis[i][j] = -1;	
	dis[sx][sy] = 0;
	while(!q.empty()){
		int x = q.front().first, y = q.front().second;
		q.pop();
		for(int i = 0; i < 4; i++){
			int tx = x + dx[i], ty = y + dy[i];
			if(tx < 1 || tx > n || ty < 1 || ty > n || dis[tx][ty] != -1 || mp1[tx][ty] == 'Y')
				continue;
			dis[tx][ty] = dis[x][y] + 1;
			q.push(P(tx, ty));
		}
	}
}
int main(){
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &tim);
	for(int i = 1; i <= n; i++)
		scanf("%s", mp1[i] + 1);
	for(int i = 1; i <= n; i++)
		scanf("%s", mp2[i] + 1);
	
	for(int i = 1; i <= n; i++)
	  for(int j = 1; j <= n; j++){
		  if(mp1[i][j] == 'Z'){
			bfs2(i, j, dis2);
			break;
		  }
	  }
	
	/*
	for(int i = 1; i <= n; i++, printf("\n"))
	  for(int j = 1; j <= n; j++)
		printf("%d ", dis2[i][j]);
	*/

	now = 1;
	s = 2 * n * n + 1, t = 2 * n * n + 2;
	for(int i = 1; i <= n; i++)
	  for(int j = 1; j <= n; j++)
		if(mp1[i][j] >= '0' && mp1[i][j] <= '9'){
			bfs2(i, j, dis1);
			for(int ii = 1; ii <= n; ii++)
			  for(int jj = 1; jj <= n; jj++){

				  int tmp;
				  if(dis2[ii][jj] == -1) tmp = tim;
				  else tmp = min(dis2[ii][jj], tim);

				  if(dis1[ii][jj] != -1 && dis1[ii][jj] < tmp){
					  // printf("Add edge: (%d %d) -> (%d %d)\n", i, j, ii, jj);
					  add(toPoint(i, j, 0), toPoint(ii, jj, 1), inf);
					  add(toPoint(ii, jj, 1), toPoint(i, j, 0), 0);
				  }else if(dis1[ii][jj] != -1 && dis1[ii][jj] == tmp){
					  for(int k = 0; k < 4; k++){
						  int tx = ii + dx[k], ty = jj + dy[k];
						  if(tx < 1 || tx > n || ty < 1 || ty > n || dis1[tx][ty] + 1 != dis1[ii][jj])
							  continue;
						  if(dis1[tx][ty] != dis2[tx][ty]){
							  add(toPoint(i, j, 0), toPoint(ii, jj, 1), inf);
							  add(toPoint(ii, jj, 1), toPoint(i, j, 0), 0);
							  break;
						  }
					  }
				  }
			  }
			add(s, toPoint(i, j, 0), mp1[i][j] - '0');
			add(toPoint(i, j, 0), s, 0);
			
			add(toPoint(i, j, 1), t, mp2[i][j] - '0');
			add(t, toPoint(i, j, 1), 0);
		}
	
	int flow = 0, maxflow = 0;
	while(bfs()){
		while(flow = dinic(s, inf)) maxflow += flow;
	}
	cout<<maxflow<<endl;
	return 0;
}
