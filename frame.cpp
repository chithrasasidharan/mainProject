#include "frame.hpp"
#include "main.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/highgui/highgui_c.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Frame::Frame(){
    cap=VideoCapture(0);
}
Frame::Frame(Mat s){
    src = s;
    cap=VideoCapture(0);
}

void Frame::normalizeColors(){
    // TODO to get from trackbar

    // normalize all boundaries so that 
	// threshold is whithin 0-255
	for(int i=0;i<nSamples;i++){
		if((average[i][0]-lower) <0){
			lower = average[i][0] ;
		}if((average[i][1]-lower) <0){
			lower = average[i][1] ;
		}if((average[i][2]-lower) <0){
			lower = average[i][2] ;
		}if((average[i][0]+upper[i][0]) >255){ 
			upper[i][0] = 255-average[i][0] ;
		}if((average[i][1]+upper[i][1]) >255){
			upper[i][1] = 255-average[i][1] ;
		}if((average[i][2]+upper[i][2]) >255){
			upper[i][2] = 255-average[i][2] ;
		}
	}
}

void Frame::makeThreshold(){
	Scalar lowerBound;
	Scalar upperBound;
    vector<Mat> bwList;
	for(int i=0;i<nSamples;i++){
		normalizeColors();
		lowerBound=Scalar(average[i][0] - lower[i][0] , average[i][1] - lower[i][1], average[i][2] - lower[i][2] );
		upperBound=Scalar(average[i][0] + upper[i][0] , average[i][1] + upper[i][1], average[i][2] + upper[i][2] );
        bwList.push_back(Mat(transient.rows,transient.cols,CV_8U));			
		inRange(transient,lowerBound,upperBound,bwList[i]);	
        if(i==0){
            bwList[i].copyTo(threshold);
        }
        else{
            threshold|=bwList[i];
        }
	}
    thresholdExists=true;
	medianBlur(threshold, threshold,blurRadius); 
    imshow("threshs", threshold);
}

void Frame::read(){
    cap>>src;
    flip(src,src,1);
    // Scale down
    pyrDown(src,transient);
    pyrDown(transient,transient);
    blur(transient,transient, Size(3,3));
    // change color
    cvtColor(transient, transient, originalToColor);
		
}
void Frame::show(){
    int x = src.cols - transient.cols;
    int y = 0;
    transient.copyTo(src(Rect(x,y,transient.cols, transient.rows)));
    
    if(thresholdExists)
    {
        // int x = src.cols - threshold.cols;
        // int y = transient.rows;
        // threshold.copyTo(src(Rect(x,y,threshold.cols, threshold.rows)));
        imshow("thresh", threshold);
    }


    imshow(windowName, src);
    if(waitKey(30)>=0)
        exit(0);
}