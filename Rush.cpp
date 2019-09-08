#include <string>
#include <vector>
#include "constants.h"
#include "GameManager.h"
#include <allegro.h>
volatile int hit_closed = 0;

void close_button_proc()
{
	hit_closed = 1;
}

int main(void) {

	std::vector<std::string> g1;

	GameState gs;
	//default settings if config does not exist
	gs.resolution_x = 640;
	gs.resolution_y = 480;
	gs.fullscreen = 0;
	gs.sound_volume = 10;
	gs.music_volume = 10;
	gs.exitGame = 0;

	GameManager gameManager(&gs);

	gameManager.init();
	gameManager.runGameLoop();
	gameManager.exit();



	return 0;
}
END_OF_MAIN()
