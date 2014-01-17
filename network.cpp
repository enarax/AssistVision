#include "network.h"
#include "networkexception.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <errno.h>

char networkrobot::_buf[BUFLEN];


networkrobot::networkrobot(const char* robotaddr, unsigned short robotport, unsigned short listenport)
	:_robotaddr(robotaddr), _robotport(robotport), _listenport(listenport), _connected(false)
{
	connect();
}


void networkrobot::connect()
{
	_outsocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(_outsocket == -1)
		throw socketexception();
	
	_outaddr.sin_family = AF_INET;
    _outaddr.sin_addr.s_addr = inet_addr(_robotaddr);
    _outaddr.sin_port  = htons(_robotport);
    
    
    _insocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(_insocket == -1)
		throw socketexception();
		
	memset((void*)&_inaddr, 0, sizeof(_inaddr));
    
    _inaddr.sin_family = AF_INET;
	_inaddr.sin_port = htons(_listenport);
	_inaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(_insocket, (struct sockaddr*)&_inaddr, sizeof(_inaddr)) == -1)
		throw bindingexception();
		
	_connected = true;
	
}


int networkrobot::send(const string& message)
{
	if(!_connected)
		throw notconnectedexception();

	if(message.length() >= BUFLEN)
		throw bufferexception(BUFLEN-1, message.length());
	//load into
	for(int i = 0; i < message.length(); i++)
	{
		_buf[i+1] = 0;
		_buf[i] = message.at(i);
	}
    int rc = sendto(_outsocket, (const void*)_buf, (size_t)message.length(), 0, (struct sockaddr *) &_outaddr, sizeof(_outaddr));
	if(rc == -1)
		return -1;
    
    return rc;
}


string networkrobot::receive(bool block)
{
	if(!_connected)
		throw notconnectedexception();

	int bytes = recv(_insocket, _buf, BUFLEN, block ? 0 : MSG_DONTWAIT);
	if(bytes == -1)
		return "";
		
	return _buf;
}


