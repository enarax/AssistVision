#include "message_targethot.h"

REGISTER_MESSAGE_DEFAULT(MSGID_TARGETHOT, message_targethot);


message_targethot::message_targethot()
	:_ishot(false)
{
}

message_targethot::message_targethot(bool ishot)
	:_ishot(ishot)
{
}


bool message_targethot::isHot() const
{
	return _ishot;
}

void message_targethot::setHot(bool val)
{
	_ishot = val;
}

GUID message_targethot::getGuid() const
{
	return MSGID_TARGETHOT;
}


void message_targethot::serialize(networkbuffer_in& data) const
{
	data << _ishot;
}

void message_targethot::deserialize(const unsigned char* data, int len)
{
	if(len != 1)
		throw deserializationexception();
		
	//if not zero, then it's hot
	_ishot = (data[0] != 0);
}

