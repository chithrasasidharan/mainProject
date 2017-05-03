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
#define	fontFace FONT_HERSHEY_PLAIN
#define	blurRadius 7
#define nSamples 7
// one hand is made every handSampleRate frames
#define handSampleRate 1
//  one command is identified from commandRate hands
#define commandRate 20
#define windowName "src"
#define fileName "poo.mp4"
#define PI 3.14159

// Variables for tuning
#define waitForCoverIterations 50
#define averageIterations 30

#define frameWidth 640
#define frameHeight 480
// do operation when width/divideby or height/divideby
#define divideBy 5

#endif