#include "string.h"

string::string()
{
	len = new int(0);
	cap = new int(0);
	data = new char[*len];
	for (auto index = 0; index < *len; index++)
	{
		data[index] = '\0';
	}
}

string::string(const string &right)
{
	len = new int(right.length());
	data = new char[*len];
	cap = new int(right.capacity());
	for (auto index = 0; index < *len; index++)
	{
		data[index] = right[index];
	} 
}

string::string(const char *right)
{
	len = new int(strlen(right));
	data = new char[*len];
	cap = new int(*len);
	strncpy(data, right, *len);
}

string::~string()
{
	delete len;
	delete cap;
	delete[] data;
}

string & string::operator = (const string &right)
{
	if (this != &right)
	{
		resize(right.length());
		reserve(right.capacity());
		for (auto index = 0; index < *len; index++)
		{
			data[index] = right[index];
		}
	}
	return *this;
}

string & string::operator = (string &&right)
{
	if (this != &right)
	{
		resize(right.length());
		reserve(right.capacity());
		for (auto index = 0; index < right.length(); index++)
		{
			data[index] = right[index];
		}
		right.set_length(0);
		right.set_capacity(0);
	}
	return *this;
}

string & string::operator = (const char *right)
{
	resize(strlen(right));
	reserve(*len);
	strncpy(data, right, *len);
	return *this;
}

char & string::operator[] (int position)
{
	if(position < 0) { return data[0]; }
	if (position >= *len) { return data[*len - 1]; }
	return data[position];
}

const char & string::operator[] (int position) const
{
	if(position < 0) { return data[0]; }
	if (position >= *len) { return data[*len - 1]; }
	return data[position];
}

int string::size() const
{
	return *len;
}

int string::length() const
{
	return *len;
}

int string::capacity() const
{
	return *cap;
}

const char * string::get_data() const
{
	return data;
}

int string::set_length(int new_len)
{
	resize(new_len);
	return *len;
}

int string::set_capacity(int new_cap)
{
	reserve(new_cap);
	return *cap;
}

void string::clear()
{
	resize(0);
	reserve(0);
}

void string::resize(int newlen)
{
	char * newdata = new char[newlen];
	if (newlen < *len)
	{
		strncpy(newdata, data, newlen);
		
		delete[] data;
		data = new char[newlen];
		
		strncpy(data, newdata, newlen);
	}
	else if (newlen > *len)
	{
		strncpy(newdata, data, *len);
		
		for (auto index = *len; index < newlen; index++) { newdata[index] = '\0'; }
		
		delete[] data;
		data = new char[newlen];
		
		strncpy(data, newdata, newlen);
	}
	delete len;
	len = new int(newlen);
	delete[] newdata;
}

void string::reserve(int newcap)
{
	delete cap;
	cap = new int(newcap);
}

const char * string::c_str()
{
	char * cstr = new char[*len];
	strncpy(cstr, data, *len);
	
	return cstr;
}

string string::substr(int position, int length)
{
	string new_string;
	int new_len;
	if ((position + length) >= *len) { new_len = *len; }
	else { new_len = position + length; }
	
	for (auto index = position; index < new_len; index++)
	{			
		new_string[index - position] = data[index];
	}
	return new_string;
}

string string::append(string &right)
{
	int rlen = right.length();
	int oldlen = *len;
	int rindex = 0;
	
	resize(oldlen + rlen);
	reserve(*len);
	for (auto index = oldlen; index < *cap; index++)
	{
		data[index] = right[rindex++];
	}
	return *this;
}

string string::insert(string &right, int position)
{
	int rlen = right.length();
	int rindex = 0;
	resize(*len + rlen);
	reserve(*len);
	
	for (auto index = *len; index > position; index--)	//make space
	{
		data[index] = data[index - rlen];
	}
	for (auto index = position; index < position + rlen; index++)	//insert string
	{
		data[index] = right[rindex++];
	}
	return *this;
}

bool operator == (const string &left, const string &right)
{
	if (left.length() == right.length())
	{
		if (strncmp(left.get_data(), right.get_data(), left.length()) == 0) { return true; }
	}
	return false;
}

bool operator != (const string &left, const string &right)
{
	if (left == right) { return false; }
	return true;
}

bool operator >= (const string &left, const string &right)
{
	if (left == right || left > right)
	{
		return true;
	}
	return false;
}

bool operator <= (const string &left, const string &right)
{
	if (left == right || right > left)
	{
		return true;
	}
	return false;
}

bool operator > (const string &left, const string &right)
{
	int len = 0;
	if (left.length() >= right.length()) { len = right.length(); }
	else { len = left.length(); }

	if (strncmp(left.get_data(), right.get_data(), len) > 0) { return true; }
	return false;
}

bool operator < (const string &left, const string &right)
{
	if (right > left)
	{
		return true;
	}
	return false;
}

std::ostream & operator << (std::ostream & out, const string &right)
{
	int size = right.length();
	for (auto index = 0; index < size; index++)
	{
		out << right.data[index];
	}
	return out;
}

std::istream & operator >> (std::istream & in, string &right)
{
	char input;
	while (in.peek() != EOF && in.good() == true && in.peek() != ' ' && in.peek() != '\n')
	{
		in.get(input);
		int size = right.length();
		right.reserve(size + 1);
		if (in.good() == true && size < right.capacity())
		{
			right.resize(size + 1);
			right.data[size] = input;
		}
	}
	return in;
}

