#include <iostream>
#include <cstring>
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
const int N = 2e5 + 19;
int n, n1, n2, s;
int a[N], b[N];
struct Interval{
	int l, r;
}seg[N];
bool check(int x){
	int tot = 0;
	for(int i = 1; i <= n2; i++){
		int l = max(0, b[i] - x), r = min(s - b[i], b[i] + x);
		if(l <= r) seg[++tot] = {l ,r};
	}
	sort(seg + 1, seg + tot + 1, [](Interval x, Interval y){ return x.r == y.r ? x.l < y.l : x.r < y.r; });
	multiset<int> st;
	for(int i = 1; i <= n1; i++) 
		st.insert(a[i]);
	
	int cnt = 0;
	for(int i = 1; i <= tot; i++){
		auto tmp = st.lower_bound(seg[i].l);
		if(tmp != st.end() && (*tmp) <= seg[i].r){
			st.erase(tmp);
			cnt++;
		}
	}
	return cnt >= n;
}
int main(){
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d%d", &n, &n1, &n2, &s);
	for(int i = 1; i <= n1; i++) scanf("%d", &a[i]);
	for(int i = 1; i <= n2; i++) scanf("%d", &b[i]);

	int l = 0, r = 1e9;
	int ans = 2e9;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	if(ans == 2e9) puts("-1");
	else printf("%d\n", ans);
	return 0;
}
