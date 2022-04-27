#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
typedef pair<int, int> P;

bool vis[110];
int ans, n;
// remain p choice, from m element, start from cur
void dfs(int m, int p, int cur, int covered){
	if(p == 0){
//		for(auto num:now){ printf("%d ", num); }
		if(covered == n - 1){
			ans++;
			// printf("true");
		}
		// printf("\n");
		return ;
	}
	for(int i = 1; i < min((cur + 1) / 2, n - 1); i++)
	  if(!vis[i]) return ;
	if(covered + p < n - 1 || (m - cur + 1) < p) return;
	
	for(int i = cur; i <= m - 1; i++){
		int pos = (i + 1) / 2;
		if(pos <= n - 1 && vis[pos] == 0){
			vis[pos] = 1;
			// now.push_back(i);
			dfs(m, p - 1, i + 1, covered + 1);
			// now.pop_back();
			vis[pos] = 0;
		}else{
			// now.push_back(i);
			dfs(m, p - 1, i + 1, covered);
			// now.pop_back();
		}
	}
}
long long C(int n, int m){
	long long sum = 1;
	for(int i = 1; i <= m; i++){
		sum = sum * (n - m + i) / i;
	}
	return sum;
}
long long gcd(long long x, long long y){ return y ? gcd(y, x % y) : x; }
int main(){
	int m, p;
	scanf("%d%d%d", &m, &n, &p);
	if(p == 0){
		if(n == 0) puts("1/1");
		else puts("0/1");
		return 0;
	}
	
	dfs(m - 1, p - 1, 1, 0);

	long long tot = C(m - 1, p - 1);
	
	// printf("%d/%lld * %d/%d", ans, tot, 2 * n, m);
	long long a = 1LL * ans * 2 * n;
	long long b = 1LL * tot * m;
	cout<<a / gcd(a, b)<<"/"<<b/gcd(a, b)<<endl;
	return 0;
}
