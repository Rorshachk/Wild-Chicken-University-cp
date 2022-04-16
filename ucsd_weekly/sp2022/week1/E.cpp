#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <unordered_set>
using namespace std;
const int N = 1e5 + 10;
int n, m;
unordered_set<int> to[N], vis;
void bfs(int s){
	queue<int> q;
	q.push(s);
	vis.erase(s);
	while(!q.empty()){
		int x = q.front(); q.pop();
		vector<int> tmp;
		for(auto i:vis){
			if(to[x].find(i) == to[x].end() && vis.find(i) != vis.end()){
				q.push(i);
				tmp.push_back(i);
			}
		}
		for(auto i:tmp)
			vis.erase(i);
	}
}
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		to[x].insert(y);
		to[y].insert(x);
	}
	int ans = 0;
	for(int i = 1; i <= n; i++) 
	  vis.insert(i);
	for(int i = 1; i <= n; i++)
		if(vis.find(i) != vis.end()){
			bfs(i);
			ans++;
		}
	cout<<ans - 1<<endl;
	return 0;
}
