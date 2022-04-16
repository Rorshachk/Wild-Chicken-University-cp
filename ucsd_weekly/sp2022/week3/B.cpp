#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <vector>
#include <queue>
using namespace std;
const int N = 1e5 + 10;
int x[N], y[N];
int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &x[i], &y[i]);
	int ans = 0;
	for(int i = 1; i <= n; i++)
	  for(int j = i + 1; j <= n; j++)
		for(int k = j + 1; k <= n; k++){
			if(i != j && i != k && j != k){
				if(1LL * (y[i] - y[j]) * (x[i] - x[k]) != 1LL * (y[i] - y[k]) * (x[i] - x[j]))
					ans++;
			}
		}
	printf("%d\n", ans);return 0;
}

