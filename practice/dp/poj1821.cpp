#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 16010, M = 110;
int dp[M][N], n, m, q[N * 2];
struct Worker{
	int l, p, s;
}a[N];
bool cmp(Worker x, Worker y){ return x.s < y.s; }
int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	  scanf("%d%d%d", &a[i].l, &a[i].p, &a[i].s);
	sort(a + 1, a + m + 1, cmp);
	
	
	for(int i = 1; i <= m; i++){
		int head = 1, tail = 0;
		q[++tail] = max(0, a[i].s - a[i].l);
		for(int j = 1; j <= n; j++){
			dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
			if(j - a[i].l >= a[i].s) 
			  continue;
			while(head <= tail && q[head] < j - a[i].l)
			  head++;
			if(j < a[i].s){
				while(head <= tail && (dp[i - 1][q[tail]] - a[i].p * q[tail]) <= dp[i - 1][j] - a[i].p * j)
				  tail--;
				q[++tail] = j;
				continue;
			}
			dp[i][j] = max(dp[i][j], dp[i - 1][q[head]] + a[i].p * (j - q[head]));
		}
	}

	printf("%d\n", dp[m][n]);
	return 0;
}
