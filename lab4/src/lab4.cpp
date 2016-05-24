//============================================================================
// Name        : lab4.cpp
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
	public: int semester,count,rrn_list[100];
			string buffer,usn,branch,name,sem;
			
			void read();
			void pack();
			void write(char* fname);
			void unpack();
			void create_rrn(char * fname);
			void search_by_rrn(int rrn,char* fname);
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
	buffer+=usn+'|'+name+'|'+branch+'|'+sem+'$'+'\n';
}

void student::write(char* fname)
{
	int pos;
	fstream f;
	f.open(fname,ios::out|ios::app);
	f<<buffer;
	pos=f.tellp();
	f.close();	
	rrn_list[++count]=pos;
}

void student::unpack()
{
	int i=0;
	usn.erase();
	while(buffer[i]!='|')
		usn+=buffer[i++];
}

void student::create_rrn(char* fname)
{
	fstream f;
	int pos;
	count=0;
	f.open(fname,ios::in);
	while(!f.eof())
	{
		pos=f.tellg();
		buffer.erase();
		getline(f,buffer);
		if(buffer.empty())
			continue;
		rrn_list[++count]=pos;
	}	
	f.close();
}

void student::search_by_rrn(int rrn,char* fname)
{
	int pos=-1;
	fstream f;
	if(rrn>count)	
		cout<<"\nRecord number does not exist!";
	else
	{
		buffer.erase();
		f.open(fname);
		pos=rrn_list[rrn];
		f.seekp(pos,ios::beg);
		getline(f,buffer);
		cout<<"\nRecord is: "<<buffer<<"\n";
	}
}

int main()
{
	int choice,rrn;
	student s;
	char* fname;
	cout<<"\nEnter the file name to search for records: ";
	cin>>fname;
	s.create_rrn(fname);
	cout<<"\nEnter 1.Add records\t2.Search\n";
	cin>>choice;
	switch(choice)
	{
		case 1: s.read();
				s.pack();
				s.write(fname);
				break;
				
		case 2: cout<<"\nEnter RRN value: ";
				cin>>rrn;
				s.search_by_rrn(rrn,fname);
				break;
				
		default:exit(0);
	}	
	return 0;
}



 /*#include<stdio.h>
#include<stdlib.h>
#include<fstream>

#include<string.h>

#include<iomanip>
#include<iostream>
using namespace std;

class student
{
	public:char name[15],usn[10],age[5],sem[5],branch[15],buffer[100];
};


void writerecord()
{
	fstream file;
	student s;
	int k,n;
	file.open("file.txt",ios::out|ios::app);

	printf("how many records\n");
	scanf("%d",&n);
	for(k=1;k<=n;k++)
	{
		cout<<"\nenter the student name: ";
		cin>>s.name;
		cout<<"\nenter the usn: ";
		cin>>s.usn;
		cout<<"\nenter the age: ";
		cin>>s.age;
		cout<<"\nenter the sem: ";
		cin>>s.sem;
		cout<<"\nenter the branch: ";
		cin>>s.branch;
		file<<k<<"|"<<s.name<<"|"<<s.usn<<"|"
		<<s.age<<"|"<<s.sem<<"|"<<s.branch<<"\n";
	}
	file.close();
}



void search()
{
	char rrn[10],rrn1[10][15];
	int i;
	student std[100];
	cout<<"\n enter the rrn to be searched";
	cin>>rrn;
	fstream file;
	file.open("file.txt",ios::in);
	if(!file)
	{
		cout<<"\n can not open the file in input mode";

		exit(0);
	}
	i=0;
	printf("\n rrn\tname\tusn\tage\tsem\tbranch\n");
	while(!file.eof())
	{
		file.getline(rrn1[i],4,'|');
		file.getline(std[i].name,15,'|');
		file.getline(std[i].usn,15,'|');
		file.getline(std[i].age,5,'|');
		file.getline(std[i].sem,5,'|');
		file.getline(std[i].branch,15,'\n');
		i++;
	}

	for(int j=0;j<i-1;j++)
	{
		if(strcmp(rrn,rrn1[j])==0)
		{
			printf("\n%s\t%s\t%s\t%s\t%s\t%s\n",
			rrn,std[j].name,std[j].usn,std[j].age,
			std[j].sem,std[j].branch);
			printf("\n record found\n");
			file.close();
			return;
		}
	}
	cout<<"\nrecord not found\n";
	file.close();
	return;
}


void displayfile()
{
	student s;
	char rrn[10];
	fstream file;
	file.open("file.txt",ios::in);
	if(!file)
	{
		cout<<"\ncannot open the file in input mode\n";
		exit(1);
	}
	cout<<"\n";
	printf("rrn\tname\t\tusn\t\tage\t\tsem\t\tbranch\n");
	while(!file.eof())
	{
		file.getline(rrn,4,'|');
		file.getline(s.name,15,'|');
		file.getline(s.usn,15,'|');
		file.getline(s.age,5,'|');
		file.getline(s.sem,5,'|');
		file.getline(s.branch,15,'\n');
		printf("\n%s\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n",
		rrn,s.name,s.usn,s.age,s.sem,s.branch);

	}
	file.close();
	return;
}



int main()
{
	int choice;
	while(1)
	{
		cout<<"\n 0:exit";
		cout<<"\n 1:insert";
		cout<<"\n 2:search";
		cout<<"\n 3:display";
		cout<<"\n enter the choice=";
		cin>>choice;
		switch(choice)
		{
			case 1:writerecord();
				break;
			case 2:search();
				break;
			case 3:displayfile();
				break;
			case 0:exit(0);
			default:cout<<"\n invalid option";
				break;
		}

	}
}
*/
