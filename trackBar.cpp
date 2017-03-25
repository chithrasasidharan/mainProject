#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
     // Read original image 
     VideoCapture cap(0);
      if(!cap.isOpened())
        return -1;
     Mat src;
     cap>>src;
     //if fail to read the image
     if (!src.data) 
     { 
          cout << "Error loading the image" << endl;
          return -1; 
     }

     // Create a window
     namedWindow("Image", 1);

     //Create trackbar to change brightness
     int iSliderValue1 = 70;
     createTrackbar("Hue", "Image", &iSliderValue1, 180);

     //Create trackbar to change contrast
     int iSliderValue2 = 50;
     createTrackbar("Saturation", "Image", &iSliderValue2, 100);

     int iSliderValue3 = 50;
     createTrackbar("Value", "Image", &iSliderValue2, 100);

     while (true)
     {
          Mat dst;
          int iBrightness  = iSliderValue1 - 50;
          double dContrast = iSliderValue2 / 50.0;
          src.convertTo(dst, -1, dContrast, iBrightness); 

          //show the brightness and contrast adjusted image
          imshow("Image", dst);

          // Wait until user press some key for 50ms
          int iKey = waitKey(50);

          //if user press 'ESC' key
          if (iKey == 27)
          {
               break;
          }
     }

     return 0;
}