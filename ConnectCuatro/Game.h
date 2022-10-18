#pragma once

#include "Board.h"

// #define ROUND_DIVIDE(numer, denom) (((numer) + (denom) / 2) / (denom))

class Game {
public:
	static const int WINDOW_LENGTH = 4;

	Game(sf::RenderWindow& window);

	void Run();

	unsigned int NumberOfMoves() const;

	// checks if current player can win with next move using col position of piece being dropped
	bool CheckWin(const Board& gameBoard, const int playerPiece) const;

	// evaluate window: window size set to 4 (want connection of 4 pieces)
	// four discs -> score of 100
	// three discs -> score < score(four discs)
	// two discs -> score < score(three discs)
	// OPPONENT has three pieces connected, PLAYER -> score = negative

	// is terminal node 

	// score position
	// calculates all scores for each possible move for each player
	// RETURNS: score of move
	//int ScorePosition();


	// AI solver
	// Minimax algo to find optimal move, further optimized with alpha-beta pruning
	//int Minimax(const Board& B, int numberOfMoves, bool isMaximizing);

private:
	sf::RenderWindow& _window;

	Piece _hoverPiece;

	unsigned int _numberMoves;
};