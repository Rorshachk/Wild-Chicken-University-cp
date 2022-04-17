#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int a[4];
int main(){
	for(int i = 1; i <= 3; i++){
		int n; scanf("%d", &n);
		int x;
		for(int i = 1; i <= n; i++){
			scanf("%d", &x);
			if(x >= 1 && x <= 5) a[1]++;
			if(x >= 6 && x <= 10) a[2]++;
			if(x >= 11 && x <= 20) a[3]++;
			if(x >= 21 && x <= 25) a[2]++;
			if(x >= 26 && x <= 30) a[1]++;
		}
	}
		if(a[1] >= 10 && a[2] >= 10 && a[3] >= 10){
			puts("Yes");
		}
		else puts("No");
}
