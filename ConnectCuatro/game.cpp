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

};

// after drop is made, checks for win starting from (x,y) position on board
bool Game::CheckWin(Board gameBoard, int arrPosition) {
	
	bool isWon = false;
	Piece* pieces = gameBoard.getPieces();
	int streak = 0; // needs 4 for a win

	// (x,y) position of the dropped piece
	int droppedCol = pieces[arrPosition].pos_x;
	int droppedRow = pieces[arrPosition].pos_y;

	// holds array index of each piece being checked
	// starting with piece most recently dropped
	int currIndex = gameBoard.positionToIndex(droppedCol, droppedRow);

	int checkIterator = 0;
	// vertically down
	while (droppedRow + checkIterator <= 6 && checkIterator < 4) { // make the 4 checks as long as within board frame
		currIndex = gameBoard.positionToIndex(droppedCol, droppedRow + checkIterator);
		if (pieces[currIndex].color == pieces[arrPosition].color) {
			// matching slot add to streak
			cout << "+1" << endl;
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
	while (droppedRow + checkIterator <= 6 && droppedCol - checkIterator >= 0 && checkIterator < 4) { // make the 4 checks as long as within board frame
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
	while (droppedRow + checkIterator <= 6 && droppedCol + checkIterator <= 5 && checkIterator < 4) { // make the 4 checks as long as within board frame
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
	while (droppedRow - checkIterator >= 0 && droppedCol + checkIterator <= 5 && checkIterator < 4) {
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

void Game::run() {

	Board gameBoard(_window);
	Piece* pieces = gameBoard.getPieces();

	bool isWon = false;

	int mouse_x = 0; // x-position of the mouse
	int colHover = 0; // corresponding column position of mouse
	int validRow = 0;

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
				// for dropping a piece
				if (mouse_x < gameBoard.getBoardXpixels()) { // mouse is within board frame; dropping event
					// find row in the column to drop
					validRow = gameBoard.checkValidDrop(colHover);
					if (validRow != -1) {
						int posIndex = gameBoard.positionToIndex(colHover, validRow);
						//gameBoard.dropPiece(pieces[posIndex], colHover, validRow); // redundant? already know the (x,y) position and changing its color in next line
						pieces[posIndex].color = _hoverPiece.color;
						if (_hoverPiece.color == YELLOW) {
							// YELLOW TO RED
							_hoverPiece.color = RED;
						}
						else {
							_hoverPiece.color = YELLOW;
						}
						isWon = CheckWin(gameBoard, posIndex);
						if (isWon) { 
							cout << "WINNER!!" << endl; 
						}
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