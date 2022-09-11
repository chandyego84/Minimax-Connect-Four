#pragma once

#include "Board.h"

class Game {
public:
	Game(sf::RenderWindow& window);

	void run();
	bool CheckWin(Board gameBoard, int arrPosition);

private:
	sf::RenderWindow& _window;

	Piece _hoverPiece;

};