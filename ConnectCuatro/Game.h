#pragma once

#include "Board.h"

// #define ROUND_DIVIDE(numer, denom) (((numer) + (denom) / 2) / (denom))

class Game {
public:
	static const int WINDOW_LENGTH = 4; // set to 4: look for connection of 4

	Game(sf::RenderWindow& window);

	void Run();

	unsigned int NumberOfMoves() const;

	// checks current board state to determine if win has occurred
	bool CheckWin(const Board& gameBoard, const int playerPiece) const;

	// EvaluateWindow(): window size set to 4 (want connection of 4 pieces)
	// helper fxn for ScorePosition()
	// four discs -> score of 100
	// three discs -> score < score(four discs)
	// two discs -> score < score(three discs)
	// OPPONENT has three pieces connected, PLAYER -> score = negative
	int EvaluateWindow(const int window[WINDOW_LENGTH], const int playerPiece) const;


	// ScorePosition()
	// calculates all scores for each possible move for each player during the play
	// RETURNS: score of move
	//int ScorePosition();

	// IsTerminalNode()


	// Minimax()
	// Minimax algo to find optimal move, further optimized with alpha-beta pruning
	// Process: 
	// Look at valid positions in each column, recursively gets new score calculated in LUT
		// LUT: calculated according to evaluteWindow()
	// Updates optimal value from the child nodes
	// Alpha - new score; when alpha > current value -> stops recursing and updates new value
	//int Minimax(const Board& B, int numberOfMoves, bool isMaximizing);

private:
	sf::RenderWindow& _window;

	Piece _hoverPiece;

	unsigned int _numberMoves;
};