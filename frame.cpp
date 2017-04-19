#include "frame.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/highgui/highgui_c.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Frame::Frame(){
    cap=VideoCapture(0);
}
Frame::Frame(Mat s){
    src = s;
    cap=VideoCapture(0);
}
void Frame::read(){
    cap>>src;
    flip(src,src,1);
}
void Frame::show(){
    imshow("window", src);
    if(waitKey(30)>=0)
        exit(0);
}