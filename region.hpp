#ifndef ROI 
#define ROI

#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
using namespace cv;

class Region{
    public:
        Region();
        // Region within a matrix, given by the top left and bottom right points.
        Region(Point tl, Point br, Mat src);
        // The region
        Mat region;
        // Color the region border is drawn in
        Scalar borderColor;
        // border thickness when drawing
        int borderThickness;
        // draw border
        void draw(Mat src);
        Point tl,br;
};
#endif
