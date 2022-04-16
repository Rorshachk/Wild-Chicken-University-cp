#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 5e5;
struct Tag{
	int tim, l, r;
};

// Segment tree for cache
struct SegTree{
	int ls, rs;
	Tag tag;
}tree1[N << 2];
int SegTreeBuild(int x, int l, int r){
	if(l == r){
		tree1[x].tag = {0, 0, 0};
		return x;
	}
	int mid = (l + r) >> 1;
	tree1[x].ls = SegTreeBuild(x << 1, l, mid);
	tree1[x].rs = SegTreeBuild(x << 1 | 1, mid + 1, r);
	return x;
}
void pushdown(int x){
	if(tree1[x].tag.l == 0) return;
	Tag tmp = tree1[x].tag;
	int mid = (tmp.l + tmp.r) >> 1;
	tree1[tree1[x].ls].tag = {tmp.tim, tmp.l, mid};
	tree1[tree1[x].rs].tag = {tmp.tim, mid + 1, tmp.r};
	tree1[x].tag = {0, 0, 0};
}
void SegUpdate(int x, int l, int r, int L, int R, Tag tag){
	if(l >= L && r <= R){
		tree1[x].tag = tag;
		return ;
	}
	pushdown(x);
	int mid = (l + r) >> 1;
	if(L <= mid){
		Tag tag1 = {tag.tim, tag.l, tag.l +(mid - L)};
		SegUpdate(tree1[x].ls, l, mid, L, R, tag1);
	}
	if(R > mid){
		Tag tag2 = {tag.tim, tag.l + (mid - L) + 1, tag.r};
		SegUpdate(tree1[x].rs, mid + 1, r, L, R, tag2);
	}
}
Tag SegQuery(int x, int l, int r, int pos){
	if(l == r) return tree1[x].tag;
	pushdown(x);
	int mid = (l + r) >> 1;
	if(pos <= mid) return SegQuery(tree1[x].ls, l, mid, pos);
	else return SegQuery(tree1[x].rs, mid + 1, r, pos);
}

// Persistent Segment tree for array
int root[N], now;
struct PersistSegTree{
	int ls, rs;
	unsigned char val;
}tree2[N * 18];
int PersisTreeBuild(int l, int r){
	int p = ++now;
	if(l == r){
		tree2[p].val = 0;
		return p;
	}
	int mid = (l + r) >> 1;
	tree2[p].ls = PersisTreeBuild(l, mid);
	tree2[p].rs = PersisTreeBuild(mid + 1, r);
	return p;
}

int PersisTreeUpdate(int x, int l, int r, int pos, int val){
	int p = ++now;
	// cout<<p<<"(";
	tree2[p] = tree2[x];
	if(l == r){
		tree2[p].val += val;
		return p;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) tree2[p].ls = PersisTreeUpdate(tree2[x].ls, l, mid, pos, val);
	else tree2[p].rs = PersisTreeUpdate(tree2[x].rs, mid + 1, r, pos, val);
	tree2[p].val = tree2[tree2[p].ls].val + tree2[tree2[p].rs].val;
	// cout<<"),";
	return p;
}

void PersisTreeUpdate2(int x, int l, int r, int pos, int val){
	if(l == r){
		tree2[x].val += val;
		return ;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) PersisTreeUpdate2(tree2[x].ls, l, mid, pos, val);
	else PersisTreeUpdate2(tree2[x].rs, mid + 1, r, pos, val);
	return ;
}

int PersisTreeQuery(int x, int l, int r, int R){
	if(r <= R) return tree2[x].val;
	int mid = (l + r) >> 1;
	int res = 0;
	res += PersisTreeQuery(tree2[x].ls, l, mid, R);
	if(R > mid) res += PersisTreeQuery(tree2[x].rs, mid + 1, r, R);
	return res;
}

int n, m, Q, sum[N], a[N], tot;
int main(){
	// freopen("input.txt", "r", stdin);
	scanf("%d%d%d", &n, &m, &Q);
	for(int i = 1; i <= m; i++){
		int num, x; scanf("%d", &num);
		sum[i] = sum[i - 1] + num;
		for(int i = 1; i <= num; i++){
			scanf("%d", &x);
			a[++tot] = x;
		}
	}
	root[0] = PersisTreeBuild(1, tot);
	SegTreeBuild(1, 1, n);
	int ver = 0;
	while(Q--){
		int op;
		scanf("%d", &op);
		if(op == 1){
			int i, p; scanf("%d%d", &i, &p);
			int L = sum[i - 1] + 1, R = sum[i];
			Tag upd = {ver, L, R};
			SegUpdate(1, 1, n, p, p + (sum[i] - sum[i - 1]) - 1, upd);
		}
		else if(op == 2){
			int p; scanf("%d", &p);
			Tag tmp = SegQuery(1, 1, n, p);
			if(tmp.l == 0) printf("0\n");
			else printf("%d\n", (a[tmp.l] + PersisTreeQuery(root[tmp.tim], 1, tot, tmp.l)) % 256);
		}
		else {
			int i, l, r; scanf("%d%d%d", &i, &l, &r);
			int L = sum[i - 1] + l, R = sum[i - 1] + r;
			ver++;
			root[ver] = PersisTreeUpdate(root[ver - 1], 1, tot, L, 1);
			PersisTreeUpdate2(root[ver], 1, tot, R + 1, -1);
//			printf("\n");
		}
	}
	return 0;
}
