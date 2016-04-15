//============================================================================
// Name        : lab7.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>

using namespace std;

class coseq
{
	public:
		string list1[100],list2[100];
		int c1, c2;
		void read_lists();
		void sort_lists();
		void match_lists();
};

int main()
{
	system("clear");
	coseq c;
	c.read_lists();
	c.sort_lists();
    	cout<<"\n\nCommon Names in Both Lists Are : \n";
	c.match_lists();
	return 0;
}

void coseq::read_lists()
{
	fstream fp;
	string name;

	c1=0;
	fp.open("f2.txt",ios::in);
	while(fp)
	{
		getline(fp,name);		
		list1[c1++]=name;	
	}
	fp.close();
	c2 = 0;
	fp.open("f3.txt",ios::in);
	while(fp)
	{
		getline(fp,name);
		list2[c2++]=name;
	}
	fp.close();
}

void coseq::sort_lists()
{
	int i,j;
	string temp;

	for(i=0;i<c1;i++)
	{
		for(j=i+1;j<c1;j++)
		{
			if(list1[i]>list1[j])
			{
				temp=list1[i];
				list1[i]=list1[j];
				list1[j]=temp;
			}
		}
	}
    
    cout<<"\nThe Sorted Contents of List 1 : \n";
    	for(i=0;i<=c1;i++)
        cout<<list1[i]<<"\n";
	for(i=0;i<c2;i++)
	{
		for(j=i+1;j<=c2;j++)
		{
			if(list2[i]>list2[j])
			{
				temp=list2[i];
				list2[i]=list2[j];
				list2[j]=temp;
			}
		}
	}

    cout<<"\nThe Sorted Contents of List 2 : \n";
    for(i=0;i<=c2;i++)
      	cout<<list2[i]<<"\n";
}

void coseq::match_lists()
{
	int i=0,j=0;
	while(i<=c1 && j<=c2)
	{
		if(list1[i]==list2[j])
		{
			cout<<list1[i]<<endl;
			i++;
			j++;
		}
		if(list1[i]<list2[j])i++;
		if(list1[i]>list2[j])j++;
	}
}

