#pragma once

#include "Board.h"

class Game {
public:
	Game(sf::RenderWindow& window);

	void run();

	unsigned int numberOfMoves() const;

	bool CheckWin(Board gameBoard, int column, int row) const;

	// AI solver
	int negamax(const Board& B);

private:
	sf::RenderWindow& _window;

	Piece _hoverPiece;

	unsigned int _numberMoves;

};