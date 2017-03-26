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

#define blurRadius 21

using namespace cv;
using namespace std;
Ptr<BackgroundSubtractor>pMOG2;
vector<Point> pointList;
Scalar runningAvg = Scalar(0,0,0);

int hlsFirst, hlsSecond,hlsThird;
int iSliderValue1 = 70;
int iSliderValue2 = 50;
int iSliderValue3 = 50;
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
    pointList.push_back(Point(240,370));
    pointList.push_back(Point(290,135));
    pointList.push_back(Point(340,175));
    pointList.push_back(Point(280,385));
    pointList.push_back(Point(320,365));
        pointList.push_back(Point(200,275));
    pointList.push_back(Point(350,275));
}

Scalar getAvgColor(Mat img){
    Scalar colour, avgColour;
    int n=0;
    for(auto iter=pointList.begin(); iter!=pointList.end(); iter++){
        Rect r(iter->x-radius, iter->y-radius, 2*radius, 2*radius);
        colour = mean(img(r));
        avgColour = avgColour+colour;
        n++;
    }
    avgColour/=n;
    return avgColour;
}



Scalar normalise(Scalar color)
{
	Scalar newColor;
    if(color[0]<0)
    	newColor[0]=0;
    if(color[1]<0)
    	newColor[1]=0;
    if(color[2]<0)
    	newColor[2]=0;
    if(color[0]>180)
    	newColor[0]=180;
    if(color[1]>100)
    	newColor[1]=100;
    if(color[2]>100)
    	newColor[2]=100;
    return newColor;
}

static void on_trackbar(int, void*){
	hlsFirst = iSliderValue1;
	hlsSecond= iSliderValue2;
	hlsThird = iSliderValue3;
}

Mat filterColor(Mat frame, Scalar hlsavg){
	Mat threshold;
	Scalar bound = Scalar(hlsFirst,hlsSecond,hlsThird);
	Scalar hlsLow = normalise(hlsavg-bound);
	Scalar hlsHigh= normalise(hlsavg+bound);
	inRange(frame,hlsLow,hlsHigh,threshold);
	// bitwise_not(threshold, threshold);
	medianBlur(threshold, threshold, blurRadius);
	Mat element = getStructuringElement(MORPH_ELLIPSE,Size(2*5+1, 2*5+1),Point(5, 5));
     dilate(threshold,threshold, element);
	return threshold;
}


int main(){
    VideoCapture cap(0);
    int loopCtr=0;
  //  pMOG2 = new BackgroundSubtractorMOG2();
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
            // cout<<getAvgColor(frame)<<endl;
           Scalar avg;
           avg = getAvgColor(frame);
           int n = loopCtr - loopCountSec;
           runningAvg = (Scalar)((avg*(n-1)+getAvgColor(frame))/n);
           for(int i=0; i<pointList.size(); i++)
                circle(frame,pointList[i],radius,Scalar(255,255,255),-1,8);
            //chec
            cout<<runningAvg<<endl;

            
        }

        if(loopCtr>loopCountSec + avgLoopCount){
     		createTrackbar("Hue", "filter", &iSliderValue1, 180,on_trackbar);
     		on_trackbar(hlsFirst,0);
     		createTrackbar("Lightness", "filter", &iSliderValue2, 100,on_trackbar);
     		on_trackbar(hlsSecond,0);
     		createTrackbar("Saturation", "filter", &iSliderValue3, 100,on_trackbar);
     		on_trackbar(hlsThird,0);
    	 
        	Mat th = filterColor(frame,getAvgColor(frame));
        	imshow("filter",th);
        	waitKey(30);
        
      		// Contour detection
      		vector<vector<Point> > contours;
	    	vector<Vec4i> hierarchy;
	     	findContours(th, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	      	size_t largestContour = 0;
	      	for (size_t i = 1; i < contours.size(); i++)
	      	{
	          if (contourArea(contours[i]) > contourArea(contours[largestContour]))
	              largestContour = i;
	      	}
	      	drawContours(frame, contours, largestContour, Scalar(0, 0, 255), 1);
	       	if (!contours.empty())
      		{
	          vector<vector<Point> > hull(1);
	          convexHull(Mat(contours[largestContour]), hull[0], false);
	          drawContours(frame, hull, 0, Scalar(0, 255, 0), 3);
	          if (hull[0].size() > 2)
	          	{
	              vector<int> hullIndexes;
	              convexHull(Mat(contours[largestContour]), hullIndexes, true);
	              vector<Vec4i> convexityDefect;
	              convexityDefects(Mat(contours[largestContour]), hullIndexes, convexityDefect);
	              for (size_t i = 0; i < convexityDefect.size(); i++)
	              	{
	                  Point p1 = contours[largestContour][convexityDefect[i][0]];
	                  Point p2 = contours[largestContour][convexityDefect[i][1]];
	                  Point p3 = contours[largestContour][convexityDefect[i][2]];
	                  line(frame, p1, p3, Scalar(255, 0, 0), 2);
	                  line(frame, p3, p2, Scalar(255, 0, 0), 2);
	              	}
	          	}
      		}
      	}
        cvtColor(frame, frame, CV_HSV2BGR);

        imshow("image",frame);
        if(waitKey(30)>=0)
            break;
    }
    
}
