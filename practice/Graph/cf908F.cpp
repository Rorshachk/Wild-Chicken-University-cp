#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
#define ll long long
const int N = 3e5 + 10;
int n;
struct Point{
	int pos;
	char col;
}a[N];
int bef[N], aft[N];
vector<int> greens, reds, blues;
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		char tmpcol[2];
		scanf("%d%s", &a[i].pos, tmpcol);
		a[i].col = tmpcol[0];
		if(a[i].col == 'G') greens.push_back(i);
		if(a[i].col == 'R') reds.push_back(i);
		if(a[i].col == 'B') blues.push_back(i);
	}

		
	ll ans = 0;
	if(greens.empty()){
		for(int i = 1; i < reds.size(); i++)
			ans += a[reds[i]].pos - a[reds[i - 1]].pos;
		for(int i = 1; i < blues.size(); i++)
			ans += a[blues[i]].pos - a[blues[i - 1]].pos;
		cout<<ans<<endl;
		return 0;
	}

	for(int i = 1; i < greens.size(); i++){
		int l = greens[i - 1], r = greens[i];
		
		int pre_r = a[greens[i - 1]].pos, pre_b = a[greens[i - 1]].pos;
		vector<int> b_dis, r_dis;
		for(int j = l; j <= r; j++){
			if(a[j].col == 'B'){
				b_dis.push_back(a[j].pos - pre_b);
				pre_b = a[j].pos;
			}
			if(a[j].col == 'R'){
				r_dis.push_back(a[j].pos - pre_r);
				pre_r = a[j].pos;
			}
		}

		b_dis.push_back(a[greens[i]].pos - pre_b);
		r_dis.push_back(a[greens[i]].pos - pre_r);

		ll tmp1 = 0;
		for(auto d:b_dis) tmp1 += d;
		for(auto d:r_dis) tmp1 += d;

		ll tmp2 = 0;
		int mx_b = 0, mx_r = 0;
		for(auto d:b_dis) mx_b = max(mx_b, d);
		for(auto d:r_dis) mx_r = max(mx_r, d);

		tmp2 = a[greens[i]].pos - a[greens[i - 1]].pos;
		tmp2 += (tmp1 - mx_b - mx_r);
		
		ans += min(tmp1, tmp2);
	}

	for(int i = 1; i < greens[0]; i++)
	  if(a[i].col == 'R'){
		  ans += a[greens[0]].pos - a[i].pos;
		  break;
	  }
	for(int i = 1; i <= greens[0]; i++)
	  if(a[i].col == 'B'){
		  ans += a[greens[0]].pos - a[i].pos;
		  break;
	  }

	for(int i = n; i > greens.back(); i--)
	  if(a[i].col == 'R'){
		  ans += a[i].pos - a[greens.back()].pos;
		  break;
	  }
	for(int i = n; i > greens.back(); i--)
	  if(a[i].col == 'B'){
		  ans += a[i].pos - a[greens.back()].pos;
		  break;
	  }
	

	cout<<ans<<endl;
	return 0;
}
