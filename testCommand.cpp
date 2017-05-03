#include<iostream>
#include"command.hpp"
#include"main.hpp"
using namespace std;
int main(int argc, char** argv)
{
	int choice;
	Command c;
	libvlc_instance_t *instance = libvlc_new(0, NULL);
	libvlc_media_t *media = libvlc_media_new_path(instance, fileName);	
	c.mplayer = libvlc_media_player_new_from_media(media);
	libvlc_media_release(media);
	c.capture.open(-1);

	c.getCommand(1);
	while(c.capture.read(c.frame)){

		
		cin>>choice;
		c.doCommand(choice);

	}
		

	return 0;
}
