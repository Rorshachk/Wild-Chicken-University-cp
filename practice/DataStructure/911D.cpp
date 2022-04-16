#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
const int N = 2e5 + 10;
int sta[N], tp, n, K, b[N], tot_b, ans[N], ans_tot;
int main(){
	scanf("%d%d", &n, &K);
	sta[++tp] = 1e9;
	for(int i = 1; i <= K; i++){
		int x; scanf("%d", &x);
		ans[++ans_tot] = x;
		while(sta[tp] < x){
			b[++tot_b] = sta[tp--];
		}
		sta[++tp] = x;
	}

	for(int i = 1; i <= tot_b; i++){
		if(b[i] != i){
			puts("-1");
			return 0;
		}
	}
	

	while(tp){
		int tmp = (tp == 1 ? n : sta[tp] - 1);
		for(int i = tmp; i > tot_b; i--)
		  ans[++ans_tot] = i;
		for(int i = tot_b + 1; i <= std::min(sta[tp], n); i++)
		  b[++tot_b] = i;
		tp--;
	}

	for(int i = 1; i <= ans_tot; i++)
	  printf("%d ", ans[i]);
	puts("");
	return 0;
}
