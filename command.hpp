
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include "hand.hpp"
#include <vlc/vlc.h>
#include "opencv2/objdetect/objdetect.hpp"

using namespace std;
using namespace cv;

class Command{
	void play();
	void pause();
	void stop();
	void bwd();
	void fwd();
	void volup();
	void voldown();
public:
	int choice;
	// Command c;
	libvlc_instance_t *instance;
	libvlc_media_t *media;
	
	Point p,q;
    libvlc_media_player_t *mplayer;
    VideoCapture capture;
    Mat frame;
    int volume;
	vector<string> help;
	vector <int> difference;
	Command();
	int getCommand(int);
	int doCommand(int);
    int recogniseCommand(vector<Hand> hands);
};
