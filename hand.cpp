#include "hand.hpp"
#include "main.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#define handContour contours[bigIndex]
using namespace cv;
using namespace std;

Hand::Hand(){
	frameNo=0;
	noOfFingers=0;
}

void Hand::setBiggestContour()
{
	bigIndex = -1;
    int sizeOfBiggestContour = 0;
    for (int i = 0; i < contours.size(); i++){
        if(contours[i].size() > sizeOfBiggestContour){
            sizeOfBiggestContour = contours[i].size();
            bigIndex = i;
        }
    }
}

void Hand::initVectors()
{
	hullI=vector<vector<int> >(contours.size());
	hullP=vector<vector<Point> >(contours.size());
	defects=vector<vector<Vec4i> > (contours.size());
}

void Hand::makeContours(Frame frame)
{
	f = frame;	
	findContours(f.contours, contours, CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
	initVectors();
	setBiggestContour();
	if(bigIndex!=-1)
	{
		boundingRectangle = boundingRect(Mat(handContour)); 
		convexHull(Mat(handContour),hullP[bigIndex],false,true);
		convexHull(Mat(handContour),hullI[bigIndex],false,false);
		approxPolyDP( Mat(hullP[bigIndex]), hullP[bigIndex], 18, true );
		if(handContour.size()>3 ){
			convexityDefects(handContour,hullI[bigIndex],defects[bigIndex]);
			// eleminateDefects(m);
			drawContours(f.src, hullP, bigIndex, Scalar(200,0,0), 2, 8, vector<Vec4i>(), 0, Point());
		}		
	}
}