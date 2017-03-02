#include <vector>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include "opencv2/video/background_segm.hpp"

#define loopCountSec 40
#define avgLoopCount 50	
#define radius 100/32

using namespace cv;
using namespace std;
Ptr<BackgroundSubtractor>pMOG2;
cv::vector<cv::Point> pointList;


// void MyFilledCircle( Mat img, Point center )
// {
//  int thickness = -1;
//  int lineType = 8;

//  circle( img,
//          center,
//          radius,
//          Scalar( 255, 0, 0 ),
//          thickness,
//          lineType );
// }
void addPoints(){
	pointList.push_back(Point(200,200));
	pointList.push_back(Point(210,350));
	pointList.push_back(Point(240,160));
	pointList.push_back(Point(290,135));
	pointList.push_back(Point(340,175));
	pointList.push_back(Point(240,370));
	pointList.push_back(Point(280,385));
	pointList.push_back(Point(320,365));
	pointList.push_back(Point(200,275));
	pointList.push_back(Point(350,275));
}

void getAvgColor(Mat img){
    Point pts[1][10];
    pts[0][0] = Point(200,200);
	pts[0][1] = Point(210,350);
	pts[0][2] = Point(240,160);
	pts[0][3] = Point(290,135);
	pts[0][4] = Point(340,175);
	pts[0][5] = Point(240,370);
	pts[0][6] = Point(280,385);
	pts[0][7] = Point(320,365);
	pts[0][8] = Point(200,275);
	pts[0][9] = Point(350,275);
    const Point* points[1] = {pts[0]};
    int npoints = 10;

    // Create the mask with the polygon
    Mat mask(img.rows, img.cols, uchar(0));
    fillPoly(mask, points, &npoints, 1, Scalar(255));

    // Compute the mean with the computed mask
    Scalar average = mean(img, mask);

    std::cout << average << std::endl;
}
int main(){
	VideoCapture cap(0);
	int loopCtr=0;
	pMOG2 = new BackgroundSubtractorMOG2();
	if(!cap.isOpened())
		return -1;
	while(1){
		loopCtr++;
		Mat frame;
		cap>>frame;
		addPoints();

		cvtColor(frame, frame, CV_BGR2HSV);

		if(loopCtr<=loopCountSec){
			for(int i=0; i<pointList.size(); i++)
				circle(frame,pointList[i],radius,Scalar(255,0,0),-1,8);
		}
		if(loopCtr > loopCountSec && loopCtr <= loopCountSec + avgLoopCount){
			for(int i=0; i<pointList.size(); i++)
				circle(frame,pointList[i],radius,Scalar(255,255,255),-1,8);
		}
		getAvgColor(frame);
		imshow("image",frame);
		if(waitKey(30)>=0)
			break;
	}
}
