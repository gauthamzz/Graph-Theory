#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;

map<int, list<int> > path;
vector<pair<int, int> > arr;

void max_heapify(int n, int i){
    int largest = i;  
    int l = 2*i + 1;  
    int r = 2*i + 2; 
	
    if (l < n && arr[l].f > arr[largest].first)
        largest = l;
 
    if (r < n && arr[r].f > arr[largest].first)
        largest = r;
 
    if (largest != i){
       list<int> v;
       v = path[arr[i].s];
       v.push_back(largest);
       path[arr[i].s] = v;	
      
       v.clear();
       v = path[arr[largest].s];
       v.push_back(i);
       path[arr[largest].s] = v;
      
       swap( arr[i],arr[largest]);
       max_heapify(n, largest);
    }
}
 
void build_max_heap( int n){
    for (int i = n / 2 - 1; i >= 0; i--)
        max_heapify(n, i);
 
    for (int i=n-1; i>=0; i--){
       list<int> v;
       v = path[arr[i].s];
       v.push_back(0);
       path[arr[i].s] = v;	
     
       v.clear();
       v = path[arr[0].s];
       v.push_back(i);
       path[arr[0].s] = v;
       swap(arr[0], arr[i]);
       max_heapify(i, 0);
    }
}

void printArray(int n){
    for (int i=0; i<n; ++i)
        cout << arr[i].f<< " ";;
    cout << "\n";
    cout<<"Path of each element\n";
    for(int i=0; i<n; i++){
    	list<int> v = path[arr[i].s];
    	cout << arr[i].f << " --> ";
    	for(list<int>::iterator it=v.begin(); it != v.end(); ++it)
    		cout<<*it<<" ";
    	cout<<endl;
    }
}

void find_elem(int n){
	int max = 0, min =  0;
	vector<int> max_val, min_val;
	for(int i =0; i < n; i++ ){
		if(path[arr[i].s].size() > path[arr[max].s].size()){
			max = i;
		}
		if(path[arr[i].s].size() < path[arr[min].s].size()){
			min = i;
		}
	}
	for(int i =0; i < n; i++ ){
		if(path[arr[i].s].size() == path[arr[max].s].size()){
			max_val.push_back(arr[i].f);
		}
		if(path[arr[i].s].size() == path[arr[min].s].size()){
			min_val.push_back(arr[i].f);
		}
	}
	cout<<"Element(s) that moved the most: ";
	for(int i =0;i<max_val.size();i++)
		cout<<max_val[i]<<" ";
	cout<<endl;
	cout<<"Element(s) that moved the least: ";
	for(int i =0;i<min_val.size();i++)
		cout<<min_val[i]<<" ";
	cout<<endl;
} 

int main(){
    int n,val;
    cin>>n;
    for(int i=0;i<n;i++){
       cin>>val;
       pair<int, int> temp = make_pair(val, i);
       arr.push_back(temp);
    }
    for(int i = 0; i < n; i++){
    	list<int> l;
    	l.push_back(i);
    	path[arr[i].s] = l ;
    }
    build_max_heap( n);
    cout << "Sorted array is \n";
    printArray( n);
    find_elem( n);
}