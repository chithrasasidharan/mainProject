#ifndef _GESTURE_
#define _GESTURE_ 

#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "hand.hpp"
#include "frame.hpp"

using namespace cv;
using namespace std;

class Gesture{
    void setBiggestContour();
    void initVectors();
    void eliminateDefects();
    void checkHandExists();
    void print();
    void removeRedundantEndPoints(vector<Vec4i>);
    //angle between 3 points
    float getAngle(Point, Point, Point);
    //distance between two points
    float distanceP2P(Point, Point);
    // checks if it is a hand and prints accordingly
    void checkHand();
    // Hand functions
    void checkForOneFinger();
    void getFingerTips();
    void drawFingerTips();
    Point findCentroid();
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
        // to know if hand exists in frame
        bool hasHand;
        // constructor
        Gesture();
        // make contours from frame
        Hand initFrame(Frame);

        // Parts of the hand
        vector<Point> fingerTips;
        Point centroid;

};

#endif