#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int main(){
	int T; scanf("%d", &T);
	while(T--){
		int n; scanf("%d", &n);
		if(n & 1){ puts("NO"); continue; }

		if(n % 2 == 0){
			n /= 2;
			int k = sqrt(n);
			if(k * k == n){ puts("YES"); continue; }
		}
		if(n % 2 == 0){
			n /= 2;
			int k = sqrt(n);
			if(k * k == n){ puts("YES"); continue; }
		}
		puts("NO");
	}
	return 0;
}
