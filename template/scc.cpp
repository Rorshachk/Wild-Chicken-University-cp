#include<bits/stdc++.h>
using namespace std;
const int N = 100100;

int head[N],now;
struct edges{
    int to,next;
}edge[N<<1];
void add(int u,int v){ edge[++now] = {v,head[u]}; head[u] = now;}

int n,m,low[N],dfn[N],tot,cnt,pri[N],dict[N],ans,w_in[N],w[N];
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
            w[tot] += w_in[tmp];
        }while(x != tmp);
    }
    return ;
}

int qhead[N],qnow;
struct qe{
    int to,next;
}q_edge[N<<1];
void q_add(int u,int v){ q_edge[++qnow] = {v,qhead[u]}; qhead[u] = qnow;}
int dp[N];
void dfs(int x){
    int tmp = 0;
    dp[x] = w[x];
    for(int i = qhead[x]; i; i = q_edge[i].next){
        int v = q_edge[i].to;
        if(!dp[v])	dfs(v);
        tmp = max(dp[v],tmp); 
    }
    dp[x] += tmp;
    return ;
}

int main(){
    scanf("%d%d",&n,&m);
    int x,y,z;
    for(int i = 1; i <= n; i++) scanf("%d",&w_in[i]);
    for(int i = 1; i <= m; i++){
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    for(int i = 1; i <= n; i++)  if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= n; i++)
      for(int j = head[i]; j; j = edge[j].next)
        if(dict[i] != dict[edge[j].to])
          q_add(dict[i],dict[edge[j].to]);
    int ans = 0;
    for(int i = 1; i <= tot; i++)
      if(!dp[i])
        dfs(i), ans = max(dp[i],ans);
    printf("%d",ans);
    return 0;
}
