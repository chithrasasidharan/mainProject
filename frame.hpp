#ifndef _FRAME_
#define _FRAME_
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/highgui/highgui_c.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class Frame{
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
    // Capture object to get video from
    VideoCapture cap;
    Point tl,br;
};
#endif