#include <iostream>
#include <cstring>
#include <cstdio>
#include <cassert>
using namespace std;
const int N = 510;
int head[N], now;
struct edges{
	int to, next;
}edge[N * N << 1];
void add(int u, int v){ edge[++now] = {v, head[u]}; head[u] = now; }
int n, col[N], match[N];
bool vis[N];
string s[N];
bool check(const string& s1, const string& s2){
	int cnt = 0;
	for(int i = 0; i < s1.length(); i++)
	  cnt += (s1[i] != s2[i]);
	// if(cnt == 2) cout<<s1<<" "<<s2<<endl;
	return cnt == 2;
}
void colDfs(int x, int color){
	col[x] = color;
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(!col[v]) colDfs(v, 3 - color);
		else if(col[v] == color){
			assert(false);
		}
	}
}
bool argDfs(int x){
	for(int i = head[x]; i; i = edge[i].next){
		int v = edge[i].to;
		if(!vis[v]){
			vis[v] = 1;
			if(!match[v] || argDfs(match[v])){
				match[v] = x; return true;
			}
		}
	}
	return false;
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		cin>>s[i];

	for(int i = 1; i <= n; i++)
	  for(int j = i + 1; j <= n; j++){
		  if(check(s[i], s[j])){
			  add(i, j); add(j, i);
		  }
	  }

	for(int i = 1; i <= n; i++)
	  if(!col[i]) colDfs(i, 1);
	
	int ans = 0;
	for(int i = 1; i <= n; i++)
	  if(col[i] == 1){
		  memset(vis, 0, sizeof(vis));
		  if(argDfs(i)) ans++; 
	  }
	cout<<n - ans<<endl;
	return 0;
}
