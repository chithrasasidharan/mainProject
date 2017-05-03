//vlc link https://www.videolan.org/developers/vlc/doc/doxygen/html/group__libvlc__video.html

#include <iostream>
#include "command.hpp"
#include "main.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <vlc/vlc.h>
#include "opencv2/objdetect/objdetect.hpp"

using namespace std;
using namespace cv;

	
Command::Command(){
	instance = libvlc_new(0, NULL);
	media = libvlc_media_new_path(instance, fileName);	
	mplayer = libvlc_media_player_new_from_media(media);
	capture.open(-1);
	libvlc_media_release(media);
	help.push_back("thumbs up: play");
	help.push_back("thumbs down: pause");
	help.push_back("full hand: stop");
	help.push_back("swipe right: forward");
	help.push_back("swipe down: backward");
	help.push_back("swipe up: volume up");
	help.push_back("swipe down: volume down");
}
void Command::play(){
	cout<<"Playing music";
	libvlc_media_player_set_rate( mplayer,1); 	
	libvlc_media_player_play(mplayer);
}
void Command::pause(){
	cout<<"paused";
	libvlc_media_player_pause(mplayer);
}
void Command::stop(){
	libvlc_media_player_stop(mplayer);
}
void Command::bwd(){
	// libvlc_media_player_set_rate( mplayer,1); 	
}
void Command::fwd(){
	libvlc_media_player_set_rate( mplayer,20); 	
	// libvlc_video_get_track(mplayer); 	
}
void Command::volup(){
	// if(volume>=10){
		volume += 10;
		libvlc_audio_set_volume(mplayer, volume);
	// }
}
void Command::voldown(){
	if(volume>=10){
		volume -= 10;
		libvlc_audio_set_volume(mplayer, volume);
	}
}
int Command::getCommand(int i=-1){
	if(i==-1){
		for(int k=0; k<help.size(); k++)
			cout<<k+1<<": "<<help[k]<<endl;
	}
	else
		cout<<i<<": "<<help[i-1]<<endl;
}
int Command::doCommand(int i=-1){
	capture.read(frame);
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

int Command::recogniseCommand(vector<Hand> hands)
{
	int p=0;
	for(int i=0; i<hands.size()-1;++i){
		p+=hands[i+1].centroid.x-hands[i].centroid.x;
	}
	cout<<"difference : "<<p<<endl;
	if(p>frameWidth/divideBy)
		return 1;
	if(p<-frameWidth/divideBy)
		return 3;

	return -1;
}