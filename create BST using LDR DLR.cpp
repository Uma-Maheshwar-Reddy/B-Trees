#include<iostream>
using namespace std;
typedef
struct bstnode
{
	bstnode* lchild;
	int data;
	bstnode* rchild;
}*btptr;
void preorder(btptr &h)
{
	if(h!=NULL)
	{
		cout<<h->data<<" ";
		preorder(h->lchild);
		preorder(h->rchild);
	}
}
void inorder(btptr &h)
{
	if(h!=NULL)
	{
		inorder(h->lchild);
		cout<<h->data<<" ";
		inorder(h->rchild);
	}
}
bool is_left(int ldr[],int a,int b,int n)
{
	int x,y;
	for(int i=0;i<n;i++)
	{
		if(ldr[i]==a)
		{
			x=i;
		}
		if(ldr[i]==b)
		{
			y=i;
		}
	}
	if(x<y)
	return 0;
	else
	return 1;
}
void create(btptr &h,int ldr[],int dlr[],int p,int n)
{
	if(p>=n)
	{
		return;
	}
	else
	if(h==NULL)
	{
		h=new bstnode;
		h->data=dlr[p];
		h->lchild=NULL;
		h->rchild=NULL;
		p++;
	}
	else
	{
		if(is_left(ldr,h->data,dlr[p],n))
		{
			create(h->lchild,ldr,dlr,p,n);
		}
		else
		{
			create(h->rchild,ldr,dlr,p,n);
		}
	}
}
int main()
{
	int ldr[30];
	int dlr[30];
	int n;
	cout<<"enter the num of elements ";
	cin>>n;
	cout<<"enter the ldr order ";
	for(int i=0;i<n;i++)
	{
		cin>>ldr[i];
	}
	cout<<"enter the dlr order ";
	for(int i=0;i<n;i++)
	{
		cin>>dlr[i];
	}
	btptr root;
	root=NULL;
	for(int i=0;i<n;i++)
	create(root,ldr,dlr,i,n);
	cout<<"the pre_order print is"<<endl;
	preorder(root);
	cout<<endl<<"the in_order print is"<<endl;
	inorder(root);
	return 0;
}
