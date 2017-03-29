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
#define minSizeForHand 20
int blurRadius=7;


using namespace cv;
using namespace std;
Ptr<BackgroundSubtractor>pMOG2;
vector<Point> pointList;
// Scalar runningAvg = Scalar(0,0,0);
std::vector<Scalar> runningAvg;

int hlsFirst, hlsSecond,hlsThird;
int iSliderValue1 = 70;
int iSliderValue2 = 50;
int iSliderValue3 = 50;
int iSliderValue4 = 7;
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
void addPoints(Mat frame){
    // to quickly move whole figure
    int xOffset = frame.cols/4;
    int yOffset = 0;
    // points vaguely in the shape of a hand
    pointList.push_back(Point(frame.cols/3 + xOffset, frame.rows/6 + yOffset));
    pointList.push_back(Point(frame.cols/3.5 + xOffset, frame.rows/6 + yOffset));
    pointList.push_back(Point(frame.cols/2.5 + xOffset, frame.rows/6 + yOffset));
    pointList.push_back(Point(frame.cols/4 + xOffset, frame.rows/2 + yOffset));
    pointList.push_back(Point(frame.cols/3 + xOffset, frame.rows/1.5 + yOffset));
    // pointList.push_back(Point(frame.cols/2 + xOffset, frame.rows/2 + yOffset));
    pointList.push_back(Point(frame.cols/2.5 + xOffset, frame.rows/2.5 + yOffset));
    // pointList.push_back(Point(frame.cols/2 + xOffset, frame.rows/1.5 + yOffset));
    pointList.push_back(Point(frame.cols/2.5 + xOffset, frame.rows/1.8 + yOffset));
}

vector<Scalar> getAvgColor(Mat img){
    Scalar colour;
    vector<Scalar>avgColour;
    int n=0;
    for(auto iter=pointList.begin(); iter!=pointList.end(); iter++){
        Rect r(iter->x-radius, iter->y-radius, 2*radius, 2*radius);
        colour = mean(img(r));
        avgColour.push_back(colour);
    }
    return avgColour;
}

bool isHand(std::vector<Point> contour)
{
  bool isHand=true;
  Rect boundingRectangle = boundingRect(contour);
  int h = boundingRectangle.height;
  int w = boundingRectangle.width;
  if(h==0 || w==0)
    isHand=false;
  else if(w/h>4 || h/w>4)
    isHand=false;
  else if(h<minSizeForHand || w<minSizeForHand)
    isHand=false;
  return isHand;
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
  if(iSliderValue4%2!=0)
    blurRadius = iSliderValue4;
  else
  	blurRadius = iSliderValue4+1;

}

Mat filterColor(Mat frame, vector<Scalar> hlsavgs){
  Mat threshold;
  bool first = true;
  for(int i=0; i<hlsavgs.size();++i)
  {
    Mat tempThreshold;
    Scalar hlsavg = hlsavgs[i];
  	Scalar bound = Scalar(hlsFirst,hlsSecond,hlsThird);
    Scalar hlsLow = normalise(hlsavg-bound);
  	Scalar hlsHigh= normalise(hlsavg+bound);
  	inRange(frame,hlsLow,hlsHigh,tempThreshold);
    if(first){
      threshold=tempThreshold;
      first=false;
    }
    else
      threshold|=tempThreshold;

  }
	// bitwise_not(threshold, threshold);
	medianBlur(threshold, threshold, blurRadius);
	// Mat element = getStructuringElement(MORPH_ELLIPSE,Size(2*5+1, 2*5+1),Point(5, 5));
  // dilate(threshold,threshold, element);
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
        pyrDown(frame,frame);
        // pyrDown(frame,frame);
        flip(frame,frame,1);
        addPoints(frame);

        cvtColor(frame, frame, CV_BGR2HSV);

        if(loopCtr<=loopCountSec){
            for(int i=0; i<pointList.size(); i++)
                circle(frame,pointList[i],radius,Scalar(255,0,0),-1,8);
        }

        if(loopCtr > loopCountSec && loopCtr <= loopCountSec + avgLoopCount){
            // cout<<getAvgColor(frame)<<endl;
           Scalar avg;
           runningAvg = getAvgColor(frame);
           for(int i=0; i<pointList.size(); i++)
                circle(frame,pointList[i],radius,Scalar(255,255,255),-1,8);

            
        }

        if(loopCtr>loopCountSec + avgLoopCount){
     		createTrackbar("Hue", "filter", &iSliderValue1, 180,on_trackbar);
     		on_trackbar(hlsFirst,0);
     		createTrackbar("Lightness", "filter", &iSliderValue2, 100,on_trackbar);
     		on_trackbar(hlsSecond,0);
     		createTrackbar("Saturation", "filter", &iSliderValue3, 100,on_trackbar);
     		on_trackbar(hlsThird,0);
    	  createTrackbar("Blur", "filter", &iSliderValue4, 100,on_trackbar);
        on_trackbar(blurRadius,0);
        
        	Mat th = filterColor(frame,runningAvg);
        	imshow("filter",th);
        	waitKey(30);
        
      		// Contour detection
      		vector<vector<Point> > contours;
	    	vector<Vec4i> hierarchy;
	     	findContours(th, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	      	size_t bestContour = 0;
	      	for (size_t i = 1; i < contours.size(); i++)
	      	{
            if(isHand(contours[i]))
            {
              bestContour = i;
              break;
            }
	          // if (contourArea(contours[i]) > contourArea(contours[bestContour]))
	          //     bestContour = i;
	      	}
	      	drawContours(frame, contours, bestContour, Scalar(0, 0, 255), 1);
	       	if (!contours.empty())
      		{
	          vector<vector<Point> > hull(1);
	          convexHull(Mat(contours[bestContour]), hull[0], false);
	          drawContours(frame, hull, 0, Scalar(0, 255, 0), 3);
	          if (hull[0].size() > 2)
	          	{
	              vector<int> hullIndexes;
	              convexHull(Mat(contours[bestContour]), hullIndexes, true);
	              vector<Vec4i> convexityDefect;
	              convexityDefects(Mat(contours[bestContour]), hullIndexes, convexityDefect);
	              for (size_t i = 0; i < convexityDefect.size(); i++)
	              	{
	                  Point p1 = contours[bestContour][convexityDefect[i][0]];
	                  Point p2 = contours[bestContour][convexityDefect[i][1]];
	                  Point p3 = contours[bestContour][convexityDefect[i][2]];
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
