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

void Game::run() {

	Board gameBoard(_window);
	Piece* pieces = gameBoard.getPieces();
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