#include<iostream>
using namespace std;
typedef
struct bstnode
{
	int d;
	bstnode* lchild;
	bstnode* rchild;
}*bstptr;
typedef
struct lnode
{
	int data;
	bstnode* b;
	lnode* next;
}*lptr;
void addend(lptr &h,int k)
{
	if(h==NULL)
	{
		h=new lnode;
		h->data=k;
		h->b=NULL;
		h->next=NULL;
	}
	else
	{
		lptr t=h;
		while(t->next!=NULL)
		{
			t=t->next;
		}
		t->next=new lnode;
		t=t->next;
		t->data=k;
		t->next=NULL;
		t->b=NULL;
	}
}void insert(bstptr &p,int &a)
{
	if(p==NULL)
	{
		p=new bstnode;
		p->lchild=NULL;
		p->rchild=NULL;
		p->d=a;
	}
	else
	{
		if(p->d>a)
		{
			insert(p->lchild,a);
		}
		else
		{
			insert(p->rchild,a);
		}
	}
}
void create(lptr &h)
{
	lptr t=h;
	int in;
	while(t!=NULL)
	{
		cout<<"enter bst of node with "<<t->data<<" ";
		cin>>in;
		while(in!=-1)
		{
			insert(t->b,in);
			cout<<"enter data ";
			cin>>in;
		}
		t=t->next;
	}
}
void print(lptr &l,bstptr& b,int& c)
{
	if(l==NULL)
	return;
	else
	if(b==NULL&&c==0)
	{
		if(l->next!=NULL)
		{
			print(l->next,l->next->b,c);
		}
		else
		return;
	}
	else
	if(b==NULL&&c!=0)
	{
		return;
	}
	else
	{
		if(c==0)
		{
			if(l->next!=NULL)
			{
				cout<<l->data<<"-"<<l->next->data<<":";
			}
			else
			{
				cout<<l->data<<"-   ";
			}
			c++;
		}
		print(l,b->lchild,c);
		cout<<b->d<<" ";
		print(l,b->rchild,c);
		if(b==l->b&&l->next!=NULL)
		{
			c=0;
			cout<<endl;
			print(l->next,l->next->b,c);
		}
	}
}
void inorder(bstptr &q)
{
	if(q!=NULL)
	{
		inorder(q->lchild);
		cout<<q->d<<" ";
		inorder(q->rchild);
	}
}
bool search(lptr &h,bstptr &b,int k)
{
	if(h==NULL||b==NULL) return 0;
	else
	if(h->next==NULL&&h->data<=k)
	{
		if(b->d==k) return 1;
		else
		if(k<b->d)
		return search(h,b->lchild,k);
		else
		return search(h,b->rchild,k);
	}
	else
	if(h->data<=k&&h->next->data>k)
	{
		if(b->d==k) return 1;
		else
		if(k<b->d)
		return search(h,b->lchild,k);
		else
		return search(h,b->rchild,k);
	}
	else
	return search(h->next,h->next->b,k);
}
int main()
{
	lptr h=NULL;
	int in;
	cout<<"enter the range values ";
	cin>>in;
	while(in!=-1)
	{
		addend(h,in);
		cout<<"enter range ";
		cin>>in;
	}
	create(h);
	int count=0;
	print(h,h->b,count);
	cout<<endl<<"enter the key you wish to search ";
	cin>>in;
	while(in!=-1)
	{
		if(search(h,h->b,in))
		{
			cout<<"key "<<in<<" found ";
		}
		else
		{
			cout<<"key "<<in<<" not found ";
		}
		cout<<"enter search ";
		cin>>in;
	}
	return 0;
}
