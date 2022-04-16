#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
#define ll long long
const int Mod = 4;
int qpow(int x, int y){
	ll base = x, ans = 1;
	while(y){
		if(y & 1){
			ans *= base; ans %= 4;
		}
		base *= base; base %= 4;
		y /= 2;
	}
	return (int)ans;
}
int main(){
	long long x, y, z;
	cin>>x>>y>>z;
	
	int a = qpow(y, z);
	if(a == 0) a = 4;
	x %= 10;
	int ans = 1;
	for(int i = 1; i <= a; i++)
		ans *= x, ans %= 10;

	cout<<ans<<endl;
	return 0;
}
