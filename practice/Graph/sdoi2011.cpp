// https://www.luogu.com.cn/problem/P2495
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long
typedef pair<int, int> P;
const int N = 5e5 + 10;
int head[N], now;
struct edges{
	int to, next, w;
}edge[N << 1];
void add(int u, int v, int w){ edge[++now] = {v, head[u], w}; head[u] = now; }
int n, fa[N][22], dfn[N], dfn_num, w[N], dep[N], m;
ll dp[N];
vector<int> g[N];

void dfs(int x, int father){
	fa[x][0] = father;
	dfn[x] = ++dfn_num;
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(v != father){
			dep[v] = dep[x] + 1;
			w[v] = min(w[x], edge[i].w);
			dfs(v, x);
		}
	}
}

int lca(int u, int v){
	if(dep[u] < dep[v]) swap(u, v);
	int k = dep[u] - dep[v];
	for(int i = 0; i <= 20; i++)
	  if((1 << i) & k) u = fa[u][i];
	if(u == v) return u;
	for(int i = 20; i >= 0; i--)
	  if(fa[u][i] != fa[v][i])
	    u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

int sta[N], tp;
void build(vector<int>& h){
	sort(h.begin(), h.end(), [](int x, int y){ return dfn[x] < dfn[y]; });
	sta[tp = 1] = 1; g[1].clear();
	for(int i = 0; i < h.size(); i++){
		int tmp = lca(h[i], sta[tp]);
		if(tmp != sta[tp]){
			while(dfn[tmp] < dfn[sta[tp - 1]])
			  g[sta[tp]].push_back(sta[tp - 1]), tp--;
			if(dfn[sta[tp - 1]] != dfn[tmp]){
				g[tmp].clear();
				g[tmp].push_back(sta[tp]);
				sta[tp] = tmp; 
			}else{
				g[tmp].push_back(sta[tp--]);
			}
		}
		g[h[i]].clear(); sta[++tp] = h[i];
	}
	for(int i = 1; i < tp; i++)
	  g[sta[i]].push_back(sta[i + 1]);
	return ;
}

int cri[N];
void dfs_dp(int x){
	dp[x] = 0;
	for(auto v:g[x]){
		dfs_dp(v);
		if(cri[v]) dp[x] += w[v];
		else dp[x] += min(dp[v], 1LL * w[v]);
	}
}

int main(){
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		int x, y, z; scanf("%d%d%d", &x, &y, &z);
		add(x, y, z); add(y, x, z);
	}

	w[1] = 2e9;
	dfs(1, 1);
	for(int j = 0; j <= 20; j++)
	  for(int i = 1; i <= n; i++)
	    fa[i][j + 1] = fa[fa[i][j]][j];


	scanf("%d", &m);
	for(int i = 1; i <= m; i++){
		int tmp_n; scanf("%d", &tmp_n);	
		vector<int> h;
		for(int i = 0; i < tmp_n; i++){
			int x; scanf("%d", &x);
			h.push_back(x);
		}
		build(h);
		for(auto x:h) cri[x] = 1;
		dfs_dp(1);
		for(auto x:h) cri[x] = 1;
		cout<<dp[1]<<endl;
	}
	return 0;
}
