//============================================================================
// Name        : lab3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include<iostream>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<string.h>
using namespace std;

class student
{
	public: int semester;
			string buffer,usn,branch,name,sem;
			
			void read();
			void pack();
			void write(char* fname);
			int del(string key,char* fname);
			int search(string key,char* fname);
			void unpack();
			void modify(string key,char* fname);
};

void student::read()
{
	cout<<"USN: ";
	cin>>usn;
	cout<<"Name: ";
	cin>>name;
	cout<<"Branch: ";
	cin>>branch;
	cout<<"Semester: ";
	cin>>semester;
}

void student::pack()
{
	stringstream out;
	out<<semester;
	sem=out.str();
	buffer.erase();
	buffer+=usn+'|'+name+'|'+branch+'|'+sem+'$'+'\n';	//change here from pgm2 (only 2 differences)
}

void student::write(char* fname)
{
	fstream f;
	f.open(fname,ios::out|ios::app);
	f<<buffer;
	f.close();	
}

int student::del(string key,char* fname)
{
	fstream f;
	char del_mark='*';
	int pos=0,flag=0;
	pos=search(key,fname);
	if(pos)
	{
		f.open(fname);
		pos=pos-(buffer.size()+1);    //change here from pgm2
		f.seekp(pos,ios::beg);
		f.put(del_mark);
		flag=1;
	}
	f.close();
	if(flag==1)
		return 1;
	else
		return 0;
} 

int student::search(string key,char* fname)
{
	fstream f;
	int flag=0,pos=0;
	f.open(fname,ios::in);
	if(!f)
	{
		cout<<"File "<<fname<<" does not exist!\n";
		exit(0);
	}
	while(!f.eof())
	{
		getline(f,buffer);
		unpack();
		if(key==usn)
		{
			flag=1;
			cout<<"\nRecord found: "<<buffer;
			pos=f.tellg();
			cout<<" at position: "<<pos<<"\n";
			f.close();
			return pos;
		}
	}
	f.close();
	cout<<"\nRecord not found!";
	return 0;
} 

void student::unpack()
{
	int i=0;
	usn.erase();
	while(buffer[i]!='|')
		usn+=buffer[i++];
}

void student::modify(string key,char* fname)
{
	int choice,i;
	i=del(key,fname);
	if(i)
	{
		cout<<"\nEnter the modified record\n";
	    cout<<"USN: ";
		cin>>usn;
		cout<<"Name: ";
		cin>>name;
		cout<<"Branch: ";
		cin>>branch;				
		cout<<"Semester: ";
		cin>>semester;
	}
	buffer.erase();
	pack();
	write(fname);
}
 

int main()
{
	student s;
	int choice,i;
	string key;
	char fname[100];
	cout<<"\nEnter\n1.Insert record\n2.Delete record\n3.Modify record\n4.Search record\n";
	cin>>choice;
	switch(choice)				
	{
		case 1: cout<<"Enter the file name to insert values into: ";
				cin>>fname;
				s.read();
				s.pack();
				s.write(fname);
				break;
				
		case 2: cout<<"Enter the file name to delete values from: ";
				cin>>fname;
				cout<<"Enter the USN of the record to delete: ";
				cin>>key;
				i=s.del(key,fname);
				if(i==1)
					cout<<"Deletion successful\n";
				else
					cout<<"Deletion error\n";
				break;
				
		case 3: cout<<"Enter the file name in which record modification operation must be perfromed: ";
				cin>>fname;
				cout<<"Enter the existing USN value of a record to be modified: ";
				cin>>key;
				s.modify(key,fname);
				break; 
				
		case 4: cout<<"Enter the file name to search records from: ";
				cin>>fname;
				cout<<"Enter the USN of the record to search for: ";
				cin>>key;
				i=s.search(key,fname);
				break; 
		
		default: cout<<"Wrong choice!";
	}
	return 0;
}

