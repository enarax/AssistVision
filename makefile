ARCH = $(shell uname -m)

all: AssistVision-$(ARCH) run

AssistVision-$(ARCH): main.cpp makefile vision.h vision.cpp
	g++ -g -Wall   -o $@ `pkg-config --cflags --libs opencv` *.cpp

run: 
	./AssistVision-$(ARCH)

clean:
	rm -f AssistVision-$(ARCH)
	
rebuild: clean all
