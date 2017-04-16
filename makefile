all:
        g++ -o gesture main.cpp  `pkg-config --cflags --libs opencv`

