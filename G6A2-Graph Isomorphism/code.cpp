#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define vi vector<int>
#define vvi vector<vi>

void transpose(vvi &a, vvi &aT, int n){
	int i, j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			aT[i][j]=a[j][i];
}

bool compare(vvi &a, vvi &b, int n){
	int i, j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(a[i][j]!=b[i][j])
				return false;
		}
	}
	return true;
}

void multiply(vvi &a, vvi &b, vvi &ans, int n){
	int i, j, k, x;
	ans.clear();
	for(i=0;i<n;i++){
		vi tmp;
		for(j=0;j<n;j++){
			x=0;
			for(k=0;k<n;k++)
				x+=a[i][k]*b[k][j];
			tmp.pb(x);
		}
		ans.pb(tmp);
	}
}

void checkIsomorphism(vvi &g, vvi &h, int n, int m){
	int gEdge, hEdge, i, j, tmp;
	vi gDegree, hDegree;
	if(n!=m){
		cout<<"Number of vertices are different."<<endl;
		return;
	}
	gEdge=0;
	hEdge=0;
	for(i=0;i<n;i++){
		tmp=0;
		for(j=0;j<n;j++){
			if(g[i][j]!=0)
				tmp++;
		}
		gDegree.pb(tmp);
		gEdge+=tmp;
	}
	for(i=0;i<m;i++){
		tmp=0;
		for(j=0;j<m;j++){
			if(h[i][j]!=0)
				tmp++;
		}
		hDegree.pb(tmp);
		hEdge+=tmp;
	}
	if(gEdge!=hEdge){
		cout<<"Number of edges are different."<<endl;
		return;
	}
	sort(gDegree.begin(), gDegree.end());
	sort(hDegree.begin(), hDegree.end());
	for(i=0;i<n;i++){
		if(gDegree[i]!=hDegree[i]){
			cout<<"Vertices have different set of degrees."<<endl;
			return;
		}
	}
	vi ar, br;
	vvi per, perT, ans, ans1;
	for(i=0;i<n;i++){
		ar.pb(i);
		br.pb(i);
		vi row1, row2;
		for(j=0;j<n;j++){
			row1.pb(0);
			row2.pb(0);
		}
		per.pb(row1);
		perT.pb(row2);
	}
	do{
		for(i=0;i<n;i++){
			per[i][br[i]]=0;
			per[i][ar[i]]=1;
		}
		transpose(per, perT, n);
		multiply(h, perT, ans, n);
		multiply(per, ans, ans1, n);
		if(compare(g, ans1, n)){
			cout<<"Isomoprphism present."<<endl;
			for(i=0;i<n;i++)
				cout<<i<<" "<<ar[i]<<endl;
			return;
		}
		for(i=0;i<n;i++){
			br[i]=ar[i];
		}
	}while(next_permutation(ar.begin(), ar.end()));
	cout<<"Isomoprphism not present."<<endl;
}

/*int main(){
	int n, i, j, m, x;
	vvi g, h;
	freopen("input.txt", "r", stdin);
	cin>>n;
	for(i=0;i<n;i++){
		vi tmp;
		for(j=0;j<n;j++){
			cin>>x;
			tmp.pb(x);
		}
		g.pb(tmp);
	}
	cin>>m;
	for(i=0;i<m;i++){
		vi tmp;
		for(j=0;j<m;j++){
			cin>>x;
			tmp.pb(x);
		}
		h.pb(tmp);
	}
	fclose(stdin);
	checkIsomorphism(g, h, n, m);
}*/

int main(){
	int n, i, j;
	float r, p;
	cin>>n>>p;
	vvi g, h, per, perT, ans, ans1;
	vi ar;
	for(i=0;i<n;i++){
		ar.pb(i);
		vi tmp;
		for(j=0;j<n;j++){
			tmp.pb(0);
		}
		g.pb(tmp);
		per.pb(tmp);
		perT.pb(tmp);
	}
	for(i=0;i<n;i++){
		for(j=0;j<i;j++){
			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			if(r<=p){
				g[i][j]=1;
				g[j][i]=1;
			}
		}
	}
	random_shuffle(ar.begin(), ar.end());
	for(i=0;i<n;i++){
		per[i][ar[i]]=1;
	}
	transpose(per, perT, n);
	multiply(g, perT, ans, n);
	multiply(per, ans, h, n);
	/*cout<<"G:"<<endl;
	printf("\t");
	for(i=0;i<n;i++)
		printf("%d\t", i);
	cout<<endl;
	for(i=0;i<n;i++){
		printf("%d\t", i);
		for(j=0;j<n;j++){
			printf("%d\t", g[i][j]);
		}
		cout<<endl;
	}
	cout<<"H:"<<endl;
	printf("\t");
	for(i=0;i<n;i++)
		printf("%d\t", i);
	cout<<endl;
	for(i=0;i<n;i++){
		printf("%d\t", i);
		for(j=0;j<n;j++){
			printf("%d\t", h[i][j]);
		}
		cout<<endl;
	}*/
	const clock_t begin_time = clock();
	checkIsomorphism(g, h, n, n);
	cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC<<endl;
	return 0;
}