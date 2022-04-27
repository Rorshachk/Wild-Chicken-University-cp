#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 510;
typedef pair<int, int> P;
int n, m;
char mp[N][N];
bool vis[N][N][4];
P dest[N][N][4];
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
P dfs(int x, int y, int dir){
	if(vis[x][y][dir]) return dest[x][y][dir];

	if(x == 0) return dfs(x + 1, y, 2);
	if(x == n + 1) return dfs(x - 1, y, 3);
	if(y == 0) return dfs(x, y + 1, 0);
	if(y == m + 1) return dfs(x, y - 1, 1);

	vis[x][y][dir] = 1;
	if(mp[x][y] == '#' || mp[x][y] == 'V' || mp[x][y] == 'H'){
		dest[x][y][dir] = {x, y};
		return dest[x][y][dir];
	}
	if(mp[x][y] == '/'){
		if(dir == 0){
			return dest[x][y][dir] = dfs(x - 1, y, 3);
		}if(dir == 1){
			return dest[x][y][dir] = dfs(x + 1, y, 2);
		}if(dir == 2){
			return dest[x][y][dir] = dfs(x, y - 1, 1);
		}if(dir == 3){
			return dest[x][y][dir] = dfs(x, y + 1, 0);
		}
	}
	if(mp[x][y] == '\\'){
		if(dir == 0){
			return dest[x][y][dir] = dfs(x + 1, y, 2);
		}if(dir == 1){
			return dest[x][y][dir] = dfs(x - 1, y, 3);
		}if(dir == 2){
			return dest[x][y][dir] = dfs(x, y + 1, 0);
		}if(dir == 3){
			return dest[x][y][dir] = dfs(x, y - 1, 1);
		}
	}
	return dest[x][y][dir] = dfs(x + dx[dir], y + dy[dir], dir);
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	  scanf("%s", mp[i] + 1);
	for(int i = 1; i <= n; i++)
	  for(int j = 1; j <= m; j++)
		for(int dir = 0; dir < 4; dir++){
			if(!vis[i][j][dir])
			  dest[i][j][dir] = dfs(i, j, dir);
		}
}
