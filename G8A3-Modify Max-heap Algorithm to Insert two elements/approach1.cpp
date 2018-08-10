#include <bits/stdc++.h>
using namespace std;
void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
class Maxheap
{
	int *heap;
	int size;
	int capacity;
	public:
		Maxheap(int capacity);
		void insert(int key1,int key2);
		int left(int index);
		int right(int index);
		int parent(int index);
		int top();
		void clear();
};
Maxheap::Maxheap(int c)
{
	this->capacity = c;
	this->size = 0;
	this->heap = new int[c];
}
void Maxheap::clear()
{
	this->size = 0;
	memset(heap,0,sizeof(heap));
}
int Maxheap::left(int index)
{
	return 2*index+1;
}
int Maxheap::right(int index)
{
	return 2*index+2;
}
int Maxheap::parent(int index)
{
	return (index-1)/2;
}
void Maxheap::insert(int key1,int key2)
{
	if(size+2>capacity)
	{
		cout << "The heap is full\n";
		return;
	}
	heap[size] = key1;
	heap[size+1] = key2;
	size = size+2;
	int index1 = size-2;
	int index2 = size-1;
	while(index1!=0&&heap[parent(index1)]<heap[index1])
	{
		swap(&heap[parent(index1)],&heap[index1]);
		index1 = parent(index1);
	}
	while(index2!=0&&heap[parent(index2)]<heap[index2])
	{
		swap(&heap[parent(index2)],&heap[index2]);
		index2 = parent(index2);
	}
}
int Maxheap::top()
{
	return heap[0];
}
int main()
{
	ios::sync_with_stdio(false);
	ofstream out("plot.csv");
	for(int n=10000;n<=100000;n=n+10)
	{
		Maxheap m(1000005);
		clock_t start,end;
		start = clock();
		for(int i=1;i<=n;i=i+2)
		{
			m.insert(i,i+1);
		}
		end = clock();
		double runtime = end-start;
		runtime = runtime/CLOCKS_PER_SEC;
		out << n << "," << runtime << "\n";
		m.clear();
	}
	out.close();
	return 0;
}