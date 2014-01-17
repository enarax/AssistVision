#ifndef _NETWORKEXCEPTION_H
#define _NETWORKEXCEPTION_H

#include <exception>
#include <string>
#include <sstream>


using namespace std;

class bufferexception : public exception
{
public:
	bufferexception(int max, int actual)
	{
		maxsize = max;
		actualsize = actual;
	}

	int maxsize;
	int actualsize;
	virtual const char* what() const throw()
	{
		std::ostringstream s;
		s << "Buffer size exceeded, max size: " << maxsize << ", actual size: " + actualsize;
		return s.str().c_str();
	}
};

class socketexception : public exception
{
	virtual const char* what() const throw()
	{
		return "Socket creation failed";
	}
};

class bindingexception : public exception
{
	virtual const char* what() const throw()
	{
		return "Binding failed";
	}
};

class notconnectedexception : public exception
{
	virtual const char* what() const throw()
	{
		return "Not connected";
	}
};

#endif
