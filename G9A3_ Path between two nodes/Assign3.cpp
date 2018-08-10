








#include<bits/stdc++.h>
using namespace std;
typedef struct Node{
	int data;
	struct Node *left, *right, *parent;
}Node;
int n1, n2;
Node *node1, *node2;
Node* createNode(int key){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->left = temp->right = temp->parent = NULL;
	temp->data = key;
	return temp;
}
Node* createTree(Node *node, int nodes[], int i, int n){
	if(i>=n){
		return node;
	}
	node = createNode(nodes[i]);
	if(nodes[i]==n1){
		node1 = node;
	}
	if(nodes[i]==n2){
		node2 = node;
	}
	node->left = createTree(node->left, nodes, 2*i+1, n);
	if(node->left!=NULL){
		node->left->parent = node;
	}
	node->right = createTree(node->right, nodes, 2*i+2, n);
	if(node->right!=NULL){
		node->right->parent = node;
	}
	return node;
}
void traversal(Node *root){
	if(root==NULL){
		return;
	}
	cout << root->data  << " " << root->parent->data << "\n";
	traversal(root->left);
	traversal(root->right);
}
void LCA(Node *node1, Node *node2){
	map < Node*, bool > ancestors;
	Node *temp = node1;
	while(node1 != NULL){
		ancestors[node1]=true;
		node1 = node1->parent;
	}
	Node *lca;
	stack < Node* > st;
	while(node2 != NULL){
		if(ancestors[node2]==true){
			lca = node2;
			break;
		}
		st.push(node2);
		node2 = node2->parent;
	}
	while(temp!=lca){
		cout << temp->data << " ";
		temp = temp->parent;
	}
	cout << lca->data << " ";
	while(!st.empty()){
		cout << st.top()->data << " ";
		st.pop();
	}
}
int main(){
	int height;
	cin >> height;
	int n = pow(2, height)-1;
	int nodes[n];
	for(int i=0; i<n; i++){
		cin >> nodes[i];
	}
	cin >> n1 >> n2;
	Node *root = NULL;
	root = createTree(root, nodes, 0, n);
	LCA(node1, node2);
	return 0;
}
