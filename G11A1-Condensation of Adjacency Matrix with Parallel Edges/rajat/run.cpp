#include <bits/stdc++.h>
using namespace std;
int main()
{
	for (int i=1;i<=17;i++) {
		string s="static.out input"+to_string(i)+".txt static/output"+to_string(i)+".txt";
		cout<<s<<endl;
		system(s.c_str());
	}

	for (int i=1;i<=17;i++) {
		string s="variable.out input"+to_string(i)+".txt variable/output"+to_string(i)+".txt";
		cout<<s<<endl;
		system(s.c_str());
	}

	for (int i=1;i<=6;i++) {
		string s="base.out input"+to_string(i)+".txt base/output"+to_string(i)+".txt";
		cout<<s<<endl;
		system(s.c_str());
	}

	return 0;
}
