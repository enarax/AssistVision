#include "vision.h"
#include "network.h"
#include "message_targethot.h"

#include <cstring>
#include <stdio.h>
#include <string>
#include <exception>


bool r1, r2, r3;
const char* robotaddr = "10.28.23.1";
const unsigned short robotport = 12869;
const unsigned short listenport = 12868;

int main(void)
{
	networkrobot robot(robotaddr, robotport, listenport);
	
	//sample sending code
	message_targethot msg(1);
	robot.sendmessage(&msg);
	
	//sample receiving code
	while(1)
	{
		networkmessage* msg = robot.receivemessage(true);
		
		if(msg->getGuid() == MSGID_TARGETHOT)
		{
			message_targethot* targetmsg = (message_targethot*)msg;
			if(targetmsg->isHot())
				printf("hot\n");
			else
				printf("nothot\n");
		}
		else
			throw std::exception();
			
		deletemessage(&msg);
	}
	
	
		
}
