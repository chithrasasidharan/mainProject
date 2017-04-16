#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "point.hpp"
#include "math.h"
// #define dist 30
#define minSizeForHand 20

using namespace std;
using namespace cv;

class Hand{
public:
	Points centroid;
	vector<Points> fingers;
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
	void contourDetection(Mat threshold,Mat frame){
		vector<vector<Point> > contours;
	    	vector<Vec4i> hierarchy;
	     	findContours(threshold, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	      	size_t bestContour = 0;
	      	for (size_t i = 1; i < contours.size(); i++)
	      	{
	           if(isHand(contours[i]))
           {
             bestContour = i;
             break;
           }
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
	int noOfFingers;
	int dist(Hand a){
		Points p;
		p.x = this->centroid.x-a.centroid.x;
		p.y=this->centroid.y-a.centroid.y;
		return max(p.x,p.y);
		// return Points(this->(centroid.x)-a.centroid.x,this->centroid.y-a.centroid.y);
	}
	bool isMoved(Hand a){
		if(dist(a))
			return true;
		return false;

	}
};

