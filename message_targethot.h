#ifndef _MESSAGE_TARGETHOT_H
#define _MESSAGE_TARGETHOT_H

#include "networkmessage.h"


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
	
	virtual std::vector<unsigned char> serialize() const;
	
	virtual void deserialize(const unsigned char* data, int len);

};



#endif
