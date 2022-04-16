#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 110;
int n, m;
char a[N][N];
int vis[N][N];
const int dx[] = {1, 1, 1, -1, -1, -1, 0, 0};
const int dy[] = {1, 0, -1, 1, 0, -1, 1, -1};
void dfs(int x, int y){
	for(int i = 0; i < 8; i++){
		int tx = x + dx[i], ty = y + dy[i];
		if(tx > n || tx < 1 || ty > m || ty < 1 || vis[tx][ty] || a[tx][ty] != '#')
			continue;
		vis[tx][ty] = 1;
		dfs(tx, ty);
	}
}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%s", a[i] + 1);

	int ans = 0;
	for(int i = 1; i <= n; i++)
	  for(int j = 1; j <= m; j++){
		  if(a[i][j] == '#' && !vis[i][j]){
			  vis[i][j] = 1;
		       dfs(i, j);
				ans++;
		  }
	  }
	cout<<ans<<endl;
	return 0;
}
