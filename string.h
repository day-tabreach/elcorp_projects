#pragma once
#include <iostream>
#include <cstring>

#define max 100
/*
	don't forget to change Flickr username to something not linked to my email
	wouldn't want anyone to find that one....
*/

class string 
{
	public: 
	string(); 						//Default constructor
	string(const string &);			//Copy constructor
	string(string &&);
	string(const char *);			//C-string constructor

	~string();				//destructor?
	
	string & operator = (const string &);	//copy operator
	string & operator = (string &&);		//move operator
	string & operator = (const char *);		//c-string copy operator

	const char & operator[](int) const;		//value subscript
	char & operator[](int);					//reference subscript

	int size() const;					//returns the size of the string
	int length() const;				//also returns the size of the string
	int capacity() const;	
	const char * get_data() const;			//accessor to data

	int set_length(int);
	int set_capacity(int);

	void clear();
	void resize(int);
	void reserve(int);
	const char * c_str();
	string substr(int, int);
	string append(string &);
	string insert(string &, int);
	
	friend std::ostream & operator << (std::ostream &, const string &);	//stream insertion (cout)
	friend std::istream & operator >> (std::istream &, string &);			//stream extraction (cin)
	
	private:
	int * len;
	int * cap;
	char * data;
};

bool operator == (const string &, const string &);	//Equal to operator
bool operator != (const string &, const string &);	//Not equal to operator
bool operator >= (const string &, const string &);	//Greater than or equals to operator
bool operator <= (const string &, const string &);	//Less than or equal to operator
bool operator >  (const string &, const string &);	//Greater than operator
bool operator <  (const string &, const string &);	//Less than operator

std::ostream & operator << (std::ostream &, const string &);
std::istream & operator >> (std::istream &, string &);
