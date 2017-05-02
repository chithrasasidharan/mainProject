#ifndef _HAND_
#define _HAND_
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class Hand
{
    public:
        vector<Point> fingerTips;
        int noOfFingers;

        Hand();
        Hand(vector<Point>);

        void print();
        bool valid();
};

#endif