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

using namespace cv;
using namespace std;
Ptr<BackgroundSubtractor>pMOG2;
cv::vector<cv::Point> pointList;
Scalar runningAvg = Scalar(0,0,0);


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

int main(){
    VideoCapture cap(0);
    int loopCtr=0;
    pMOG2 = new BackgroundSubtractorMOG2();
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
            //chec
            for(int i=0; i<pointList.size(); i++)
                circle(frame,pointList[i],radius,Scalar(255,255,255),-1,8);
            cout<<getAvgColor(frame)<<endl;

        }

        imshow("image",frame);
        if(waitKey(30)>=0)
            break;
    }
}
