#include <iostream>
#include <frame.hpp>
#include <region.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/highgui/highgui_c.h"
#include <opencv2/opencv.hpp>
#include <vector>
#define square_len 20
using namespace std;
using namespace cv;

// Make a lot of regions
vector<Region> initRegions(Frame f)
{
    vector<Region> regions;
    regions.push_back(Region(Point(f.src.cols/3,   f.src.rows/6),Point(f.src.cols/3+square_len,f.src.rows/6+square_len),f.src));
	regions.push_back(Region(Point(f.src.cols/4,   f.src.rows/2),Point(f.src.cols/4+square_len,f.src.rows/2+square_len),f.src));
	regions.push_back(Region(Point(f.src.cols/3,   f.src.rows/1.5),Point(f.src.cols/3+square_len,f.src.rows/1.5+square_len),f.src));
	regions.push_back(Region(Point(f.src.cols/2,   f.src.rows/2),Point(f.src.cols/2+square_len,f.src.rows/2+square_len),f.src));
	regions.push_back(Region(Point(f.src.cols/2.5, f.src.rows/2.5),Point(f.src.cols/2.5+square_len,f.src.rows/2.5+square_len),f.src));
	regions.push_back(Region(Point(f.src.cols/2,   f.src.rows/1.5),Point(f.src.cols/2+square_len,f.src.rows/1.5+square_len),f.src));
	regions.push_back(Region(Point(f.src.cols/2.5, f.src.rows/1.8),Point(f.src.cols/2.5+square_len,f.src.rows/1.8+square_len),f.src));
    return regions;
}
int main()
{
    Frame f;
    f.read();
    vector<Region> regions = initRegions(f);
    f.show();
    while(true){
        f.read();

        f.show();
    }
    return 0;
}