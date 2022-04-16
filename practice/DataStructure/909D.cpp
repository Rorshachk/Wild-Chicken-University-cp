#include <iostream>
#include <cstring>
#include <cstdio>
#include <set>
#include <vector>
#include <list>
using namespace std;
const int N = 1e6 + 10;
struct Node{
	int cnt;
	char col;
	bool operator < (const Node &b) const{
		return cnt < b.cnt;
	}
};
list<Node> s;
char c[N];
int cnt, n;
int deleteEle(){
	int mn_cnt = 1e9, ret;
	for(auto it = s.begin(); it != s.end(); ++it){
		if(it == s.begin() || next(it) == s.end())
			mn_cnt = min(mn_cnt, 2 * (it->cnt));
		else 
			mn_cnt = min(mn_cnt, it->cnt);
	}
	if(mn_cnt & 1) mn_cnt++;
	ret = mn_cnt / 2;
	vector<decltype(s.begin())> tmp;
	for(auto it = s.begin(); it != s.end(); ++it){
		if(it == s.begin() || next(it) == s.end())
			it->cnt -= ret;
		else it->cnt -= mn_cnt;
		if(it->cnt <= 0)
			tmp.push_back(it);
	}
	for(auto it:tmp) s.erase(it);
	tmp.clear();
	for(auto it = s.begin(); it != s.end(); ++it){
		auto j = next(it);
		if(j != s.end() && j->col == it->col){
			tmp.push_back(it);
			j->cnt += it->cnt;
		}
	}
	for(auto it:tmp)
		s.erase(it);
	return ret;
}
int main(){
	scanf("%s", c); n = strlen(c);
	for(int i = 0; c[i]; i++){
		Node tmp;
		int j = i;
		while(c[j + 1] == c[j]) j++;
		s.push_back({(j - i + 1), c[j]});
		i = j;
	}
	int ans = 0;
	while(s.size() > 1){
		ans += deleteEle();
	}
	printf("%d\n", ans);
	return 0;
}
