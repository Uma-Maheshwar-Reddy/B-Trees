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
struct queue
{
	int size;
	int front;
	int rear;
	bptr elem[20];
};
void enque(struct queue &q,bptr &a)
{
	if((q.rear+1)%q.size==q.front)
	{
		cout<<"the queue is full"<<endl;
	}
	else
	{
		if(q.front==-1)
		q.front=0;
		q.rear=(q.rear+1)%q.size;
		q.elem[q.rear]=a;
	}
}
bptr deque(struct queue &q)
{
	if(q.rear==-1)
	{
		cout<<"the queue is empty "<<endl;
	}
	else
	{
		bptr t=q.elem[q.front];
		if(q.front==q.rear)
		{
			q.rear=-1;
			q.front=-1;
		}
		else
		{
			q.front=(q.front+1)%q.size;
		}
		return t;
	}
}
void levelprint(bptr &h,int &d)
{
	struct queue q;
	q.front=-1;
	q.rear=-1;
	q.size=20;
	bptr temp;
	temp=new bnode;
	temp->arr=new int[2*d];
	temp->ptr=new bptr[2*d+1];
	for(int i=0;i<=2*d;i++)
	{
		if(i!=2*d)
		temp->arr[i]=-1;
		temp->ptr[i]=NULL;
	}
	temp->parent=NULL;
	temp->count=-1;
	if(h==NULL)
	{
		return;
	}
	enque(q,h);
	enque(q,temp);
	bptr t;
	while(q.front!=-1)
	{
		t=deque(q);
		if(t->count==-1&&q.front!=-1)
		{
			cout<<endl;
			enque(q,t);
		}
		else
		{
			for(int i=0;i<=t->count;i++)
			{
				if(i!=t->count)
				cout<<t->arr[i]<<" ";
				if(t->ptr[i]!=NULL)
				enque(q,t->ptr[i]);
				if(i==t->count) cout<<"** ";
			}
		}	
	}
}
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
void set_parent(bptr &h)
{
	if(h!=NULL)
	{
		for(int i=0;i<=h->count;i++)
		{
			if(h->ptr[i]!=NULL)
			{
				h->ptr[i]->parent=h;
			}
		}
		for(int i=0;i<=h->count;i++)
		{
			if(h->ptr[i]!=NULL)
			{
				set_parent(h->ptr[i]);
			}
		}
	}
}
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
			if(is_emp(l,d))
			{
				cout<<l->arr[0]<<" the parents first elem "<<med<<endl;
				insert_sort(l,med);
				cout<<l->arr[0]<<endl;
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
				while(r->parent!=NULL)
				r=r->parent;
				return r;
			}
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
		i=0;
		h->parent=NULL;
		set_parent(h);
		levelprint(h,d);
		cout<<endl<<"enter the data to be added ";
		cin>>in;
	}
	levelprint(h,d);
	return 0;
}
