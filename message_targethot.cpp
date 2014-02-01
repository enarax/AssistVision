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

void message_targethot::deserialize(networkbuffer_out data)
{
	data >> _ishot;
	
}

