ARCH = $(shell uname -m)

all: AssistVision-$(ARCH) run

AssistVision-$(ARCH): main.cpp makefile vision.h vision.cpp message_targethot.h message_targethot.cpp message_requeststatus.h message_requeststatus.cpp
	g++ -Wall -I"../Robot-Networking/include" -L"../Robot-Networking/lib"  -o $@ `pkg-config --cflags --libs opencv` *.cpp -lrobotnetworking

run: 
	./AssistVision-$(ARCH)

clean:
	rm -f AssistVision-$(ARCH)
	
rebuild: clean all
