all:
	g++ -o gesture main.cpp frame.cpp region.cpp gesture.cpp hand.cpp command.cpp `pkg-config --cflags  libvlc --libs opencv  libvlc` -std=c++11
command:
	g++ -ggdb `pkg-config --cflags opencv libvlc` command.cpp -o run `pkg-config --libs opencv libvlc`;
