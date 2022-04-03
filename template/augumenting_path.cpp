// Argumenting path
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 5e4 + 10; 
int n1, n2, m, head[N], now, match[N];
bool vis[N];
struct edges{
	int to, next;
}edge[N << 1];
void add(int u, int v){ edge[++now] = {v, head[u]}; head[u] = now; }
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
	scanf("%d%d%d", &n1, &n2, &m);
	for(int i = 1; i <= m; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y + n1); add(y + n1, x);
	}

	int ans = 0;
	
	for(int i = 1; i <= n1; i++){
		memset(vis, 0, sizeof(vis));
		if(dfs(i)) ans++;
	}

	cout<<ans<<endl;
	return 0;
}
