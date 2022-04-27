#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 2e5 + 10;
int n, a[N];
double b[N];
bool check(double mid){
	for(int i = 1; i <= n; i++)
		b[i] = a[i] * 1.0 - mid;

	double sum1 = 0, tmp1 = 0;
	for(int i = 1; i <= n; i++){
		if(tmp1 > 0){
			tmp1 += b[i];
		}
		else tmp1 = b[i];
		if(tmp1 > sum1) sum1 = tmp1;
	}

	double sum2 = 0, tmp2 = 0;
	for(int i = 1; i <= n; i++){
		if(tmp2 > 0){
			tmp2 -= b[i];
		}
		else tmp2 = -b[i];
		if(tmp2 > sum2) sum2 = tmp2;
	}
	return sum2 - sum1 > 0;
}
int main(){
	scanf("%d", &n);
	double sum = 0;
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		sum += a[i];
	}
	if(n == 1){ puts("0"); return 0;}
	
	double l = -sum, r = sum, mid;
	if(r < l) swap(l, r);
	for(int i = 1; i <= 100; i++){
		mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid;
	}


	for(int i = 1; i <= n; i++)
		b[i] = a[i] * 1.0 - mid;

	double sum1 = 0, tmp1 = 0;
	for(int i = 1; i <= n; i++){
		if(tmp1 > 0){
			tmp1 += b[i];
		}
		else tmp1 = b[i];
		if(tmp1 > sum1) sum1 = tmp1;
	}
	
	printf("%.8lf", sum1);
}
