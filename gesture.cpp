#include "gesture.hpp"
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

Gesture::Gesture(){
	frameNo=0;
	noOfFingers=0;
}

void Gesture::setBiggestContour()
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

void Gesture::initVectors()
{
	hullI=vector<vector<int> >(contours.size());
	hullP=vector<vector<Point> >(contours.size());
	defects=vector<vector<Vec4i> > (contours.size());
}

float Gesture::distanceP2P(Point a, Point b){
	float d= sqrt(fabs( pow(a.x-b.x,2) + pow(a.y-b.y,2) )) ;  
	return d;
}

float Gesture::getAngle(Point s, Point f, Point e){
	float l1 = distanceP2P(f,s);
	float l2 = distanceP2P(f,e);
	float dot=(s.x-f.x)*(e.x-f.x) + (s.y-f.y)*(e.y-f.y);
	float angle = acos(dot/(l1*l2));
	angle=angle*180/PI;
	return angle;
}

void Gesture::removeRedundantEndPoints(vector<Vec4i> newDefects){
	Vec4i temp;
	float avgX, avgY;
	float tolerance=boundingRectangle.width/6;
	int startidx, endidx, faridx;
	int startidx2, endidx2;
	for(int i=0;i<newDefects.size();i++){
		for(int j=i;j<newDefects.size();j++){
	    	startidx=newDefects[i][0]; Point ptStart(contours[bigIndex][startidx] );
	   		endidx=newDefects[i][1]; Point ptEnd(contours[bigIndex][endidx] );
	    	startidx2=newDefects[j][0]; Point ptStart2(contours[bigIndex][startidx2] );
	   		endidx2=newDefects[j][1]; Point ptEnd2(contours[bigIndex][endidx2] );
			if(distanceP2P(ptStart,ptEnd2) < tolerance ){
				contours[bigIndex][startidx]=ptEnd2;
				break;
			}if(distanceP2P(ptEnd,ptStart2) < tolerance ){
				contours[bigIndex][startidx2]=ptEnd;
			}
		}
	}
}

void Gesture::eliminateDefects()
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
	removeRedundantEndPoints(defects[bigIndex]);
}

// make contours with current frame
void Gesture::initFrame(Frame frame)
{
	f = frame;	
	findContours(f.contours, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
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

			checkHandExists();
			print();
			if(hasHand)
			{
				// TODO make hand object
			}
		}		
	}
}

// print info regarding hand
void Gesture::print()
{
	// TODO do print function
}

// check if hand exists, if so init hand with it
// if more than 5 fingers, or h or w is 0, or aspect ratio more than 4 or less than 20 pixels, then not hand
void Gesture::checkHandExists()
{
	hasHand=true;
	if(fingerTips.size() > 5 ){
		hasHand=false;
	}else if(boundingRectangle.height==0 || boundingRectangle.width == 0){
		hasHand=false;
	}else if(boundingRectangle.height/boundingRectangle.width > 4 || boundingRectangle.width/boundingRectangle.height >4){
		hasHand=false;	
	}else if(bRect.x<20){
		hasHand=false;	
	}	
}