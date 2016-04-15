//============================================================================
// Name        : lab1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<string.h>
#include<fstream>

using namespace std;
fstream fp1,fp2;

void reverse(char *);
char str[30];

int main()
{
	int ch,n,i;
	cout<<"Enter your choice: 1.String reversal through terminal 2.String reversal through files" <<endl;
	cin>>ch;
	switch(ch)
	{
		case 1:cout<<"Enter the number of names:";
		cin>>n;
		for(i=0;i<n;i++)
		{
		    cout<<"Enter the string:"<<endl;
		    cin>>str;
		    reverse(str);
		}
		break;
		
		case 2: fp1.open("input.txt",ios::in);
		fp2.open("output.txt",ios::out);
		while(!fp1.eof())
		{
			fp1.getline(str,21);
			reverse(str);
			fp2<<str;
		}
		fp1.close();
		fp2.close();
		break;
		
		default: cout<<"Wrong choice"<<endl;
		break;
	}
}

void reverse(char *)
{
	int len,i;
	len=strlen(str);
	for(i=0;i<len/2;i++)
	{
		char temp=str[i];
		str[i]=str[len-1-i];
		str[len-1-i]=temp;
	}
	cout<<"The reverse of the string is:"<<str<<endl;
}
