#pragma once

#include "Board.h"

class Game {
public:
	Game(sf::RenderWindow& window);

	void run();


private:
	sf::RenderWindow& _window;

	Piece _hoverPiece;

};