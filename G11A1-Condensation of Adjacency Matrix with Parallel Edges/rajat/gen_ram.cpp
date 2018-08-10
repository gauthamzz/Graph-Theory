#include<bits/stdc++.h>
using namespace std;
int main()
{
	if(fopen("inp1.txt","r")){
		freopen("inp1.txt","r",stdin);
		freopen("input24.txt","w",stdout);
	}
	int i,a,b,n,m;
	cin>>n>>m;
	cout<<n<<" "<<m<<endl;
	for(i=0;i<m;i++){
		a=(rand()%rand())%(n-1);
		b=(rand()%127)%n;
		while(a==b){
			b=(rand()%127)%n;
		}
		cout<<a<<" "<<b<<endl;
	}
	return 0;
}

