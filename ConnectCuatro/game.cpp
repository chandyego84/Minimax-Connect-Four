#pragma once

#include "Game.h"

Game::Game(sf::RenderWindow& window) : _window(window) {

	_hoverPiece.coin.setRadius(float(window.getSize().x * 1 / 25));
	_hoverPiece.coin.setPointCount(300);
	_hoverPiece.coin.setOutlineThickness(-3);
	_hoverPiece.coin.setOutlineColor(sf::Color::Black);
	_hoverPiece.color = RED; // starting color is red
	_hoverPiece.pos_x = 0;
	_hoverPiece.pos_y = 0;
	_numberMoves = 0;

};

// returns total number of moves made since start of the game
unsigned int Game::numberOfMoves() const {
	return this->_numberMoves;
}

// checks if a column drop leads to a win
bool Game::CheckWin(Board gameBoard, int column, int row) const{
	
	bool isWon = false;
	Piece* pieces = gameBoard.getPieces();

	int arrPosition = gameBoard.positionToIndex(column, row);

	// (x,y) position of the dropped piece
	int droppedCol = pieces[arrPosition].pos_x;
	int droppedRow = pieces[arrPosition].pos_y;

	// holds array index of each piece being checked
	int currIndex = 0;

	int checkIterator = 0;
	// vertically down
	while (droppedRow + checkIterator < 6 && checkIterator < 4) { // make the 4 checks as long as within board frame
		currIndex = gameBoard.positionToIndex(droppedCol, droppedRow + checkIterator);
		if (pieces[currIndex].color == pieces[arrPosition].color) {
			// matching slot add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}	
	}
	if (checkIterator == 4) {
		// win
		return true;
	}

	// horizontally left
	while (droppedCol - checkIterator >= 0 && checkIterator < 4) { // make the 4 checks as long as within board frame
		currIndex = gameBoard.positionToIndex(droppedCol - checkIterator, droppedRow);
		if (pieces[currIndex].color == pieces[arrPosition].color) {
			// matching slot, add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}
	}
	if (checkIterator == 4) {
		// win
		return true;
	}

	checkIterator = 0;
	// horizontal right
	while (droppedCol + checkIterator < 7 && checkIterator < 4) { // make the 4 checks as long as within board frame
		currIndex = gameBoard.positionToIndex(droppedCol + checkIterator, droppedRow);
		if (pieces[currIndex].color == pieces[arrPosition].color) {
			// matching slot, add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}
	}
	if (checkIterator == 4) {
		// win
		return true;
	}

	checkIterator = 0;
	// down-diagonal left
	while (droppedRow + checkIterator < 6 && droppedCol - checkIterator >= 0 && checkIterator < 4) { // make the 4 checks as long as within board frame
		currIndex = gameBoard.positionToIndex(droppedCol - checkIterator, droppedRow + checkIterator);
		if (pieces[currIndex].color == pieces[arrPosition].color) {
			// matching slot, add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}
	}
	if (checkIterator == 4) {
		// win
		return true;
	}

	checkIterator = 0;
	// down-diagonal right
	while (droppedRow + checkIterator < 6 && droppedCol + checkIterator < 7 && checkIterator < 4) { // make the 4 checks as long as within board frame
		currIndex = gameBoard.positionToIndex(droppedCol + checkIterator, droppedRow + checkIterator);
		if (pieces[currIndex].color == pieces[arrPosition].color) {
			// matching slot, add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}
	}
	if (checkIterator == 4) {
		// win 
		return true;
	}

	checkIterator = 0;
	// up-diagonal left
	while (droppedRow - checkIterator >= 0 && droppedCol - checkIterator >= 0 && checkIterator < 4) {
		currIndex = gameBoard.positionToIndex(droppedCol - checkIterator, droppedRow - checkIterator);
		if (pieces[currIndex].color == pieces[arrPosition].color) {
			// matching slot, add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}
	}
	if (checkIterator == 4) {
		// win
		return true;
	}

	checkIterator = 0;
	// up-diagonal right
	while (droppedRow - checkIterator >= 0 && droppedCol + checkIterator < 7 && checkIterator < 4) {
		currIndex = gameBoard.positionToIndex(droppedRow - checkIterator, droppedCol + checkIterator);
		if (pieces[currIndex].color == pieces[arrPosition].color) {
			// matching slot, add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}
	}
	if (checkIterator == 4) {
		// win
		return true;
	}

	return false;
}

// Recursively solve a connect 4 position using negamax algorithm
// RETURNS: score of a position
// - 0 for draw game
// - Positive Score: if can win with whatever opponent is playing
//		- Score is number of moves left before you win. CHECK README (faster you can win, higher your score)
// - Negative Score: if opponent can force you to lose
//		- Score is opposite of the number of moves before you lose. CHECK README (faster you can lose, lower your score)
int Game::negamax(const Board& B) {

	// check for draw game
	if (this->numberOfMoves() == Board::WIDTH * Board::HEIGHT) {
		return 0;
	}

	// check if current player can win next move
	int validCol = -1;
	for (int x = 0; x < Board::WIDTH; x++) {
		validCol = B.checkValidDrop(x);
		if (B.checkValidDrop(x) && CheckWin(B, x, validCol)) {
			cout << "current player can win next move" << endl;
			return (Board::WIDTH * Board::HEIGHT + 1 - this->numberOfMoves()) / 2;
		}
	}

	// init the best possible score with lower bound of score
	int bestScore = -Board::WIDTH * Board::HEIGHT;

	// compute the score of all possible next moves and keep the best one


	return 1;

}

void Game::run() {

	Board gameBoard(_window);
	Piece* pieces = gameBoard.getPieces();

	bool isWon = false;

	int mouse_x = 0; // x-position of the mouse
	int colHover = 0; // corresponding column position of mouse
	int validCol = 0;
	int rowToDrop = 0;

	while (_window.isOpen()) {
		sf::Event event;
		while (_window.pollEvent(event)) {
			switch (event.type) {

			case event.Closed:
				_window.close();
				break;

			case event.MouseMoved:
				mouse_x = event.mouseMove.x;
				// set up hovering piece
				colHover = gameBoard.getColumnHover(mouse_x); // current piece to be dropped
				gameBoard.hoverPiece(_hoverPiece, colHover);

				break;
			
			case event.MouseButtonPressed:
				// human player drops their piece
				if (mouse_x < gameBoard.getBoardXpixels() && !isWon) { // mouse is within board frame; dropping event
					// find row in the column to drop
					// checks if column is playable
					validCol = gameBoard.checkValidDrop(colHover);
					
					if (validCol) {
						int validRow = gameBoard.findValidRow(colHover);
						int posIndex = gameBoard.positionToIndex(colHover, validRow);
						pieces[posIndex].color = _hoverPiece.color; // change color of slot being dropped in
						isWon = CheckWin(gameBoard, colHover, validRow); // check if recent play leads to win

						// AI Solver
						//negamax(gameBoard);

						// change token color for next player
						if (_hoverPiece.color == YELLOW) {
							_hoverPiece.color = RED;
						}
						else {
							_hoverPiece.color = YELLOW;
						}

						this->_numberMoves++; // update number of moves made in game

					}
					else {
						cout << "Not valid column on the board" << endl;
					}
				}

				break;

			default:
				break;
			}
		}

		_window.clear();
		
		// draw everything
		gameBoard.drawBoard();
		_window.draw(_hoverPiece.coin);

		// end current frame
		_window.display();
	}

};