#ifndef _HAND_
#define _HAND_
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
#include<gesture.hpp>
using namespace std;
using namespace cv;
class Hand
{
    void checkForOneFinger();
    void getFingerTips();
    public:
        Gesture g;
        void init(Gesture);
        Hand();
};

#endif