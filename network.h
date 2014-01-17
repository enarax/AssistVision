#ifndef _NETWORK_H
#define _NETWORK_H

#include <cstddef>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

using namespace std;

#define BUFLEN 256

class networkrobot
{

protected:
	bool _connected;

	static char _buf[BUFLEN];
	
	int _outsocket;
	int _insocket;
	struct sockaddr_in _outaddr;
	struct sockaddr_in _inaddr;

	const char* _robotaddr;
	const unsigned short _robotport;
	const unsigned short _listenport;
	
public:
	networkrobot(const char* robotaddr, unsigned short robotport, unsigned short listenport);
	
	void connect();
	
	int send(const string& message);
	string receive(bool block);
};




#endif
