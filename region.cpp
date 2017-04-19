#include "region.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

Region::Region(){
    tl=Point(0,0);
    br=Point(0,0);
}

Region::Region(Point tlc, Point brc, Mat src){
    tl=tlc;
    br=brc;
    borderThickness=2;
    borderColor=Scalar(0,255,0);
    region=src(Rect(tl.x, tl.y, br.x-tl.x, br.y-tl.y));
}

void Region::draw(Mat src){
    rectangle(src, tl, br, borderColor, borderThickness);
}