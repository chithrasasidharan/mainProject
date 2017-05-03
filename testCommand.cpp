#include<iostream>
#include"command.hpp"
#include"main.hpp"
using namespace std;
int main(int argc, char** argv)
{
	int choice;
	Command c;
	

	c.getCommand(0);

	while(true){

		
		cin>>choice;
		c.doCommand(choice);

	}
		

	return 0;
}
