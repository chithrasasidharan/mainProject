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

Hand::Hand(vector<Point> aFingerTips, Point aCentroid){
    fingerTips = aFingerTips;
    noOfFingers = fingerTips.size();
    centroid = aCentroid;
}

void Hand::print(){
    cout<<fingerTips.size()<<" : ";
    for(int i=0;i<fingerTips.size();++i)
    {
        cout<<fingerTips[i].x<<" "<<fingerTips[i].y<<", ";

    }
    cout<<"Centroid: "<<centroid.x<<" "<<centroid.y;
    cout<<endl;
}

bool Hand::valid(){
    return fingerTips.size()>0;
}
