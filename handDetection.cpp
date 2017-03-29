#include <vector>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include "opencv2/video/background_segm.hpp"

using namespace std;
using namespace cv;

int main(int argc, char *argv[]){
	int minH = 0, maxH = 60, minS = 40, maxS = 120, minV = 45, maxV = 135;
	// int minH = 130, maxH = 160, minS = 10, maxS = 40, minV = 75, maxV = 130;
  	namedWindow("Fingertip Detection");
  	createTrackbar("MinH", "Fingertip Detection", &minH, 180);
  	createTrackbar("MaxH", "Fingertip Detection", &maxH, 180);
  	createTrackbar("MinS", "Fingertip Detection", &minS, 255);
  	createTrackbar("MaxS", "Fingertip Detection", &maxS, 255);
 	createTrackbar("MinV", "Fingertip Detection", &minV, 255);
  	createTrackbar("MaxV", "Fingertip Detection", &maxV, 255);

	while(1){
		Mat frame;
		VideoCapture cap(0);
		cap>>frame;
		// frame = imread(argv[1],CV_LOAD_IMAGE_COLOR);
		Mat hsv;
		cvtColor(frame,hsv,CV_BGR2HSV);
		inRange(hsv, Scalar(minH,minS,minV),Scalar(maxH,maxS,maxV),hsv);
		int blurSize = 5;
      	int elementSize = 5;
      	medianBlur(hsv, hsv, blurSize);
      	Mat element = getStructuringElement(MORPH_ELLIPSE,Size(2*elementSize+1, 2*elementSize+1),Point(elementSize, elementSize));
      	dilate(hsv, hsv, element);
      	// Contour detection
      	vector<vector<Point> > contours;
	     vector<Vec4i> hierarchy;
	      findContours(hsv, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	      size_t largestContour = 0;
	      for (size_t i = 1; i < contours.size(); i++)
	      {
	          if (contourArea(contours[i]) > contourArea(contours[largestContour]))
	              largestContour = i;
	      }
	      drawContours(frame, contours, largestContour, Scalar(0, 0, 255), 1);
	       if (!contours.empty())
      {
          std::vector<std::vector<cv::Point> > hull(1);
          cv::convexHull(cv::Mat(contours[largestContour]), hull[0], false);
          cv::drawContours(frame, hull, 0, cv::Scalar(0, 255, 0), 3);
          if (hull[0].size() > 2)
          {
              std::vector<int> hullIndexes;
              cv::convexHull(cv::Mat(contours[largestContour]), hullIndexes, true);
              std::vector<cv::Vec4i> convexityDefects;
              cv::convexityDefects(cv::Mat(contours[largestContour]), hullIndexes, convexityDefects);
              for (size_t i = 0; i < convexityDefects.size(); i++)
              {
                  cv::Point p1 = contours[largestContour][convexityDefects[i][0]];
                  cv::Point p2 = contours[largestContour][convexityDefects[i][1]];
                  cv::Point p3 = contours[largestContour][convexityDefects[i][2]];
                  cv::line(frame, p1, p3, cv::Scalar(255, 0, 0), 2);
                  cv::line(frame, p3, p2, cv::Scalar(255, 0, 0), 2);
              }
          }
      }

		imshow("Fingertip Detection",frame);
	if(waitKey(30)>=0)
			break;
	}
    return 0;	
}
