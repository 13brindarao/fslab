//============================================================================
// Name        : lab12.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
using namespace std;


class node{
	node *p;
	int offset;
public:
	node(int ioffset)
	{
		offset=ioffset;
		p=NULL;
	}
	/*node()
	{
		p=NULL;
	}*/
friend class list;
};


class list{
       node *head;
public:
      list()
      {
         head = NULL;
      }
      void insert(int offset)
	{
	node *temp = new node(offset);
        temp->p = head;
	head = temp;
	}
      int get()
        {
	int offset;
	if (head == NULL) {
		return -1;
	}
	node *temp=head;
        head = head->p;
        offset = temp->offset;
        delete temp;
	return offset;
        }
};


class Student
{
public:
  string name;
  string usn;
  string sem;
  string branch;
public:
    Student ()
  {
  }
  Student (string iname, string iusn, string isem, string ibranch)
  {
	name=iname;
	usn=iusn;
	sem=isem;
	branch=ibranch;
 }
  string pack(int n)
  {
    string s;
    s = name + "|" + usn + "|" + sem + "|" + branch;
    s.resize(n,'$');
    return s;
  }
  static Student unpack (string in)
  {
    stringstream ss;
    ss << in;
    string name, usn, sem, branch;
    getline (ss, name, '|');
    getline (ss, usn, '|');
    getline (ss, sem, '|');
    getline (ss, branch, '$');
    return Student (name, usn,sem, branch);
  }
  bool match (string key, string value)
  {
    return (key == "name" && value == name) ||
      (key == "usn" && value == usn) ||
      (key == "sem" && value== sem) ||
      (key == "branch" && value == branch);
  }
};

class flbrfile {
	string filename;
        list lar;
        int recordsize;
        public:
        flbrfile(string fname, int rsize)
	{
		filename=fname;
		recordsize=rsize;
	}

	void addrecord(string s)
	{

        int offset = lar.get();
        if(offset == -1) {
		fstream of(filename.c_str(),ios::out|ios::app);
	        if(!of)
   	             cout<<"Cant write to file"<<endl;
		of.write(s.c_str(),recordsize);
                of.close();
	}
	else {
		fstream of(filename.c_str(),ios::out|ios::in);
	        if(!of)
   	             cout<<"Cant write to file"<<endl;
		of.seekp(offset);
		of.write(s.c_str(),recordsize);
        	of.close();
        }
	}

        void deleterecord(string key,string value)
	{
        char buffer[recordsize];
        int off;
        fstream of(filename.c_str(),ios::in|ios::out);
        buffer[recordsize + 1] = '$';
	while(!of.eof()) {
		off = of.tellg();
		of.read(buffer,recordsize);
		Student s = Student::unpack(buffer);
		if (s.match(key,value)) {
		    of.clear();
                    of.seekp(off);
		    of.write("\n",1);
                    lar.insert(off);
		}

        }
	}

};
int main()
{


	Student s1("gitwe","123","is","7");
	Student s2("gitwe2","1232","cs","8");
	Student s3("gita","1233","es","9");
	//Student s1("gitwe","123","is","7");
	flbrfile f("abc.txt",100);
	f.addrecord(s1.pack(100));
	f.addrecord(s2.pack(100));
	f.addrecord(s3.pack(100));
	f.deleterecord("name","gitwe2");
	Student s4("gitaer","1233","es","9");
	f.addrecord(s4.pack(100));
return 0;
}

