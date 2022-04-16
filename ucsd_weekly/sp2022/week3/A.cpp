#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <queue>
using namespace std;
const int N = 1e5 + 10;
int A[110][110];
int main(){
	int H, W;
	scanf("%d%d", &H, &W);
	for(int i = 1; i <= H; i++)
		for(int j =1; j <= W; j++)
			scanf("%d", &A[i][j]);
	int flg = 0;
	for(int i1 = 1; i1 <= H; i1++)
		for(int j1 = 1; j1 <= W; j1++)
			for(int i2 = i1 + 1; i2 <= H; i2++)
				for(int j2 = j1 + 1; j2 <= W; j2++)
					if(A[i1][j1] + A[i2][j2] > A[i2][j1] + A[i1][j2])
						flg = 1;
	if(flg) puts("No");
	else puts("Yes");
	

	return 0;
}
