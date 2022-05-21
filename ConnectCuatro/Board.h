#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

enum PieceColor {
	RED,
	YELLOW,
	NONE
};

struct Piece {
	sf::CircleShape coin;
	PieceColor color;
	int pos_x;
	int pos_y;
};

class Board {
public:

	// regular connect-4 board of 7x6
	Board(sf::RenderWindow& window, int boardX = 7, int boardY = 6);

	// getters
	int getBoardX() const;
	int getBoardY() const;
	int getBoardXpixels() const;
	sf::RectangleShape getBoard() const;
	Piece* getPieces() const;
	int positionToIndex(int column, int row); 

	// setters
	void setPieceColor(Piece& piece);

	// other
	int getColumnHover(int mouse_x);
	void hoverPiece(Piece& currPiece, int mouse_x);

	int checkValidDrop(int column);
	void dropPiece(Piece& currPiece, int column, int row);

	void drawBoard();


private:
	sf::RenderWindow& _window;
	// dimensions of the board
	int _boardX;
	int _boardY;
	int _boardXpixels;

	sf::RectangleShape _board;
	Piece* _pieces; // array to hold all of the pieces
};