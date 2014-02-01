#ifndef _MESSAGE_REQUESTSTATUS_H
#define _MESSAGE_REQUESTSTATUS_H

#include "networkmessage.h"
#include "networkbuffer.h"


#define MSGID_REQUESTSTATUS 12011

class message_requeststatus : public networkmessage
{
	
public:
	message_requeststatus();

	virtual GUID getGuid() const;
	
	virtual void serialize(networkbuffer_in&) const;
	
	virtual void deserialize(networkbuffer_out);

};



#endif
