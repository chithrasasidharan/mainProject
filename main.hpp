#ifndef _MAIN_HEADER_ 
#define _MAIN_HEADER_ 

#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>


#define originalToColor CV_BGR2HLS
#define colorToOriginal CV_HLS2BGR
#define NSAMPLES 7
#define windowName "src"
#define PI 3.14159

// Variables for tuning
#define waitForCoverIterations 50
#define handReadIterations 30


#endif