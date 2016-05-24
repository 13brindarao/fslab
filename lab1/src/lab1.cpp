//============================================================================
// Name        : lab1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string.h>
using namespace std;

class student
{
	char str[100];
	public: friend void console();
			friend void file();
};

void console()
{
	int i,j,n,length;
	cout<<"\nEnter the number of strings: ";
	cin>>n;
	student s[n];
	cout<<"\nEnter the strings: ";
	for(i=0;i<n;i++)
		cin>>s[i].str;
	cout<<"String in reverse: \n";
	for(i=0;i<n;i++)
	{
		length=strlen(s[i].str);
		for(j=length-1;j>=0;j--)
			cout<<s[i].str[j];
		cout<<"\n";
	}
}

void file()
{
	int i;
	fstream f1,f2;
	char buffer[100],fname1[100],fname2[100];
	cout<<"\nEnter file name to read strings from: ";
	cin>>fname1;
	cout<<"\nEnter file name to store the output: ";
	cin>>fname2;
	f1.open(fname1,ios::in);
	f2.open(fname2,ios::out);
	if(!f1)
	{
		cout<<"File: "<<fname1<<" does not exist!\n";
		exit(0);
	}
	if(!f2)
	{
		cout<<"File: "<<fname2<<" does not exist!\n";
		exit(0);
	}
	while(!f1.eof())
	{
		f1.getline(buffer,25);
		for(i=strlen(buffer)-1;i>=0;i--)
			f2<<buffer[i];
		f2<<"\n";		
	}
	f1.close();
	f2.close();
	cout<<"\n";
}

int main()
{
	int choice;
	while(1)
	{
		cout<<"\nTo perform string reversal operation for a given input\nEnter 1.Console\t2.File\t3.Exit\n";
		cin>>choice;
		switch(choice)
		{
			case 1: cout<<"Standard I/O operation via console";
					console();
					break;
			
			case 2: cout<<"File Operation";
					file();
					break;
					
			case 3: exit(0);
			
			default: cout<<"Invlaid input!";
		}
	}
	return 0;
}
