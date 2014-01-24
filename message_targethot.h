#ifndef _MESSAGE_TARGETHOT_H
#define _MESSAGE_TARGETHOT_H

#include "networkmessage.h"
#include "networkbuffer.h"


#define MSGID_TARGETHOT 12001

class message_targethot : public networkmessage
{

protected:
	bool _ishot;
	
public:
	message_targethot();
	message_targethot(bool ishot);
	
	bool isHot() const;
	
	void setHot(bool);

	virtual GUID getGuid() const;
	
	virtual void serialize(networkbuffer_in&) const;
	
	virtual void deserialize(const unsigned char* data, int len);

};



#endif
