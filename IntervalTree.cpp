//Interval Tree using Binary Search Tree
//By - Atul Kumar Singh(14116021)

#include<bits/stdc++.h>
using namespace std;

struct Interval{
	int start,end;
};

struct node{
	Interval *i;
	int max;
	node *left,*right;
};

node *newInterval(Interval i){
	struct node *temp=new node;
	temp->i=new Interval(i);
	temp->max=i.end;
	temp->left=temp->right=NULL;
	return temp;
}

node *insert(node *root,Interval i){
	if(root==NULL){
		return newInterval(i);
	}
	if(i.start<(root->i)->start){
		root->left=insert(root->left,i);
	}
	else{
		root->right=insert(root->right,i);
	}
	if(root->max<i.end){
		root->max=i.end;
	}
	return root;
}

struct node * minstartInterval(struct node* node)
{
    struct node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

int findMax(int a,int b,int c){
	return a>b?(a>c?a:c):(b>c?b:c);
}

node *deleteInterval(node *root,Interval i){
	if(root==NULL){
		return NULL;
	}
	if(i.start<(root->i)->start){
		root->left=deleteInterval(root->left,i);
	}
	else if(i.start>(root->i)->start){
		root->right=deleteInterval(root->right,i);
	}
	else if(i.start==(root->i)->start ){
		if(i.end==(root->i)->end){
			if(root->left==NULL){
				struct node *temp=root->right;
				free(root);
				return temp;
			}
			else if(root->right==NULL){
				struct node *temp=root->left;
				free(root);
				return temp;
			}
			struct node *temp=minstartInterval(root->right);
			root->i=temp->i;
			root->right=deleteInterval(root->right,*(temp->i));
			}
		else{
			root->right=deleteInterval(root->right,i);
		}
	}
	root->max=findMax(root->i->end,((root->left!=NULL)?root->left->max:INT_MIN),((root->right!=NULL)?root->right->max:INT_MIN));
	return root;
}

bool doOverlap(Interval i1,Interval i2){
	return (!(i1.end<i2.start || i2.end<i1.start));
}

Interval *overlapSearch(node *root,Interval i){
	if(root==NULL){
		return NULL;
	}
	if(doOverlap(*(root->i),i)){
		return root->i;
	}
	if(root->left!=NULL && i.start<=(root->left)->max){
		return overlapSearch(root->left,i);
	}
	return overlapSearch(root->right,i);
}

void inorder(node *root){
	if(root!=NULL){
		inorder(root->left);
		cout<<"["<<root->i->start<<","<<root->i->end<<"] "<<" = "<<root->max<<"\n";
		inorder(root->right);
	}
}

int main(){
	Interval ints[] = {{16, 21}, {8, 9}, {25, 30}, {5, 8}, {15, 23}, {17, 19}, {26,26}, {0,3}, {6,10}, {19,20}};
    int n = sizeof(ints)/sizeof(ints[0]);
    node *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, ints[i]);

    inorder(root);
 
    Interval x = {6, 10};
 
    Interval *res = overlapSearch(root, x);
    if (res == NULL)
        cout << "\nNo Overlapping Interval\n";
    else
        cout << "\nOverlaps with [" << res->start << "," << res->end << "]\n";
 
    Interval y= {15, 23};
    root=deleteInterval(root,y);
    inorder(root);
    cout<<endl;
 
    Interval z= {19, 20};
    root=deleteInterval(root,z);
    inorder(root);
    cout<<endl;
 
    return 0;
}