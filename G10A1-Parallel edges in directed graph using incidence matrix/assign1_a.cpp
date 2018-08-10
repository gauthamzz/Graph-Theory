#include<bits/stdc++.h>

// Implementation with O(VE^2) time complexity for undirected graph

int a[1010][1010]; //incidence matrix
using namespace std;

int check(int i,int j,int n){
    for(int k=0;k<n;k++){
        if((a[k][i]==0 && a[k][j]!=0) || (a[k][i]!=0 && a[k][j]==0))
            return 0;
    }
    return 1;
}

int main()
{
    freopen("in.txt","r",stdin);
    int n,e;     // number of vertices and edges
    cin>>n>>e;
    memset(a,0,sizeof(a));
    for(int i=0;i<e;i++){
        int x,y;     // two vertices of given edge from x to y
        cin>>x>>y;
        a[x-1][i] = 1;
        a[y-1][i] = -1;
    }
    cout<<"Incidence matrix is given as below : \n";
    for(int i=0;i<n;i++){
        for(int j=0;j<e;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i=0;i<e;i++){
        for(int j=i+1;j<e;j++){
            if(check(i,j,n))
                cout<<"Paralle edges : "<<i+1<<" "<<j+1<<endl;
            else
                cout<<"Non-Parallel edges : "<<i+1<<" "<<j+1<<endl;
        }
    }
    return 0;
}
