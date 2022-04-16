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
# define PI 3.14159265358979323846
int main(){
	double n;
	cin>>n;
	double x1, y1, x2, y2;
	cin>>x1>>y1>>x2>>y2;
	x2 = (x1 + x2) / 2;
	y2 = (y1 + y2) / 2;
	double dx = x1 - x2, dy = y1 - y2;
	double theta = PI * 2 / n;
	double resx = dx * cos(theta) - dy * sin(theta) + x2;
	double resy = dy * cos(theta) + dx * sin(theta) + y2;
	cout<<resx<<" "<<resy<<endl;
	return 0;
}

