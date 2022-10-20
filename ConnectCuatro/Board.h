#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

enum PieceColor {
	NONE,
	RED,
	YELLOW
};

enum PiecePlayer {
	EMPTY,
	PLAYER,
	AI
};

struct Piece {
	sf::CircleShape coin;
	int color;
	int player;
	int pos_x;
	int pos_y;
};

class Board {
public:
	static const int WIDTH = 7;	// width of the board
	static const int HEIGHT = 6; // length of the board

	// regular connect-4 board of 7x6
	Board(sf::RenderWindow& window, int boardX = WIDTH, int boardY = HEIGHT);

	// copy constructor
	Board &operator=(const Board& rhs) {
		this->_board = rhs._board;
		this->_boardX = rhs._boardX;
		this->_boardY = rhs._boardY;
		this->_boardXpixels = rhs._boardXpixels;
		this->_pieces = rhs._pieces;
	}

	// getters
	int GetBoardX() const;
	
	int GetBoardY() const;
	
	int GetBoardXpixels() const;
	
	sf::RectangleShape GetBoard() const;
	
	Piece* GetPieces() const;

	static vector<int> GetValidColumns(const Piece* pieces);

	// setters
	void SetPieceColor(Piece& piece);

	void SetPieceColor(int color, int index);
	void SetPiecePlayer(int player, int index);

	// other
	int GetColumnHover(int mouse_x) const;

	void HoverPiece(Piece& currPiece, int mouse_x);

	bool CheckValidDrop(int column);
	static bool CheckValidDrop(const Piece* pieces, int column);
	
	static int FindValidRow(Piece* pieces, int column);

	static int PositionToIndex(int column, int row);

	void DropPiece(Piece& currPiece, int column, int row);

	void DrawBoard();


private:
	sf::RenderWindow& _window;
	// dimensions of the board
	int _boardX;
	int _boardY;
	int _boardXpixels;

	sf::RectangleShape _board;

	Piece* _pieces; // array to hold all of the pieces
};