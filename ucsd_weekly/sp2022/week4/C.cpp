#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define ll long long
ll C[62][62];
void init(){
	for(int i = 0; i <= 60; i++)
	  C[i][0] = 1;
	for(int i = 1; i <= 60; i++)
	  for(int j = 1; j <= i; j++)
		C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
}
int main(){
	init();
	int A, B;
	ll tot;
	cin>>A>>B>>tot;
	
	int now = A + B;
	while(now > 1){
		now--;
		if(tot > C[A + B - 1][A - 1]){
			cout<<"b";
			tot -= C[A + B - 1][A - 1];
			B--;
		}
		else {
			cout<<"a";
			A--;
		}
	}
	if(A) cout<<"a";
	else cout<<"b";
	return 0;
}
