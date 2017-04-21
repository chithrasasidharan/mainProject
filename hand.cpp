#include "frame.hpp"
#include "main.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Hand::Hand(Frame frame){
    f=frame;
}