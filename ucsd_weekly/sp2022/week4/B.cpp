#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> P;
const int N = 1e5 + 10;
int n, m, x, ans[N];
P h[N], sum[N];

int main(){
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d%d%d", &n, &m, &x);
		for(int i = 1; i <= n; i++){
			ans[i] = 0;
			sum[i] = h[i] = {0, 0};
		}
		for(int i = 1; i <= m; i++) sum[i].second = i;
		for(int i = 1; i <= n; i++){
			scanf("%d", &h[i].first);
			h[i].second = i;
		}
		sort(h + 1, h + n + 1);

		bool flg = false;
		int i;
		for(i = n; i >= m; i -= m){
			if(!flg){
				for(int j = 1; j <= m; j++){
					sum[j].first += h[i - j + 1].first;
					ans[h[i - j + 1].second] = j;
				}
			}else{
				for(int j = 1; j <= m; j++){
					sum[m - j + 1].first += h[i - j + 1].first;
					ans[h[i - j + 1].second] = m - j + 1;
				}
			}
			flg ^= 1;
		}
		sort(sum + 1, sum + m + 1);
		int cnt = 0;
		for(int j = i; j >= 1; j--){
			++cnt;
			sum[cnt].first += h[j].first;
			ans[h[j].second] = sum[cnt].second;
		}
		sort(sum + 1, sum + m + 1);
		if(sum[m].first - sum[1].first <= x){
			puts("YES");
			for(int i = 1; i <= n; i++)
				printf("%d ", ans[i]);
			printf("\n");
		}
		else puts("NO");
	}
	return 0;
}
