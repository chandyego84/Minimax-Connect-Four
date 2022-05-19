/*
Connect Cuatro with SFML
*/

#include "Game.h"

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 630), "Connect Cuatro");
	Game game(window);
	game.run();

	return 0;
}

