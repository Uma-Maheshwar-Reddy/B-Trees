#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
struct student
{
	char name[50];
	char rno[5];
	char branch[10];
};
void pack(ofstream &fout)
{
	char buffer[100];
	struct student s;
	cout<<"enter name"<<endl;
	cin>>s.name;
	strcpy(buffer,s.name);
	int i;
	char a[2]={'*','\0'};
	for(i=strlen(buffer);i<49;i++)
	strcat(buffer,a);
	cout<<strlen(buffer)<<endl;
	strcat(buffer,"|");
	cout<<"enter branch"<<endl;
	cin>>s.branch;
	strcat(buffer,s.branch);
	for(int i=strlen(buffer);i<60;i++)
	strcat(buffer,a);
	cout<<strlen(buffer)<<endl;
	strcat(buffer,"|");
	cout<<"enter roll num"<<endl;
	cin>>s.rno;
	strcat(buffer,s.rno);
	for(int i=strlen(buffer);i<65;i++)
	strcat(buffer,a);
	strcat(buffer,"#");
	cout<<strlen(buffer)<<endl;
	int len=strlen(buffer);
	cout<<"the length of input given is "<<len<<endl;
	fout<<buffer;
}
void create_index(ifstream &fin,int arr[][2])
{
	int i=0;
	char buffer[100];
	while(!fin.eof())
	{
		arr[i][0]=i;
		arr[i][1]=fin.tellg();
		fin.getline(buffer,100,'#');
		cout<<buffer;
		i++;
	}
}
int search(int arr[][2],int lo,int hi,int key)
{
	if(hi<lo)
	{
		return -1;
	}
	if(hi==lo)
	{
		if(arr[hi][0]==key)
		{
			return hi;
		}
		else
		return -1;
	}
	else
	{ 	cout<<"l"<<endl;
		int mid=(hi+lo)/2;
		if(arr[mid][0]==key)
		return mid;
		if(arr[mid][0]>key)
		return search(arr,lo,mid-1,key);
		else
		return search(arr,mid+1,hi,key);
	}
}
int main()
{
	ofstream fout;
	int n;
	fout.open("myfile.txt");
	cout<<"enter the number of records "<<endl;
	cin>>n;
	int i=0,j=0;
	for(int i=0;i<n;i++)
	{
		pack(fout);
		if(i!=n-1)
		fout<<endl;
	}
	fout.close();
	char buffer[100];
	ifstream fin;
	int arr[20][2];
	fin.open("myfile.txt");
	create_index(fin,arr);
	fin.close();
	int key;
	cout<<endl<<"enter the RRN of student you want ";
	cin>>key;
	fin.open("myfile.txt");
	while(key!=-1)
	{
		int k=search(arr,0,n-1,key);
		cout<<"K:"<<k<<endl;
		if(k!=-1)
		{
			fin.seekg(arr[k][1],ios::beg);
			fin.getline(buffer,100,'#');
			cout<<"the record is "<<endl;
			cout<<buffer;
		}
		cout<<endl<<"enter the RRN of student you want ";
		cin>>key;
	}
	fin.close();
	fout.open("the_index_file.txt");
	for(int p=0;p<i;p++)
	{
		fout<<arr[p][0]<<"|"<<arr[p][1]<<endl;
	}
	fout.close();
	return 0;
}
