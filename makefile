all:
	g++ -o gesture main.cpp frame.cpp region.cpp gesture.cpp `pkg-config --cflags --libs opencv` -std=c++11

