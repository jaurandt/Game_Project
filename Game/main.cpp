#include <OGL3D/Game/Game.h>
#include <iostream>


int main() {
	std::cout << "Welcome to the Game!" << std::endl;

	try
	{
		Game game;
		game.Run();
	}
	catch (const std::exception& e)
	{
		std::cout << "An error occurred: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}