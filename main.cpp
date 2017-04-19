#include <iostream>
#include <frame.hpp>
#include <main.hpp>
#include <region.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/highgui/highgui_c.h"
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;
Frame f;

// Make a lot of regions
vector<Region> initRegions(Frame f)
{
    vector<Region> regions;
    regions.push_back(Region(Point(f.src.cols/3, f.src.rows/6), f.src));
	regions.push_back(Region(Point(f.src.cols/4, f.src.rows/2), f.src));
	regions.push_back(Region(Point(f.src.cols/3, f.src.rows/1.5), f.src));
	regions.push_back(Region(Point(f.src.cols/2, f.src.rows/2), f.src));
	regions.push_back(Region(Point(f.src.cols/2.5, f.src.rows/2.5), f.src));
	regions.push_back(Region(Point(f.src.cols/2, f.src.rows/1.5), f.src));
	regions.push_back(Region(Point(f.src.cols/2.5, f.src.rows/1.8), f.src));
    return regions;
}
void printText(Mat src, string text){
	int fontFace = FONT_HERSHEY_PLAIN;
	putText(src,text,Point(src.cols/2, src.rows*9/10),fontFace, 1.2f,Scalar(200,0,0),2);
}

void waitForPalmCover(vector<Region> regions){
    for(int i=0; i<waitForCoverIterations; ++i)
    {
        f.read();
        for(int i=0;i<regions.size(); ++i)
        {
            regions[i].draw(f.src);
        }
		string imgText=string("Cover rectangles with palm");
		printText(f.src,imgText);	
        
        f.show();
    }
}

int main()
{
    f.read();
    f.show();   
    namedWindow(windowName, CV_WINDOW_KEEPRATIO);
    vector<Region> regions = initRegions(f);
    waitForPalmCover(regions);
    while(true){
        f.read();

        f.show();
    }
    return 0;
}