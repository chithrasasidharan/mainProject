#include "region.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

Region::Region(){
    tl=Point(0,0);
    br=Point(0,0);
    length = 20;
}

Region::Region(Point tlc, Mat src){
    length = 20;
    tl=tlc;
    br=Point(tl.x+length, tl.y+length);
    borderThickness=2;
    borderColor=Scalar(0,255,0);
    region=src(Rect(tl.x, tl.y, br.x-tl.x, br.y-tl.y));
}

void Region::draw(Mat src){
    rectangle(src, tl, br, borderColor, borderThickness);
}

int Region::getMedian(vector<int> values)
{
  int median;
  size_t size = values.size();
  sort(values.begin(), values.end());
  if (size  % 2 == 0)  {
      median = values[size / 2 - 1] ;
  } else{
      median = values[size / 2];
  }
  return median;
}

void Region::getAverage(Mat src, int averageColors[3]){
    Mat temp;
    region.copyTo(temp);
    vector<int> hm;
    vector<int> sm;
    vector<int> lm;
	for(int i=borderThickness; i<temp.rows-borderThickness; i++){
    	for(int j=borderThickness; j<temp.cols-borderThickness; j++){
    		hm.push_back(temp.data[temp.channels()*(temp.cols*i + j) + 0]) ;
        	sm.push_back(temp.data[temp.channels()*(temp.cols*i + j) + 1]) ;
        	lm.push_back(temp.data[temp.channels()*(temp.cols*i + j) + 2]) ;
   		}
	}
    averageColors[0]=getMedian(hm);
	averageColors[1]=getMedian(sm);
	averageColors[2]=getMedian(lm);
}