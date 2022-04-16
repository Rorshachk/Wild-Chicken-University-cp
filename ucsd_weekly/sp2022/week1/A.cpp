#include <iostream>
#include <cstring>
#include <cstdio>
#include <unordered_map>
using namespace std;
int main(){
	unordered_map<int, int> mp1, mp2;
	for(int i = 1; i <= 3; i++){
		int x, y;
		cin>>x>>y;
		mp1[x]++;
		mp2[y]++;
	}
	for(auto i:mp1)
		if(i.second == 1)
			cout<<i.first<<" ";
	for(auto i:mp2)
		if(i.second == 1)
			cout<<i.first<<endl;
	return 0;
}
