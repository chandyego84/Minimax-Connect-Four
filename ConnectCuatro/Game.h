#pragma once

#include "Board.h"

// #define ROUND_DIVIDE(numer, denom) (((numer) + (denom) / 2) / (denom))

class Game {
public:
	Game(sf::RenderWindow& window);

	void run();

	unsigned int numberOfMoves() const;

	// checks if current player can win with next move using (col, row) position of piece being dropped
	//bool CheckWin(Board gameBoard, int column, int row) const;
	// checks if current player can win with next move using col position of piece being dropped
	bool CheckWin(const Board& gameBoard, int column, bool isAI) const;

	// AI solver
	int minimax(const Board& B, int numberOfMoves, bool isMaximizing);

private:
	sf::RenderWindow& _window;

	Piece _hoverPiece;

	unsigned int _numberMoves;

	int isAiPlaying; 

};