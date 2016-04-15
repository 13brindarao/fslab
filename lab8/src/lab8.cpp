//============================================================================
// Name        : lab8.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class namedlist
{
	fstream f1,f2;
	int left,right,mid,k,i,j;
	public: string merge(vector<string> fname,int left,int right);
			void sort(string fname);
};

void namedlist::sort(string fname)
{
	k=0;
	string l[100],temp,buffer;
	cout<<"\ntest: "<<fname;
	f1.open(fname.c_str(),ios::in);
	while(!f1.eof())
	{
		getline(f1,buffer);
		l[k++]=buffer;
	}
	for(i=0;i<k;i++)
		for(j=i+1;j<k;j++)
			if(l[i]>l[j])
			{
				temp=l[i];
				l[i]=l[j];
				l[j]=temp;
			}
	f1.close();
	f1.open((fname.c_str()),ios::out|ios::trunc);
	for(i=0;i<k;i++)
	{
		if(i!=k)
			f1<<l[i]<<"\n";
		else
			f1<<l[i];
	}
	f1.close();
	return;
}

string namedlist::merge(vector<string> fname,int left,int right)
{
	if(left==right)
		return fname[left];
	else if(right-left==1)
	{
		string buffer1,buffer2;
		f1.open(fname[left].c_str(),ios::in);
		f2.open(fname[right].c_str(),ios::in);
		ofstream of((fname[left]+'a').c_str());
		getline(f1,buffer1);
		getline(f2,buffer2);
		while(!f1.eof()&&!f2.eof())
		{
			if(buffer1==buffer2)
			{
				of<<buffer1<<"\n";
				getline(f1,buffer1);
				getline(f2,buffer2);
			}
			else if(buffer1<buffer2)
			{
				of<<buffer1<<"\n";
				getline(f1,buffer1);
			}
			else
			{
				of<<buffer2<<"\n";
				getline(f2,buffer2);
			}
		}
		while(!f1.eof())
		{
			of<<buffer1<<"\n";
			getline(f1,buffer1);
		}
		while(!f2.eof())
		{
			of<<buffer2<<"\n";
			getline(f2,buffer2);
		}
		f1.close();
		f2.close();
		of.close();
		return fname[left]+'a';
	}
	else
	{
		int mid=(right+left)/2;
		string f1,f2,f3;
		f1=merge(fname,left,mid);
		f2=merge(fname,mid+1,right);
		vector<string> a;
		a.push_back(f1);
		a.push_back(f2);
		f3=merge(a,0,1);
		return f3;
	}
}

int main()
{
	namedlist n1;
	int n,i;
	cout<<"\nEnter the number of files to be merged: ";
	cin>>n;
	vector<string> fname;
	string fn;
	cout<<"\nEnter the names of the "<<n<<" files: ";
	for(i=0;i<n;i++)
	{
		cin>>fn;
		n1.sort(fn);
		fname.push_back(fn);
	}
	fn=n1.merge(fname,0,n-1);
	cout<<"\nAll the input files have their data merged and sorted into file: "<<fn<<"\n";
	return 0;
}
