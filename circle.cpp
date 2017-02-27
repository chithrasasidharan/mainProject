#include <vector>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include "opencv2/video/background_segm.hpp"

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
         100/32.0,
         Scalar( 0, 0, 255 ),
         thickness,
         lineType );
}
void addPoints(){
	Point pt1=Point(200,200);
	Point pt2=Point(210,350);
	Point pt3=Point(240,160);
	Point pt4=Point(290,135);
	Point pt5=Point(340,175);
	Point pt6=Point(240,370);
	Point pt7=Point(280,385);
	Point pt8=Point(320,365);
	Point pt9=Point(200,275);
	Point pt10=Point(350,275);
	pointList.push_back(pt1);
	pointList.push_back(pt2);
	pointList.push_back(pt3);
	pointList.push_back(pt4);
	pointList.push_back(pt5);
	pointList.push_back(pt6);
	pointList.push_back(pt7);
	pointList.push_back(pt8);
	pointList.push_back(pt9);
	pointList.push_back(pt10);

}

int main(){
	VideoCapture cap(0);
	pMOG2 = new BackgroundSubtractorMOG2();
	if(!cap.isOpened())
		return -1;
	while(1){
		
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
