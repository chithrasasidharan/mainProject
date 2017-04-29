#include "frame.hpp"
#include "gesture.hpp"
#include "main.hpp"
#include "hand.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Hand::Hand(){}

Hand::Hand(vector<Point> aFingerTips){
    fingerTips = aFingerTips;
    noOfFingers = fingerTips.size();
}
