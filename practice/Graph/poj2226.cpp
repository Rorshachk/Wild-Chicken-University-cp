#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 55, G_N = 50 * 51 * 2;
int n, m, row_cov[N][N], cov_tot, col_cov[N][N], left_n;
char a[N][N];

int head[G_N], now, match[G_N];
bool vis[G_N];
struct edge{
	int to, next, w;
}edge[G_N << 1];
void add(int u, int v){
	edge[++now] = {v, head[u]};
	head[u] = now;
}
bool dfs(int x){
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(!vis[v]){
			vis[v] = 1;
			if(!match[v] || dfs(match[v])){
				match[v] = x; return true;
			}
		}
	}
	return false;
}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		 scanf("%s", a[i] + 1);
	

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			int t = j;
			if(a[i][t] == '*'){
				cov_tot++;
				while(a[i][t] == '*'){
					row_cov[i][t] = cov_tot;
					t++;
				}
				j = t;
			}
		}

	left_n = cov_tot;

	for(int i = 1; i <= m; i++)
		for(int j = 1; j <= n; j++){
			int t = j;
			if(a[t][i] == '*'){
				cov_tot++;
				while(a[t][i] == '*'){
					col_cov[t][i] = cov_tot;
					t++;
				}
				j = t;
			}
		}

	now = 1;
	for(int i = 1; i <= n; i++)
	  for(int j = 1; j <= m; j++)
		if(a[i][j] == '*'){
			add(row_cov[i][j], col_cov[i][j]);
			add(col_cov[i][j], row_cov[i][j]);
		}

	/*
	cout<<"row cov"<<endl;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++)
			cout<<row_cov[i][j]<<" ";
		cout<<endl;
	}

	cout<<"col cov"<<endl;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++)
			cout<<col_cov[i][j]<<" ";
		cout<<endl;
	}
	*/

	
	int ans = 0;
	for(int i = 1; i <= left_n; i++){
		memset(vis, 0, sizeof(vis));
		if(dfs(i)) ans++;
	}
	
	cout<<ans<<endl;
	return 0;
}

