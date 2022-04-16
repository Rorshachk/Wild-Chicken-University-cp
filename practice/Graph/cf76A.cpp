#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <unordered_set>
using namespace std;
#define ll long long
const int N = 210, M = 1e5 + 10;
int head[N], now;
struct edges{
	int u, v, next, g, s, ref;
}edge[M], ori[M];
void add(int u, int v, int g, int s){
	edge[++now] = {u, v, head[u], g, s};
	head[u] = now;
}
int n, m, G, S, pa[N], dep[N], in_edge[N];
void dfs(int x){
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].v;
		if(v == pa[x]) continue;
		pa[v] = x; dep[v] = dep[x] + 1;
		in_edge[v] = edge[i].ref;
		dfs(v);
	}
}
int findMax(int u, int v){
	if(dep[u] < dep[v]) swap(u, v);
	int mx_s = 0, ret;
	while(dep[u] < dep[v]){
		if(edge[in_edge[u]].s > mx_s){
			ret = in_edge[u];
			mx_s = edge[in_edge[u]].s;
		}
		u = pa[u];
	}
	
	while(u != v){
		if(edge[in_edge[u]].s > mx_s){
			ret = in_edge[u];
			mx_s = edge[in_edge[u]].s;
		}
		if(edge[in_edge[v]].s > mx_s){
			ret = in_edge[v];
			mx_s = edge[in_edge[v]].s;
		}
		u = pa[u];
		v = pa[v];
	}
	return ret;
}
int fa[N];
int get(int x){ return x == fa[x] ? x : fa[x] = get(fa[x]); }
void Merge(int x, int y){
	int tx = get(x), ty = get(y);
	if(tx != ty) fa[ty] = tx; 
}
int main(){
	// freopen("input.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	scanf("%d%d", &G, &S);

	for(int i = 1; i <= m; i++)
	  scanf("%d%d%d%d", &ori[i].u, &ori[i].v, &ori[i].g, &ori[i].s);
	sort(ori + 1, ori + m + 1, [](edges x, edges y){ return x.g < y.g; });
	
	int mx_g = 0, mx_s = 0;
	for(int i = 1; i <= n; i++) fa[i] = i;
	unordered_set<int> cur;
	int cnt = 0;
	for(int i = 1; i <= m; i++){
		int x = get(ori[i].u), y = get(ori[i].v);
		if(x != y){
			mx_g = max(mx_g, ori[i].g);
			mx_s = max(mx_s, ori[i].s);
			add(ori[i].u, ori[i].v, ori[i].g, ori[i].s);
			edge[now].ref = i;
			add(ori[i].v, ori[i].u, ori[i].g, ori[i].s);
			edge[now].ref = i;
			Merge(x, y);
			cur.insert(i);
			cnt++;
		}
	}
	if(cnt != n - 1){
		puts("-1");
		return 0;
	}
	ll ans = 1LL * mx_g * G + 1LL * mx_s * S;
	for(int i = 1; i <= m; i++){
		if(cur.find(i) == cur.end() && ori[i].u != ori[i].v){
			dfs(1);
			int k = findMax(ori[i].u, ori[i].v);
			if(ori[k].s < ori[i].s) continue;
			cur.erase(k);
			cur.insert(i);
			
			// update ans and rebuild graph
			mx_g = 0, mx_s = 0;
			now = 0;
			memset(head, 0, sizeof(head));
			for(auto j:cur){
				mx_g = max(mx_g, ori[j].g);
				mx_s = max(mx_s, ori[j].s);
				add(ori[j].u, ori[j].v, ori[j].g, ori[j].s);
				add(ori[j].v, ori[j].u, ori[j].g, ori[j].s);
			}
			cur.clear();
			ans = min(ans, 1LL * mx_g * G + 1LL * mx_s * S);
		}
		
	}
	cout<<ans<<endl;
	return 0;
}
