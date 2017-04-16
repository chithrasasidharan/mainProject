#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Points{
public:
	int x,y;
	Points(){}
	Points(int x, int y){
		this->x = x;
		this->y = y;
	}
};

