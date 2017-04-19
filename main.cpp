#include <iostream>
#include <frame.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/highgui/highgui_c.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Frame f;
int main()
{
    f.read();
    f.show();
    while(true){
        f.read();
        f.show();
    }
    return 0;
}