//vlc link https://www.videolan.org/developers/vlc/doc/doxygen/html/group__libvlc__video.html

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <vlc/vlc.h>
#include "opencv2/objdetect/objdetect.hpp"

using namespace std;
using namespace cv;

libvlc_media_player_t *mplayer;
VideoCapture capture;
Mat frame;
int volume;

class Command{
public:
	vector<string> help;
	Command(){
		help.push_back("thumbs up: play");
		help.push_back("thumbs down: pause");
		help.push_back("full hand: stop");
		help.push_back("swipe right: forward");
		help.push_back("swipe down: backward");
		help.push_back("swipe up: volume up");
		help.push_back("swipe down: volume down");
	}
	void play(){
		cout<<"Playing music";
		libvlc_media_player_set_rate( mplayer,1); 	
		libvlc_media_player_play(mplayer);

	}
	void pause(){
		cout<<"paused";
		libvlc_media_player_pause(mplayer);
	}
	void stop(){
		libvlc_media_player_stop(mplayer);

	}
	void bwd(){

		// libvlc_media_player_set_rate( mplayer,1); 	
	}
	void fwd(){
		libvlc_media_player_set_rate( mplayer,20); 	
		// libvlc_video_get_track(mplayer); 	


	}
	void volup(){
		// if(volume>=10){
			volume += 10;
			libvlc_audio_set_volume(mplayer, volume);
		// }

	}
	void voldown(){
		if(volume>=10){
			volume -= 10;
			libvlc_audio_set_volume(mplayer, volume);
		}
	}
	int getCommand(int i=-1){
		if(i==-1){
			for(int k=0; k<help.size(); k++)
				cout<<k+1<<": "<<help[k]<<endl;
		}
		else
			cout<<i<<": "<<help[i-1]<<endl;
	}

	int doCommand(int i=-1){
		if(i==-1||i==1){
			play();
		}
		else if(i==2)
			pause();
		else if(i==3)
			stop();
		else if(i==4)
			fwd();
		else if(i==5)
			bwd();
		else if(i==6)
			volup();
		else if(i==7) 
			voldown();
		else
			cout<<"Invalid entry";
	}
};
void play(){
	cout<<"check";
	libvlc_media_player_play(mplayer);
	
}
int main(int argc, char** argv)
{
	int choice;

	libvlc_instance_t *instance = libvlc_new(0, NULL);
	libvlc_media_t *media = libvlc_media_new_path(instance, argv[1]);	
	mplayer = libvlc_media_player_new_from_media(media);
	libvlc_media_release(media);
	capture.open(-1);

	Command c;
	c.getCommand(1);
	while(capture.read(frame)){

		
		cin>>choice;
		c.doCommand(choice);

	}
		

	return 0;
}
