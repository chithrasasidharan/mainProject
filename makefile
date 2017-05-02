all:
	g++ -o gesture main.cpp  `pkg-config --cflags --libs opencv`
command:
	g++ -ggdb `pkg-config --cflags opencv libvlc` command.cpp -o run `pkg-config --libs opencv libvlc`;
