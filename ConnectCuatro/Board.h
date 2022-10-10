#pragma once

#include <iostream>
#include <algorithm>
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
	int player; // -1: nobody, 0: human, 1: AI
	int pos_x;
	int pos_y;
};

class Board {
public:
	static const int WIDTH = 7;	// width of the board
	static const int HEIGHT = 6; // length of the board

	// regular connect-4 board of 7x6
	Board(sf::RenderWindow& window, int boardX = WIDTH, int boardY = HEIGHT);

	// getters
	int getBoardX() const;
	int getBoardY() const;
	int getBoardXpixels() const;
	sf::RectangleShape getBoard() const;
	Piece* getPieces() const;
	int positionToIndex(int column, int row) const; 

	// setters
	void setPieceColor(Piece& piece);

	// other
	int getColumnHover(int mouse_x) const;
	void hoverPiece(Piece& currPiece, int mouse_x);

	bool checkValidDrop(int column) const;
	int findValidRow(int column) const;
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