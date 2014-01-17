#include "vision.h"
#include "network.h"

#include <cstring>
#include <stdio.h>


bool r1, r2, r3;
const char* robotaddr = "10.28.23.2";
const unsigned short robotport = 12869;
const unsigned short listenport = 12868;

int main(void)
{
	networkrobot robot(robotaddr, robotport, listenport);
	while(1)
		robot.send(robot.receive(true));
}
