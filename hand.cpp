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

// convexity defects does not check for one finger
// so another method has to check when there are no
// convexity defects
void Hand::checkForOneFinger(){
	int yTol=g.boundingRectangle.height/6;
	Point highestP;
	highestP.y=g.f.src.rows;
	vector<Point>::iterator d=g.contours[g.bigIndex].begin();
	while( d!=g.contours[g.bigIndex].end() ) {
   	    Point v=(*d);
		if(v.y<highestP.y){
			highestP=v;
			cout<<highestP.y<<endl;
		}
		d++;	
	}int n=0;
	d=g.hullP[g.bigIndex].begin();
	while( d!=g.hullP[g.bigIndex].end() ) {
   	    Point v=(*d);
			cout<<"x " << v.x << " y "<<  v.y << " highestpY " << highestP.y<< "ytol "<<yTol<<endl;
		if(v.y<highestP.y+yTol && v.y!=highestP.y && v.x!=highestP.x){
			n++;
		}
		d++;	
	}if(n==0){
		fingerTips.push_back(highestP);
	}
}
void Hand::getFingerTips(){
	fingerTips.clear();
	int i=0;
	vector<Vec4i>::iterator d=g.defects[g.bigIndex].begin();
	while( d!=g.defects[g.bigIndex].end() ) {
   	    Vec4i& v=(*d);
	    int startidx=v[0]; Point ptStart(g.contours[g.bigIndex][startidx] );
   		int endidx=v[1]; Point ptEnd(g.contours[g.bigIndex][endidx] );
  	    int faridx=v[2]; Point ptFar(g.contours[g.bigIndex][faridx] );
		if(i==0){
			fingerTips.push_back(ptStart);
			i++;
		}
		fingerTips.push_back(ptEnd);
		d++;
		i++;
   	}
	if(fingerTips.size()==0){
		checkForOneFinger();
	}
}

void Hand::init(Gesture gesture){
    g=gesture;
    getFingerTips();
}