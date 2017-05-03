#include<iostream>
#include<command.hpp>
using namespace std;
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
