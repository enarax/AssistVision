#include "message_requeststatus.h"

REGISTER_MESSAGE_DEFAULT(MSGID_REQUESTSTATUS, message_requeststatus);


message_requeststatus::message_requeststatus()
{
}


GUID message_requeststatus::getGuid() const
{
	return MSGID_REQUESTSTATUS;
}


void message_requeststatus::serialize(networkbuffer_in& data) const
{
	//dummy
}

void message_requeststatus::deserialize(networkbuffer_out data)
{
	//dummy
	
}

