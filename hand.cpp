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

float Hand::distanceP2P(Point a, Point b){
	float d= sqrt(fabs( pow(a.x-b.x,2) + pow(a.y-b.y,2) )) ;  
	return d;
}

float Hand::getAngle(Point s, Point f, Point e){
	float l1 = distanceP2P(f,s);
	float l2 = distanceP2P(f,e);
	float dot=(s.x-f.x)*(e.x-f.x) + (s.y-f.y)*(e.y-f.y);
	float angle = acos(dot/(l1*l2));
	angle=angle*180/PI;
	return angle;
}

void Hand::eliminateDefects()
{
	int tolerance =  boundingRectangle.height/5;
	float angleTol=95;
	vector<Vec4i> newDefects;
	int startidx, endidx, faridx;
	vector<Vec4i>::iterator d=defects[bigIndex].begin();
	for(auto iterator=defects[bigIndex].begin(); d!=defects[bigIndex].end(); d++ ) {
   	    Vec4i& v=(*d);
	    startidx=v[0]; Point ptStart(contours[bigIndex][startidx] );
   		endidx=v[1]; Point ptEnd(contours[bigIndex][endidx] );
  	    faridx=v[2]; Point ptFar(contours[bigIndex][faridx] );
		if(distanceP2P(ptStart, ptFar) > tolerance && distanceP2P(ptEnd, ptFar) > tolerance && getAngle(ptStart, ptFar, ptEnd  ) < angleTol ){
			if( ptEnd.y > (boundingRectangle.y + boundingRectangle.height -boundingRectangle.height/4 ) ){
			}else if( ptStart.y > (boundingRectangle.y + boundingRectangle.height -boundingRectangle.height/4 ) ){
			}else {
				newDefects.push_back(v);		
			}
		}	
	}
	defects[bigIndex].swap(newDefects);
	// removeRedundantEndPoints(defects[bigIndex], m);
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
			eliminateDefects();
			drawContours(f.src, hullP, bigIndex, Scalar(200,0,0), 2, 8, vector<Vec4i>(), 0, Point());
		}		
	}
}