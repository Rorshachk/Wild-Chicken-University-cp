#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1e6 + 10;
char s[maxn];
 
struct X {
  char id;
  int num;
}p[maxn], q[maxn];
int sz;
 
void work() {
  for(int i = 0; i <= sz; i ++) {
    if(i == 0 || i == sz) {
      p[i].num --;
    } else {
      p[i].num --;
      p[i].num --;
    }
  }
  int cnt = 0;
  for(int i = 0; i <= sz; i ++) {
    if(p[i].num <= 0) continue;
    q[cnt ++] = p[i];
  }
  sz = 0;
  p[0] = q[0];
  for(int i = 1; i < cnt; i ++) {
    if(q[i].id == p[sz].id) p[sz].num += q[i].num;
    else {
      sz ++;
      p[sz] = q[i];
    }
  }
}
 
int main() {
  scanf("%s", s);
  p[sz].id = s[0];
  p[sz].num = 1;
  for(int i = 1; s[i]; i ++) {
    if(s[i] == p[sz].id) p[sz].num ++;
    else  {
      sz ++;
      p[sz].id = s[i];
      p[sz].num = 1;
    }
  }
  int ans = 0;
  while(1) {
    if(sz == 0) break;
    work();
    ans ++;
  }
  printf("%d\n", ans);
  return 0;
}
