#ifndef _HAND_
#define _HAND_ 

#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "frame.hpp"

using namespace cv;
using namespace std;

class Hand{
    void setBiggestContour();
    void initVectors();
    void eliminateDefects();
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
        Hand();
        // make contours from frame
        void makeContours(Frame);
};

#endif