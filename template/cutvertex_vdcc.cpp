#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
using namespace std;
const int N = 1e5 + 10;
int head[N], now;
struct edges{
	int to, next;
}edge[N << 1];
void add(int u, int v){ edge[++now] = {v, head[u]}; head[u] = now; }
int n, m, dfn[N], low[N], cut[N], num, cnt, root;
stack<int> sta;
vector<int> dcc[N];
void tarjan(int x){
	dfn[x] = low[x] = ++num;
	sta.push(x);
	if(x == root && head[x] == 0){
		dcc[++cnt].push_back(x);
		return;
	}
	int flg = 0;
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(!dfn[v]){
			tarjan(v);
			low[x] = min(low[x], low[v]);
			if(low[v] >= dfn[x]){
				flg++;
				if(x != root || flg > 1) cut[x] = 1;
				cnt++;
				int z;
				do {
					z = sta.top(); sta.pop();
					dcc[cnt].push_back(z);
				}while(z != v);
				dcc[cnt].push_back(x);
			}
		}else low[x] = min(low[x], dfn[v]);
	}
}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		int x, y;   scanf("%d%d", &x, &y);
		add(x, y);  add(y, x);
	}
	for(int i = 1; i <= n; i++){
		if(!dfn[i]){
			root = i;
			tarjan(i);
		}
	}
	
	vector<int> ans;
	for(int i = 1; i <= n; i++)
	  if(cut[i]) ans.push_back(i);

	printf("%d\n", ans.size());
	for(auto i:ans)
	  printf("%d ", i);
	printf("\n");
	return 0;

}
