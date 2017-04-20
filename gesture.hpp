#ifndef _GESTURE_
#define _GESTURE_ 

#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "frame.hpp"

using namespace cv;
using namespace std;

class Gesture{
    void setBiggestContour();
    void initVectors();
    void eliminateDefects();
    void removeRedundantEndPoints(vector<Vec4i>);
    float getAngle(Point, Point, Point);
    float distanceP2P(Point, Point);
    public:
        Frame f;
        // no of the frame where hand was read
        int frameNo;
        int noOfFingers;

        // contours
        vector<vector<Point> > contours;
        vector<vector<int> > hullI;
        vector<vector<Point> > hullP;
        vector<vector<Vec4i> > defects;

        // helpers
        int bigIndex;
        Rect boundingRectangle;
        // constructor
        Gesture();
        // make contours from frame
        void initFrame(Frame);
        // checks if it is a hand and prints accordingly
        void checkHand();
};

#endif