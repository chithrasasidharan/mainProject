#ifndef _HAND_
#define _HAND_ 

#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "main.hpp"
#include "frame.hpp"

using namespace cv;
using namespace std;

class Hand{
    public:
        Frame f;
        // no of the frame where hand was read
        int frameNo;
        Hand();
}

#endif