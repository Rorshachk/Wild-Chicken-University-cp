#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int main(){
	string s, s1, s2;
	cin>>s;
	s1 = s.substr(0, s.length() / 2);
	s2 = s.substr(s.length() / 2);

	int val = 0;
	for(auto ch:s1)
		val += (ch - 'A'), val %= 26;
	for(auto& ch:s1)
		ch = ((ch - 'A') + val) % 26 + 'A';


	val = 0;
	for(auto ch:s2)
		val += (ch - 'A'), val %= 26;
	for(auto& ch:s2)
		ch = ((ch - 'A') + val) % 26 + 'A';
	

	for(int i = 0; i < s1.length(); i++){
		s1[i] = ((s1[i] - 'A') + (s2[i] - 'A')) % 26 + 'A';
	}

	cout<<s1<<endl;
	return 0;

}
