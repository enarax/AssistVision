#ifndef _NETWORKMESSAGE_H
#define _NETWORKMESSAGE_H

#include <vector>
#include <map>
#include <stdio.h>
#include "networkexception.h"
#include "guid.h"


#if 0
#define MESSAGE_DEFAULT_FACTORY(classname) networkmessage* _classname__defaultfactory(unsigned char* d, int l) \
{ \
	classname* ret = new classname();\
	ret->deserialize(d, l);\
	return ret;\
}
#endif

#define REGISTER_MESSAGE_DEFAULT(id, classname) namespace{\
	networkmessage* _classname__defaultfactory(unsigned char* d, int l) \
	{ \
		classname* ret = new classname();\
		ret->deserialize(d, l);\
		return ret;\
	}\
    networkmessage::Registrar _registrar__id(id, &_classname__defaultfactory);\
}

#if 0
#define REGISTER_MESSAGE_CUSTOM(id, factory) namespace{\
 networkmessage::Registrar _registrar__id(id, factory);\
}
#endif

class networkmessage;

typedef networkmessage* (*messagecreator)(unsigned char*, int);


class networkmessage
{
private:
	static std::map<GUID, messagecreator>& getFactoryTable();

protected:
	networkmessage();
	
public:
	static bool ismessageregistered(GUID);
	static void registermessage(GUID, messagecreator);
	static void unregistermessage(GUID);
	
	struct Registrar
	{
		explicit Registrar(GUID id, messagecreator fac)
		{
			networkmessage::registermessage(id, fac);
		}
	private:
		Registrar(const Registrar&){}
		Registrar& operator=(const Registrar&){return *this;}
	};
	
	static networkmessage* createmessage(GUID guid, unsigned char* data, int datalen);


	virtual GUID getGuid() const = 0;
	
	virtual std::vector<unsigned char> serialize() const = 0;
	
	virtual void deserialize(const unsigned char* data, int len) = 0;
	
	virtual ~networkmessage();
};


inline void deletemessage(networkmessage** messageptr)
{
	delete *messageptr;
	*messageptr = 0;
};


#endif
