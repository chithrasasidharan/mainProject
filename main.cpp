#include <iostream>
#include "frame.hpp"
#include "main.hpp"
#include "command.hpp"
#include "hand.hpp"
#include "gesture.hpp"
#include "region.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
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
	putText(src,text,Point(src.cols/2, src.rows*9/10),fontFace, 1.2f,Scalar(200,0,0),2);
}

void initWindows(Frame f){

    namedWindow(windowName,CV_WINDOW_FULLSCREEN);

	// createTrackbar("lower1",windowName,&f.lower[0],255);
	// createTrackbar("upper1",windowName,&f.upper[0],255);
	// createTrackbar("lower2",windowName,&f.lower[1],255);
	// createTrackbar("upper2",windowName,&f.upper[1],255);
	// createTrackbar("lower3",windowName,&f.lower[2],255);
	// createTrackbar("upper3",windowName,&f.upper[2],255);
}

void waitForPalmCover(vector<Region> regions){
    for(int i=0; i<waitForCoverIterations; ++i)
    {
        f.read();
        for(int i=0;i<nSamples; ++i)
        {
            regions[i].draw(f.src);
        }
		string imgText=string("Cover rectangles with palm");
		printText(f.src,imgText);	
        f.show();
    }
}

void takeAverage(vector<Region> regions)
{
    for(int i=0; i<averageIterations; ++i)
    {
        f.read();
        cvtColor(f.src, f.src, originalToColor);
       for(int j=0;j<nSamples; ++j)
        {
            regions[j].getAverage(f.src, f.average[j]);
            regions[j].draw(f.src);
            // Testing cout output to see if average works
            // cout<<f.average[j][0]<<" "<<f.average[j][1]<<" "<<f.average[j][2]<<" "<<endl;
        }
        // cout<<endl;
        cvtColor(f.src, f.src, colorToOriginal);
		string imgText = string("Finding average color of hand");
		printText(f.src,imgText);	
        f.show();
    }
}

int main()
{
    f.read();
    Gesture g;
    vector<Region> regions = initRegions(f);
    initWindows(f);
    waitForPalmCover(regions);
    takeAverage(regions);
    vector<Hand> h(commandRate);
    Hand temp;
    Command com;
    int now=0;
    int noC=2;
    while(true){
        f.read();
        f.makeThreshold();
        temp = g.initFrame(f);
        if(temp.valid())
        {
            h.push_back(temp);
            now = (now+1)%commandRate;
            if(!now && noC--)
            {
                if(noC<0)
                    exit(0);
                // identify command
                for(int i=0;i<commandRate;++i)
                {
                    h[i].print();
                }
                cout<<endl;
                int command = com.recogniseCommand(h);
                cout<<"command : "<<command<<endl;
                if(command>-1)
                {
                    com.doCommand(command);
                }

                // clear for next round
                h.clear();
            }
        }
        f.show();
    }
    return 0;
}
