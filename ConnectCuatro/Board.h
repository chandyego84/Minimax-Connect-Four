#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

enum PieceColor {
	NONE,
	RED,
	YELLOW
};

struct Piece {
	sf::CircleShape coin;
	PieceColor color;
	int pos_x;
	int pos_y;
};

struct testing {
	int x;
};

class Board {
public:

	// regular connect-4 board of 7x6
	Board(sf::RenderWindow& window, int boardX = 7, int boardY = 6);

	// getters
	int getBoardX() const;
	int getBoardY() const;
	Piece* getPieces() const;

	// setters
	void setPieceColor(Piece& piece);
	// other
	void drawBoard();

	int getColumnHover(int mouse_x);
	void hoverPiece(Piece currPiece, int mouse_x);



private:
	sf::RenderWindow& _window;
	// dimensions of the board
	int _boardX;
	int _boardY;

	sf::RectangleShape _board;
	Piece* _pieces; // array to hold all of the pieces
};