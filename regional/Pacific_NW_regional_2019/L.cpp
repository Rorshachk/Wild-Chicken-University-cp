#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
vector<int> target, ans;
int n;

void dfs(int x){
	if(x == n){
		for(int i = 0; i < ans.size(); i++)
		  cout<<ans[i];
		cout<<endl;
		exit(0);
	}
	for(int i = 0; i <= 9; i++){
		ans.push_back(i);
		bool flg = 1;
		vector<int> tmp(2 * x + 1);
		for(int j = 0; j < ans.size(); j++)
		  for(int k = 0; k < ans.size(); k++)
			  tmp[j + k] += ans[j] * ans[k];
	//	cout<<i<<": "<<endl;
	//	cout<<tmp[0]<<endl;
	//	cout<<target[0]<<endl;
		
		for(int j = 0; j < tmp.size(); j++)
		  if(tmp[j] % 10 != target[j]){
			  flg = 0;
			  break;
		  }
		
		if(flg){
			dfs(x + 1);
		}
		ans.pop_back();
		
	}
}
int main(){
	string s;
	cin>>s;
	
	for(int i = 0; i < s.length(); i++) 
	  target.push_back(s[i] - '0');

	if(target.size() % 2 == 0){
		puts("-1");
		return 0;
	}

	n = (target.size() + 1) / 2;

	dfs(0);
	puts("-1");
	return 0;
}
