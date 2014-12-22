#include "Game.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")


//#include "Story.h"

int main()
{
//	Story s = Story("dialogue/dtest1.txt");


//	std::vector<Dialogue> d = s.getDialogue();

//	s.respond(2);

//	d = s.getDialogue();

	Game game = Game();
	game.run();

	return 0;
}