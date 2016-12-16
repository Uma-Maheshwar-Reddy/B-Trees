#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
using namespace std;
struct student
{
	char name[30];
	char rno[5];
	char branch[5];
};
void pack(ofstream &fout)
{
	student s;
	char buffer[100];
	cout<<"enter the name of student ";
	cin>>s.name;
	strcpy(buffer,s.name);
	strcat(buffer,"|");
	cout<<"enter rno ";
	cin>>s.rno;
	strcat(buffer,s.rno);
	strcat(buffer,"|");
	cout<<"enter branch ";
	cin>>s.branch;
	strcat(buffer,s.branch);
	strcat(buffer,"#");
	fout<<buffer;
}
void create_index(ifstream &fin,int arr[][2])
{
	int i=0;
	char buffer[100];
	while(!fin.eof())
	{
		arr[i][1]=fin.tellg();
		fin.getline(buffer,100,'#');
		cout<<buffer<<endl;
		int p=0;
		while(buffer[p]!='|')
		{
			p++;
		}
		p++;
		char num[5];
		int q=0;
		while(buffer[p]!='|')
		{
			num[q]=buffer[p];
			p++;
			q++;
		}
		num[q]='\0';
		arr[i][0]=atoi(num);
		i++;
	}
}
int main()
{
	ofstream fout;
	fout.open("records.txt");
	int n;
	cout<<"enter the number of student details ";
	cin>>n;
	for(int i=0;i<n;i++)
	{
		pack(fout);
		if(i!=n-1)
		{
			fout<<endl;
		}
	}
	fout.close();
	int arr[20][2];
	ifstream fin;
	fin.open("records.txt");
	create_index(fin,arr);
	fin.close();
	fout.open("index_file.txt");
	for(int i=0;i<n;i++)
	{
		fout<<arr[i][0]<<"|"<<arr[i][1]<<endl;
	}
	fout.close();
	fout.open("records.txt",ios::app);
	cout<<"enter the details of student record you wish to add ";
	fout<<endl;
	arr[n][1]=fout.tellp();
	pack(fout);
	fout.close();
	char buffer[100];
	fin.open("records.txt");
	fin.seekg(arr[n][1],ios::beg);
	fin.getline(buffer,100,'#');
	int p=0;
	while(buffer[p]!='|')
	{
		p++;
	}
	p++;
	char num[5];
	int q=0;
	while(buffer[p]!='|')
	{
		num[q]=buffer[p];
		p++;
		q++;
	}
	num[q]='\0';
	arr[n][0]=atoi(num);
	n++;
	int k;
	cout<<"enter the roll num of student record you want ";
	cin>>k;
	char b[30];
	while(k!=-1)
	{
		for(int i=0;i<n;i++)
		{
			if(arr[i][0]==k)
			{
				fin.seekg(arr[i][1],ios::beg);
				fin>>b;
				cout<<"the record is "<<b<<endl;
				break;
			}
		}
		cout<<"enter roll num ";
		cin>>k;
	}
	return 0;
}
