#include<bits/stdc++.h>

// Implementation with O(VE + E) time complexity avg case and O(VE+ElogE) in worst case for undirected graph
using namespace std;

int a[1010][1010]; 
unordered_map<string,vector<int> > mm;

int main()
{
    freopen("in.txt","r",stdin);

    int n,e;     
    cin>>n>>e;
    memset(a,0,sizeof(a));
    for(int i=0;i<e;i++){
        int x,y;    
        cin>>x>>y;
        a[x-1][i] = 1;
        a[y-1][i] = -1;
    }
    cout<<"Incidence matrix is given as below : \n";
    for(int i=0;i<n;i++){
        for(int j=0;j<e;j++){
            cout<<abs(a[i][j])<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i=0;i<e;i++){
        string st = "";
        for(int j=0;j<n;j++){
            st += char(abs(a[j][i])+'0');
        }
        cout<<st<<endl;
        mm[st].push_back(i);
    }
    unordered_map<string,vector<int> >::iterator it = mm.begin();
    while(it!=mm.end()){
        vector<int> vec = it->second;
        for(int i=0;i<vec.size();i++){
            cout<<vec[i]<<" ";
        }
        cout<<endl;
        it++;
    }
    return 0;
}
