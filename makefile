all:
	g++ -o gesture main.cpp frame.cpp `pkg-config --cflags --libs opencv` -std=c++11

