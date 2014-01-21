#ifndef _NETWORKMESSAGE_H
#define _NETWORKMESSAGE_H

#include <vector>
#include "networkexception.h"
#include "guid.h"


class networkmessage
{
private:
	bool _loaded;

protected:
	networkmessage();

	virtual void int_deserialize(const unsigned char* data, int len) = 0;
	
public:

	virtual GUID getGuid() const = 0;
	
	bool isLoaded() const;
	
	virtual std::vector<unsigned char> serialize() const = 0;
	
	void deserialize(const unsigned char* data, int len);
	
	virtual ~networkmessage();
	
};


networkmessage* createmessage(GUID id);

inline void deletemessage(networkmessage** messageptr)
{
	delete *messageptr;
	*messageptr = 0;
};


#endif
