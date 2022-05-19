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
	int mouse_x = 0; // x-position of the mouse
	int colHover = 0; // corresponding column position of mouse

	while (_window.isOpen()) {
		sf::Event event;
		while (_window.pollEvent(event)) {
			switch (event.type) {

			case event.Closed:
				_window.close();
				break;

			case event.MouseMoved:
				mouse_x = event.mouseMove.x;
				//cout << mouse_x << endl;
				break;

			default:
				break;
			}
		}

		_window.clear(sf::Color::Black);

		colHover = gameBoard.getColumnHover(mouse_x);

		// draw everything
		gameBoard.drawBoard();
		gameBoard.hoverPiece(_hoverPiece, colHover);

		// end current frame
		_window.display();
	}

};