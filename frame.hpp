#ifndef _FRAME_
#define _FRAME_
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/highgui/highgui_c.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class Frame{
// normalize colors to be within 0 to 255
Scalar normalizeColors(int, bool);
// If threshold exists, to display it. 
bool thresholdExists;
public:
    Frame();
    Frame(Mat);
    // read image
    void read();
    // Show image
    void show();
    // Initially read matrix
    Mat src;
    // The matrix where all the changes will occur
    Mat transient;
    // The matrix black and white matrix threshold
    Mat threshold;
    // The average, lower bound and upper bound color found after average function
    int average[7][3];
    Scalar lower;
    Scalar upper;
    // make the black and white threshold image
    void makeThreshold();
    // Capture object to get video from
    VideoCapture cap;
    Point tl,br;
};
#endif