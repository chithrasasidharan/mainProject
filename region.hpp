#ifndef ROI 
#define ROI

#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <vector>
using namespace cv;

class Region{
    int getMedian(vector<int>);
    public:
        Region();
        // Region within a matrix, given by the top left and bottom right points.
        Region(Point tl, Mat src);
        // The region
        Mat region;
        // length of region
        int length;
        // Color the region border is drawn in
        Scalar borderColor;
        // border thickness when drawing
        int borderThickness;
        // draw border
        void draw(Mat src);
        //get average color of src in region
        void getAverage(Mat src, int colors[3]); 
        Point tl, br;
};
#endif
