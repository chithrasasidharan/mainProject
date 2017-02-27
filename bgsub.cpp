#include <vector>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include "opencv2/video/background_segm.hpp"

using namespace cv;
using namespace std;
Ptr<BackgroundSubtractor>pMOG2;	



int main(){
	VideoCapture cap(0);
	pMOG2 = new BackgroundSubtractorMOG2();
	if(!cap.isOpened())
		return -1;
	Mat sub;
	while(1){
		Mat frame;
		cap>>frame;
		// cap.read(frame);
		pMOG2->operator()(frame,sub,0.01);
		// cvtColor()
		imshow("subtracted",sub);
		imshow("image",frame);
		if(waitKey(30)>=0)
			break;
	}
}
