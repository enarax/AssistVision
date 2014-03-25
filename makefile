ARCH = $(shell uname -m)

all: AssistVision-$(ARCH) run

AssistVision-$(ARCH): main.cpp makefile vision.h vision.cpp
	g++ -g -Wall   -o $@ `pkg-config --cflags --libs opencv` *.cpp
	cp AssistVision-$(ARCH) /home/pi/

run: 
	/home/pi/AssistVision-$(ARCH)

clean:
	rm -f AssistVision-$(ARCH)
	rm -f /home/pi/AssistVision-$(ARCH)
	
rebuild: clean all
