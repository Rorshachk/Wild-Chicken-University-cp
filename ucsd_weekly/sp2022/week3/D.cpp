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
#define ll long long
typedef pair<ll, ll> P;
const int N = 2e5 + 10;
ll n, a[N], t[N];
vector<P> fil;
int main(){
	std::ios::sync_with_stdio(false);
	cin>>n;
	ll sum = 0;
	for(int i = 1; i <= n; i++){
		cin>>a[i]>>t[i];
		if(t[i] == 1) sum += a[i];
		else fil.push_back({a[i] - sum, t[i]});
	}
	ll mxmx = -1e18;
	for(auto f:fil)
		if(f.second == 2)
			mxmx = max(f.first, mxmx);
	ll mnmn = 1e18;
	for(auto f:fil)
		if(f.second == 3)
			mnmn = min(f.first, mnmn);
	bool flg = 0;
	int Q; 
	cin>>Q;
	if(mnmn < mxmx){
		flg = 1;
		ll now = 0;
		for(auto f:fil){
			if(f.second == 2)
				now = max(now, f.first);
			else
				now = min(now, f.first);
		}
		for(int i = 1; i <= Q; i++){
			ll x;
			cin>>x;
			cout<<now+sum<<endl;
		}
	}
	else{
		ll now1 = mxmx - 1;
		ll now2 = mnmn + 1;
		for(auto f:fil){
			if(f.second == 2){
				now1 = max(now1, f.first);
				now2 = max(now2, f.first);
			}
			else{
				now1 = min(now1, f.first);
				now2 = min(now2, f.first);
			}
		}
		for(int i = 1; i <= Q; i++){
			ll x;
			cin>>x;
			if(x < mxmx) cout<<now1 + sum<<endl;
			else if(x > mnmn) cout<<now2 + sum<<endl;
			else cout<<x + sum<<endl;
		}
	}
	return 0;

}
