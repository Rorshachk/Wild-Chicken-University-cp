#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
typedef pair<int, int> P;
const int N = 10010;
int head[N], now;
struct edges{
	int to, next;
}edge[N << 1];
void add(int u, int v){
	edge[++now] = {v, head[u]};
	head[u] = now;
}
int n, w[N], fa[N];
void dfs1(int x){
	w[x] = 1;
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(v == fa[x]) continue;
		fa[v] = x;
		dfs1(v);
		w[x] += w[v];
	}
}
int main(){
	scanf("%d", &n); n++;
	for(int i = 1; i < n; i++){
		int x, y; scanf("%d%d", &x, &y);
		x++, y++;
		add(x, y); add(y, x);
	}

	dfs1(1);
	int ans1 = 2e9, ans2 = 0;
	for(int x = 1; x <= n; x++){
		int tmp = 0, cur = 0;
		vector<int> p;
		for(int i = head[x]; i; i = edge[i].next){
			int v = edge[i].to;
			if(v == fa[x]) continue;
			tmp += (w[v] * (w[v] - 1) / 2);
			cur += w[v];
			p.push_back(w[v]);
		}
		tmp += (n - cur - 1) * (n - cur - 2) / 2;
		p.push_back(n - cur - 1);
		if(tmp < ans1){
			ans1 = tmp;
			sort(p.begin(), p.end(), [](int x, int y){ return x > y;});
			if(p.size() == 1) ans2 = 0;
			else ans2 = ans1 - p[0] * (p[0] - 1) / 2 - p[1] * (p[1] - 1) / 2 + (p[0] + p[1]) * (p[0] + p[1] - 1) / 2;
		}
	}
	cout<<(n - 2) * (n - 1) / 2 - ans1<<endl<<(n - 2) * (n - 1) / 2 - ans2<<endl;

	return 0;	

}
