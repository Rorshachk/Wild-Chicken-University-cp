#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
using namespace std;
const int N = 2e5 + 10;
int head[N], now;
struct edges{
	int to, next;
}edge[N << 1];
void add(int u, int v){ edge[++now] = {v, head[u]}; head[u] = now; }
int n, m, a[N];
vector<int> bel[N];
int low[N], dfn[N], cnt, tot, dict[N];
bool exi[N];
stack<int> sta;

void tarjan(int x){
    low[x] = dfn[x] = ++cnt; exi[x] = 1;
    sta.push(x);
    for(int i = head[x];i ; i = edge[i].next){
        int v = edge[i].to;
        if(!dfn[v]){
            tarjan(v);  low[x] = min(low[x],low[v]);
        }
        else if(exi[v]) low[x] = min(low[x],dfn[v]);
    } 
    if(dfn[x] == low[x]){
        tot++;
        int tmp = -1;
        do{
            tmp = sta.top(); sta.pop();
            dict[tmp] = tot;
            exi[tmp] = 0;
        }while(x != tmp);
    }
    return ;
}

int main(){
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= m; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++){
		int x, y; scanf("%d", &x);
		for(int j = 1; j <= x; j++){
			scanf("%d", &y);
			bel[y].push_back(i);
		}
	}

	for(int i = 1; i <= m; i++){
		if(a[i]){
			add(bel[i][0], bel[i][1]);
			add(bel[i][1] + n, bel[i][0] + n);
			add(bel[i][1], bel[i][0]);
			add(bel[i][0] + n, bel[i][1] + n);
		}else{
			add(bel[i][0], bel[i][1] + n);
			add(bel[i][1], bel[i][0] + n);
	
			add(bel[i][1] + n, bel[i][0]);
			add(bel[i][0] + n, bel[i][1]);
		}
	}
	for(int i = 1; i <= 2 * n; i++)
		if(!dfn[i])
			tarjan(i);
	for(int i = 1; i <= n; i++){
		if(dict[i] == dict[i + n]){
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	return 0;
}
