#include "networkmessage.h"

#include "message_targethot.h"




networkmessage* createmessage(GUID id)
{

	
	REGISTERCLASS(MSGID_TARGETHOT, message_targethot)


	
	throw guidunregisteredexception(id);
};





networkmessage::networkmessage()
	:_loaded(false)
{
}

networkmessage::~networkmessage()
{
}

bool networkmessage::isLoaded() const
{
	return _loaded;
}

void networkmessage::deserialize(const unsigned char* data, int len)
{
	int_deserialize(data, len);
	_loaded = true;
}
