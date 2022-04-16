#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 1010;
int a[N][N];
int main(){
	freopen("input.txt", "w", stdout);
	int n = 1000, m = 4e5;

	printf("%d %d\n", n, m);
	
	for(int i = 1; i <= m; i++){
		int x = rand() % n + 1, y = rand() % n + 1;
		if(a[x][y] || a[y][x] || x == y){ i--; continue; }
		printf("%d %d\n", x, y);
	}

	return 0;

}
