

int main(){
	// do tarjan
	for(int i = 1; i <= n; i++){
		if(c[i] == c[i + n]){ puts("NO"); return 0; }
		opp[i] = n + i, opp[n + i] = i;
	}
	puts("YES");
	for(int i = 1; i <= 2 * n; i++)
		val[i] = c[i] > c[opp[i]];
}
