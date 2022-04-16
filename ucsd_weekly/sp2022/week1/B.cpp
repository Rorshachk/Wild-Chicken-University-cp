#include <iostream>
#include <cstring>
#include <set>
using namespace std;
int main(){
	set<int> s;
	int n;
	scanf("%d", &n);
	for(int i = 1; i <=n ;i++){
		int x;
		scanf("%d", &x);
		s.insert(x);
	}
	for(int i = 0; i <= 2000; i++)
		if(s.find(i) == s.end()){
			cout<<i<<endl;
			return 0;
		}
}
