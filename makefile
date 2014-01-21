ARCH = $(shell uname -m)

all: AssistVision-$(ARCH) run

AssistVision-$(ARCH): main.cpp makefile vision.h vision.cpp network.h network.cpp networkexception.h networkmessage.h networkmessage.cpp message_targethot.h message_targethot.cpp
	g++ -Wall -o $@ `pkg-config --cflags --libs opencv` *.cpp

run: 
	./AssistVision-$(ARCH)

clean:
	rm -f AssistVision-$(ARCH)
