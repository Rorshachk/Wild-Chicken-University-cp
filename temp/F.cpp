#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
struct Coor{
	int x, y;
	double d;
	bool operator < (const Coor& b) const{
		return d < b.d;
	}
};
typedef pair<int, int> P;
int n, m, cnt;
string mp[31];
vector<P> S;
double p[2010][32][32], res_p[110][111];
const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
bool check_eps(double x, double y){
	return abs(x - y) <= 1e-8;
}
bool check(int st, int ed){
	for(int i = 0; i < n; i++)
	  for(int j = 0; j < m; j++)
	    if(!check_eps(p[st][i][j], p[ed][i][j]))
		  return false;
	return true;
}

double dis[110][110];
double dij(P s, P e){
	priority_queue<Coor> pq;
	pq.push({s.first, s.second, 0});
	for(int i = 0; i < n; i++)
	  for(int j = 0; j < m; j++)
	    dis[i][j] = 100;
	
	dis[s.first][s.second] = 0;

	while(!pq.empty()){
		Coor u = pq.top(); pq.pop();
		if(dis[u.x][u.y] < u.d) continue;
		if(u.x == e.first && u.y == e.second){
			return u.d;
		}
		for(int i = 0; i < 4; i++){
			int tx = u.x + dx[i], ty = u.y + dy[i];
			if(tx < 0 || tx >= n || ty < 0 || ty >= m || mp[tx][ty] == '#')
			  continue;
			
			if(dis[tx][ty] > u.d + res_p[tx][ty]){
				dis[tx][ty] = u.d + res_p[tx][ty];
				pq.push({tx, ty, dis[tx][ty]});
			}
		}
	}
}
int main(){
	cin>>n>>m;
	cin.ignore();
	for(int i = 0; i < n; i++){
		getline(cin, mp[i]);
	}

	P s_dij, e_dij;

	for(int i = 0; i < n; i++)
	  for(int j = 0; j < m; j++){
	      if(mp[i][j] == ' ')
			S.emplace_back(i, j);
		  if(mp[i][j] == 'E')
		    s_dij = {i, j};
		  if(mp[i][j] == 'D')
		    e_dij = {i, j};
	  }
		  
	
	for(auto& s:S){
		p[0][s.first][s.second] = 1.0 / S.size();
	} 

	int st, ed;

	for(int t = 1; t; t++){
		for(auto i:S){
			vector<P> to;
			for(int j = 0; j < 4; j++){
				int tx = i.first + dx[j], ty = i.second + dy[j];
				if(tx < 0 || tx >= n || ty < 0 || ty >= m || mp[tx][ty] != ' ') continue;
				to.emplace_back(tx, ty);
			}

			if(to.empty())
			  p[t][i.first][i.second] = p[t - 1][i.first][i.second];

			for(auto j:to){
				p[t][j.first][j.second] += p[t - 1][i.first][i.second] / to.size();
			}
		}

		bool flg = 0;

		for(int k = max(t - 2, 0); k < t; k++)
		  if(check(t, k)){
			  flg = 1;
			  st = k, ed = t;
			  break;
		  }

		if(flg) break;
	}

	for(int t = st; t < ed; t++){
		for(int i = 0; i < n; i++)
		  for(int j = 0; j < m; j++)
		    res_p[i][j] += (p[t][i][j] / (ed - st)); 
	}

	cout<<dij(s_dij, e_dij)<<endl;

	return 0;

}
