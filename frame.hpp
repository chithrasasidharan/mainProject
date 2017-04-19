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
    void read();
    void show();
    Mat src;
    VideoCapture cap;
};
#endif