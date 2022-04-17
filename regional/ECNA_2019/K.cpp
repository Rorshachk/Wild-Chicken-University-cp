#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
#include <unordered_set>
#include <queue>
using namespace std;
const int N = 1e5 + 10;
int head[N],now;
struct edges{
    int to,next, dir;
}edge[N<<1];
void add(int u,int v, int dir){ 
//	printf("Add: %d %d\n", u, v);
	edge[++now] = {v,head[u], dir}; head[u] = now;
}

int n;
int mp[110][110];
unordered_set<int> uni[N];

vector<int> G[N];
int dis[2][N], dp[N];

void bfs(int s, int* d, int dir){
	queue<int> q;
	for(int i = 1; i <= n; i++) d[i] = 1e9;
	q.push(s);
	d[s] = 0;
	while(!q.empty()){
		int x = q.front(); q.pop();
		for(int i = head[x]; i; i = edge[i].next){
			int v = edge[i].to;
			if(edge[i].dir != dir) continue;
			if(d[v] > d[x] + 1){
				d[v] = d[x] + 1;
				q.push(v);
			}
		}
	}
}

int main(){
	// freopen("data/K/14-rand.in", "r", stdin);
	int w, h;
	scanf("%d%d", &h, &w);
	for(int i = 1; i <= h; i++)
	  for(int j = 1; j <= w; j++){
		  scanf("%d", &mp[i][j]);
		  n = max(mp[i][j], n);
	  }
	
	n++; h++;
	for(int j = 1; j <= w; j++) mp[h][j] = n;

	for(int i = 1; i < h; i++)
	  for(int j = 1; j <= w; j++){
		  if(mp[i][j] != mp[i + 1][j] && uni[mp[i][j]].find(mp[i + 1][j]) == uni[mp[i][j]].end()){
			  add(mp[i][j], mp[i + 1][j], 1);
			  add(mp[i + 1][j], mp[i][j], 0);
			  uni[mp[i][j]].insert(mp[i + 1][j]);
		  }
	  }

	bfs(n, dp, 0);

	unordered_set<int> tmp_s;
	for(int i = 1; i <= w; i++){
		tmp_s.insert(mp[1][i]);
	}

	int tmp_cnt = 0;
	for(auto s:tmp_s) bfs(s, dis[tmp_cnt], 1), tmp_cnt++;


	int ans = 1e9;
	for(int i = 1; i <= n; i++){
		ans = min(ans, dp[i] + dis[0][i] + dis[1][i]);
	}

	cout<<ans<<endl;
	return 0;

}
