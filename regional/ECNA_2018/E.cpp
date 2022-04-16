#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <map>
using namespace std;
const int N = 510;
int n, m, q, now, g1[N][N], g2[N][N];
map<string, int> ls;
int main(){
	std::ios::sync_with_stdio(false);
	cin>>m>>q;
	for(int i = 1; i <= m; i++){
		string s1, s2, s3;
		cin>>s1>>s2>>s3;
		if(ls.find(s1) == ls.end())
			ls[s1] = ++n; 
		if(ls.find(s3) == ls.end())
			ls[s3] = ++n;
		if(s2 == "is-a")
			g1[ls[s1]][ls[s3]] = 1;
		if(s2 == "has-a")
			g2[ls[s1]][ls[s3]] = 1;
	}
	for(int i = 1; i <= n; i++)
	  g1[i][i] = 1;
	
	for(int k = 1; k <= n; k++)
	  for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
		  g1[i][j] |= g1[i][k] & g1[k][j]; 

	for(int k = 1; k <= n; k++)
	  for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++){
			if(g2[i][k] && g2[k][j])
				g2[i][j] = 1;
			if(g2[i][k] && g1[k][j])
				g2[i][j] = 1;
			if(g1[i][k] && g2[k][j])
				g2[i][j] = 1;
		}

	int kase = 0;
	while(q--){
		++kase;
		string s1, s2, s3;
		cin>>s1>>s2>>s3;
		int x = ls[s1], y = ls[s3];
		if(s2 == "is-a"){
			if(g1[x][y])
				cout<<"Query "<<kase<<": "<<"true"<<endl;
			else
				cout<<"Query "<<kase<<": "<<"false"<<endl;
		}
		if(s2 == "has-a"){
			if(g2[x][y])
				cout<<"Query "<<kase<<": "<<"true"<<endl;
			else
				cout<<"Query "<<kase<<": "<<"false"<<endl;
		}
	}
	return 0;
}
