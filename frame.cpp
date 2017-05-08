#include "frame.hpp"
#include "main.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Frame::Frame(){
    cap=VideoCapture(0);
    lower = Scalar(13, 30, 80);
    upper = Scalar(7, 40, 80);
}
Frame::Frame(Mat s){
    src = s;
    cap=VideoCapture(0);
    lower = Scalar(13, 30, 80);
    upper = Scalar(7, 40, 80);
}

Scalar Frame::normalizeColors(int i, bool isLower){	
    Scalar color;
    if(isLower)
        color = Scalar(average[i][0],average[i][1],average[i][2]) - lower;
    else
        color = Scalar(average[i][0],average[i][1],average[i][2]) + upper;

    if(color[0]<0)
        color[0]=0;
    if(color[0]>255)
        color[0]=255;
    if(color[1]<0)
        color[1]=0;
    if(color[1]>255)
        color[1]=255;
    if(color[2]<0)
        color[2]=0;
    if(color[2]>255)
        color[2]=255;
    return color;
}

void Frame::makeThreshold(){
	Scalar lowerBound;
	Scalar upperBound;
    vector<Mat> bwList;
	for(int i=0;i<nSamples;i++){
        lowerBound = normalizeColors(i, true);
        upperBound = normalizeColors(i, false);
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
    threshold.copyTo(contours);
	medianBlur(threshold, threshold,blurRadius); 
    pyrUp(contours, contours);
    pyrUp(contours, contours);
}

void Frame::read(){
    // Some hocus pocus is done to shift the transient and bw screens to added black area to the right
   cap>>transient;
   flip(transient,transient,1);
   src = Mat::zeros(Size(transient.cols + transient.cols/4, transient.rows), transient.type());
   transient.copyTo(src(Rect(0,0,transient.cols, transient.rows)));
   // Scale down
   pyrDown(src(Rect(0,0,transient.cols, transient.rows)),transient);
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
        // The threshold matrix is somehow layered, or has channels. So all channels are merged to get single matrix
        Mat result;
        vector<Mat> channels;
        for(int i=0;i<3;i++)
            channels.push_back(threshold);
        merge(channels,result);

        y+= transient.rows;
        result.copyTo(src(Rect(x,y,result.cols, result.rows)));
    }


    imshow(windowName, src);
    if(waitKey(30)>=0)
        exit(0);
}