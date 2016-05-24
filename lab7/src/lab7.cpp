//============================================================================
// Name        : lab7.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<sys/types.h>
#include<unistd.h>
using namespace std;
#define max 20
class seqo
{
    string l1[max];
    string l2[max];
public:
    int c1;
    int c2;
    void load(char flname[max],char flname1[max]);
    void sort();
    void match();
};
void seqo :: load(char flname[max],char flname1[max])
{
    int i=0;
    c1=0;c2=0;
    fstream fp1,fp2;
    string buffer;
    fp1.open(flname,ios::in);
    fp2.open(flname1,ios::in);
   // cout<<"opened file"<<endl;
    while(!fp1.eof())
    {
        //cout<<"*";
        getline(fp1,buffer);
        l1[i]=buffer;
        i++;
        c1++;   
    }
    cout<<endl;
    i=0;
    while(!fp2.eof())
    {
      
        getline(fp2,buffer);
        l2[i]=buffer;
        i++;
        c2++;   
    }

     cout<<"content of l1:"<<endl;
    for(i=0;i<c1;i++)
        cout<<l1[i]<<endl;
     cout<<"content of l2"<<endl;
    for(i=0;i<c2;i++)
        cout<<l2[i]<<endl;
    fp1.close();
    fp2.close();
}
void seqo :: sort()
{
    string temp;
    int i=0,j=0;
    for(i=0;i<c1;i++)
    {
     for(j=i+1;j<c1;j++)
        {
           if(l1[i]>l1[j])
           {
               temp=l1[i];
               l1[i]=l1[j];
               l1[j]=temp;
           }
        }    
    }
    for(i=0;i<c2;i++)
    {
     for(j=i+1;j<c2;j++)
        {
           if(l2[i]>l2[j])
           {
               temp=l2[i];
               l2[i]=l2[j];
               l2[j]=temp;
           }
        }    
    }
   cout<<"new content of l1:"<<endl;
    for(i=0;i<c1;i++)
        cout<<l1[i]<<endl;
    cout<<"new content of l2"<<endl;
    for(i=0;i<c2;i++)
        cout<<l2[i]<<endl;
}
void seqo :: match()
{
     cout<<"matching records are :"<<endl;
    int i=0,j=0,k=0;
  while(i<c1 && j<c2)
	{
		if(l1[i]==l2[j])
		{
			cout<<l1[i]<<endl;
			i++;
			j++;	
		}
		if(l1[i]<l2[j])
		{
			i++;
			continue;
		}
		if(l1[i]>l2[j])
		{
			j++;
			continue;
		}
	}
		
}
int main()
{
    int c1=0,c2=0;
    char fn1[max],fn2[max];
    cout<<"enter the first filename :";
    cin>>fn1;
    cout<<endl;
    cout<<"enter the second filename :";
    cin>>fn2;
    cout<<endl;
    seqo s;
    s.load(fn1,fn2);
    s.sort();
    s.match();
    cout<<"program terminate"<<endl;
}
