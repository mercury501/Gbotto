#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include "gbcpu.h"
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

	for (;;) {

		cpu.cycle();
	}

	return 0;
}
