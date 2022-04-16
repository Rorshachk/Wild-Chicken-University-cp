#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 2e5 + 10;
bool dp[N][2];
int a[N], b[N], n, k;
int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= n; i++){
		scanf("%d", &b[i]);
	}
	dp[1][0] = dp[1][1] = 1;
	for(int i = 2; i <= n; i++){
		dp[i][0] = dp[i][1] = 0;
		if(abs(a[i] - b[i - 1]) <= k)
			dp[i][0] |= dp[i - 1][1];
		if(abs(a[i] - a[i - 1]) <= k)
			dp[i][0] |= dp[i - 1][0];
		if(abs(b[i] - b[i - 1]) <= k)
			dp[i][1] |= dp[i - 1][1];
		if(abs(b[i] - a[i - 1]) <= k)
			dp[i][1] |= dp[i - 1][0];
	}
	if(dp[n][1] || dp[n][0])
		puts("Yes");
	else
		puts("No");
	return 0;
}
