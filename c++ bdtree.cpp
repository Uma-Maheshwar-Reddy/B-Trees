#include<iostream>
using namespace std;
typedef
struct bnode
{
	int *arr;
	bnode** ptr;
	bnode* parent;
	int count;
}*bptr;
//depth first traversal print
void print(bptr &h)
{
	if(h!=NULL)
	{
		for(int i=0;i<h->count;i++)
		{
			print(h->ptr[i]);
			cout<<h->arr[i]<<" ";
		}
		print(h->ptr[h->count]);
	}
}
//returns true if a node id not full
bool is_emp(bptr &h,int &d)
{
	if(h!=NULL)
	{
		if(h->count<=2*d-1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}
//returns true if a node is a leaf
bool is_leaf(bptr &h,int &d)
{
	for(int i=0;i<2*d+1;i++)
	{
		if(h->ptr[i]!=NULL)
		{
			return 0;
		}
	}
	return 1;
}
//bubble sort an array
void sort(int arr[],int count)
{
	int t;
	for(int j=0;j<count-1;j++)
	{
		for(int i=0;i<count-1;i++)
		{
			if(arr[i]>arr[i+1])
			{
				t=arr[i];
				arr[i]=arr[i+1];
				arr[i+1]=t;
			}
		}
	}
}
//inserts a data into a node and sorts all the pointers and key values accordingly
void insert_sort(bptr &h,int &key)
{
	if(key>h->arr[h->count-1])
	{
		h->arr[h->count]=key;
		h->ptr[h->count]=NULL;
		h->ptr[h->count+1]=NULL;
	}
	else
	if(key<h->arr[0])
	{
		for(int j=h->count;j>0;j--)
		{
			h->arr[j]=h->arr[j-1];
			h->ptr[j+1]=h->ptr[j];
		}
		h->arr[0]=key;
		h->ptr[0]=NULL;
		h->ptr[1]=NULL;
	}
	else
	{
		for(int i=0;i<h->count;i++)
		{
			if(h->arr[i]<key&&h->arr[i+1]>key)
			{
				for(int j=h->count;j>i+1;j--)
				{
					h->arr[j]=h->arr[j-1];
					h->ptr[j+1]=h->ptr[j];
				}
				h->arr[i+1]=key;
				h->ptr[i+1]=NULL;
				h->ptr[i+2]=NULL;
			}
		}
	}
	h->count++;
}
//to insert a node int a btree
bptr insert(bptr &l,bptr &p)
{
	if(l==NULL)
	{
		return p;
	}
	else
	{
		if(p->arr[0]<l->arr[0])
		{
			if(l->ptr[0]==NULL)
			p->parent=l;
			l->ptr[0]=insert(l->ptr[0],p);
		}
		else
		if(l->arr[l->count-1]<p->arr[0])
		{
			if(p->ptr[l->count]==NULL)
			p->parent=l;
			l->ptr[l->count]=insert(l->ptr[l->count],p);
		}
		else
		{
			for(int i=0;i<l->count-1;i++)
			{
				if(l->arr[i]<p->arr[0]&&l->arr[i+1]>p->arr[0])
				{
					if(l->ptr[i+1]==NULL)
					p->parent=l;
					l->ptr[i+1]=insert(l->ptr[i+1],p);
				}
			}
		}
		return l;
	}
}

bptr overflow(bptr &h,int d,int &k)
{
	/*first all the elem of the node and the data to be inserted are taken in an array and then it is sorted median is taken and then 3 cases*/
	int t[10];
	for(int i=0;i<h->count;i++)
	{
		t[i]=h->arr[i];
	}
	t[h->count]=k;
	sort(t,h->count+1);
	int n=2*d+1;
	int med=t[n/2];
	//cout<<med<<endl;
	bptr l=h->parent;
	/*if(l!=NULL)
	cout<<l->arr[0]<<endl;*/
	bptr t1,t2;
	t1=	NULL;
	t2=NULL;
	t1=new bnode;
	t2=new bnode;
	t1->arr=new int[2*d];
	t1->ptr=new bptr[2*d+1];
	t2->arr=new int[2*d];
	t2->ptr=new bptr[2*d+1];
	for(int i=0;i<n/2;i++)
	{
		t1->arr[i]=t[i];
		t2->arr[i]=t[(n/2)+i+1];
	}	
	for(int i=0;i<n;i++)
	{
		t1->ptr[i]=NULL;
		t2->ptr[i]=NULL;
	}
	t1->count=n/2;
	t2->count=n/2;
	//t1 and t2 are the nodes formed by splitting
	//case1 :there is no parent to the given node that is the given node is root 
	if(l==NULL)
	{
		l=new bnode;
		l->arr=new int[2*d];
		l->ptr=new bptr[2*d+1];
		l->count=1;
		l->arr[0]=med;
		
		for(int i=1;i<2*d;i++)
		{
			l->arr[i]=-1;
			l->ptr[i+1]=NULL;
		}
		l->ptr[0]=t1;
		l->ptr[1]=t2;
		t1->parent=l;
		t2->parent=l;
		l->parent=NULL;
		return l;
	}
	else
	{
		if(l!=NULL)
		{
			//the parent node is not null and it has empty space then first insert and sort the data and the pointer
			//then the split nodes t1 and t2 are on the left and right side of median
			if(is_emp(l,d))
			{
				insert_sort(l,med);
				for(int i=0;i<l->count;i++)
				{
					if(l->arr[i]==med)
					{
						l->ptr[i]=t1;
						l->ptr[i+1]=t2;
						t1->parent=l;
						t2->parent=l;
					}
				}
				bptr r=l;
				while(r->parent!=NULL) r=r->parent;
				return r;
			}
			//case 3: the node where the data is inserted has a parent which is not empty
			//store all info of parent in a temp node and then make its parent a leaf by making all the pointers null
			//then call overflow of parent and then again insert the pointers stored in temp and also split nodes t1 and t2
			else
			{
				bptr temp=NULL;
				temp=new bnode;
				temp->arr=new int[2*d];
				temp->ptr=new bptr[2*d+1];
				for(int i=0;i<=2*d;i++)
				{
					if(i!=2*d)
					temp->arr[i]=l->arr[i];
					if(l->ptr[i]==h)
					temp->ptr[i]=NULL;
					else
					temp->ptr[i]=l->ptr[i];
					l->ptr[i]=NULL;
				}
				temp->count=l->count;
				l=overflow(l,d,med);
				/*print(l);
				cout<<"rec l "<<endl;*/
				for(int i=0;i<=temp->count;i++)
				{
					if(temp->ptr[i]!=NULL)
					l=insert(l,temp->ptr[i]);
				}
				l=insert(l,t1);
				l=insert(l,t2);
				delete(temp);
				return l;
			}
		}
	}
}
//add function 
//case1 if h=NULL create new bnode
//case 2 the node is leaf and is empty insert and sort
//case3 move till tj=he leaf node and then if leaf is emp insert and sort else call overflow
bptr add(bptr &h,int a,int d)
{
	if(h==NULL)
	{
		h=new bnode;
		h->arr=new int[2*d];
		h->ptr=new bptr[2*d+1];
		h->count=1;
		for(int i=0;i<2*d;i++)
		{
			h->arr[i]=-1;
			h->ptr[i]=NULL;
		}
		h->ptr[2*d]=NULL;
		h->arr[0]=a;
		h->parent=NULL;
		return h;
	}
	else
	if(is_leaf(h,d)&&is_emp(h,d))
	{
		insert_sort(h,a);
		return h;
	}
	else
	{
		bptr t=h;
		while(!is_leaf(t,d))
		{
			if(t->arr[t->count-1]<a)
			t=t->ptr[t->count];
			else
			{
				for(int i=0;i<t->count;i++)
				{
					if(t->arr[i]>a)
					{
						t=t->ptr[i];
						break;
					}
				}
			}
		}
		if(is_emp(t,d))
		insert_sort(t,a);
		else
		h=overflow(t,d,a);
		return h;
	}
}
int main()
{
	bptr h;
	h=NULL;
	int in,d;
	cout<<"enter the value of d for the Bd-tree ";
	cin>>d;
	cout<<"enter the data to be added ";
	cin>>in;
	int i=0;
	while(in!=-1)
	{
		h=add(h,in,d);
		//parent of root is set to be null 
		h->parent=NULL;
		//prints after insertion of each element
		print(h);
		cout<<endl<<"enter the data to be added ";
		cin>>in;
	}
	print(h);
	return 0;
}
