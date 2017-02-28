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


void MyFilledCircle( Mat img, Point center )
{
 int thickness = -1;
 int lineType = 8;

 circle( img,
         center,
         radius,
         Scalar( 0, 0, 255 ),
         thickness,
         lineType );
}
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
		for(int i=0; i<pointList.size(); i++)
			MyFilledCircle(frame,pointList[i]);
		imshow("image",frame);
		if(waitKey(30)>=0)
			break;
	}
}
