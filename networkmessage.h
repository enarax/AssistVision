#ifndef _NETWORKMESSAGE_H
#define _NETWORKMESSAGE_H

typedef unsigned short GUID;


class networkmessage
{
	
public:
	GUID getGuid() = 0;
	
	char* serialize() = 0;
	
	void deserialize() = 0;
	
}


#endif
