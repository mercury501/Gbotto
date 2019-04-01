#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include "gbcpu.cpp"
#include <SDL2/SDL.h>

using namespace std;




int main(int argc, char* argv[])
{
	
	gbcpu cpu;

	

	int w = 512;
	int h = 512;

	SDL_Window* window = NULL;

	bool loaded = 0;


	cpu.initialize();

	if (argc == 2) {
		while (!loaded) {

			loaded = cpu.load_bin_char(argv[1]);
			if (!loaded)
				cout << endl << "Insert a valid file path" << endl;

		}
	}

	else
	{

		while (!loaded) {
			cout << "Insert rom file path:  ";
			string filepath;
			cin >> filepath;

			loaded = cpu.load_binary(filepath);
			if (!loaded)
				cout << endl << "Insert a valid file path" << endl;
		}

	}

	cpu.ginit();

	for (;;) {  // fps 59.7, clock 4.19 Mhz  69 833 ca instructions per second
		
		cpu.cycle();

		//cpu.drawDisplay();
		
	}

	return 0;
}
