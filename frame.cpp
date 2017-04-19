#include "frame.hpp"
#include "main.hpp"
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
    // Scale down
    pyrDown(src,transient);
    pyrDown(transient,transient);
    // change color
    cvtColor(transient, transient, originalToColor);
		
}
void Frame::show(){
    int x = src.cols - transient.cols;
    int y = 0;
    transient.copyTo(src(Rect(x,y,transient.cols, transient.rows)));
    imshow(windowName, src);
    if(waitKey(30)>=0)
        exit(0);
}