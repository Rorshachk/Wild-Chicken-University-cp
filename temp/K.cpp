#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 2510;
int head[N], now;
struct edge{
	int to, next;
}edge[N << 1];
void add(int u, int v){
	edge[++now] = {v, head[u]};
	head[u] = now;
}
int dp[N][N];
int n, K;
void dfs(int x){
	if(!head[x]){
		dp[x][1] = K;
		return ;
	}
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		dfs(v);
		for(int j = 1; j <= K; j++){
			dp[x][j] += dp[v][j - 1] * (K - j + 1) + dp[v][j] / j * (j - 1);
		}
	}
}
int main(){
	scanf("%d%d", &n, &K);
	for(int i = 1; i < n; i++){
		int x;
		scanf("%d", &x);
		add(x + 1, i + 1);
	}

	dfs(1);
	cout<<dp[1][K]<<endl;
	return 0;
}
