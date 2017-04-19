all:
	# g++ -o gesture main.cpp  `pkg-config --cflags --libs opencv` -std=c++11
	g++ -o gesture handDetection.cpp  `pkg-config --cflags --libs opencv` -std=c++11

