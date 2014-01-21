#include "network.h"
#include "networkexception.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <algorithm>
#include <errno.h>

unsigned char networkrobot::_buf[BUFLEN];


networkrobot::networkrobot(const char* robotaddr, unsigned short robotport, unsigned short listenport)
	:_connected(false), _outsocket(-1), _insocket(-1), _robotaddr(robotaddr), _robotport(robotport), _listenport(listenport)
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

void networkrobot::int_send(const unsigned char* message, int len)
{
	if(!_connected)
		throw notconnectedexception();

	if(len > MSGLEN)
		throw bufferexception(MSGLEN, len);
	unsigned char messagelength = (unsigned char)len;
	//load into
	_buf[0] = messagelength;
	for(int i = 0; i < messagelength; i++)
		_buf[i+1] = message[i];
	int rc = sendto(_outsocket, (const void*)_buf, messagelength+1, 0, (struct sockaddr *) &_outaddr, sizeof(_outaddr));
	if(rc == -1)
		throw sendexception();
}

void networkrobot::sendmessage(networkmessage const* msg)
{
	vector<unsigned char> messagedata = msg->serialize();
	if(messagedata.size() > MSGLEN-2)
		throw messagelengthexceededexception();
	GUID netid = ENCODEGUID(msg->getGuid());
	vector<unsigned char> data;
	data.push_back((netid >> 8) & 0xff);
	data.push_back(netid & 0xff);
	copy(messagedata.begin(), messagedata.end(), back_inserter(data));
	
	int_send(&data[0], data.size());
}


networkmessage* networkrobot::receivemessage(bool block)
{
	if(!_connected)
		throw notconnectedexception();

	int bytes = recv(_insocket, _buf, BUFLEN-1, block ? 0 : MSG_DONTWAIT);
	

	if(bytes == -1)
		return 0;
	
	int messagelength = _buf[0];
	int guid = DECODEGUID((short)(((unsigned char)_buf[1]) << 8 | ((unsigned char)_buf[2])));
	
	return networkmessage::createmessage(guid, _buf+3, messagelength-2);
}
	
	

	


