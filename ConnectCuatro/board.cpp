#include "Board.h"

Board::Board(sf::RenderWindow& window, int boardX, int boardY) : _window(window),
	_boardX(boardX), _boardY(boardY) {

	// get dimensions of the window
	int windowX = window.getSize().x;
	int windowY = window.getSize().y;

	_boardXpixels = windowX * 4 / 5;	// takes up 4/5 of width to potentially have more info on right-hand side of board

	// setting the up the board to be drawn
	_board.setSize(sf::Vector2f((float)(_boardXpixels), (float)windowY));
	_board.setFillColor(sf::Color::Blue);
	_board.setOutlineColor(sf::Color::Green);
	_board.setOutlineThickness(5);

	// setting up the initial pieces to be drawn
	_pieces = new Piece[boardX * boardY]; // initialize the # of pieces in array
	for (int i = 0; i < boardX * boardY; i++) {
		_pieces[i].coin.setRadius(float(windowX * 1 / 25));
		_pieces[i].coin.setPointCount(300);
		_pieces[i].coin.setOutlineThickness(-3);
		_pieces[i].coin.setOutlineColor(sf::Color::Black);
		_pieces[i].color = NONE;
		_pieces[i].player= EMPTY;

		// positions of the pieces as (x,y) coordinates on the board
		_pieces[i].pos_x = i % 7;
		_pieces[i].pos_y = i / 7;
	}
};

// get dimensions of the board
int Board::GetBoardX() const{
	return _boardX;
}

int Board::GetBoardY() const {
	return _boardY;
}

int Board::GetBoardXpixels() const {
	return _boardXpixels;
}

sf::RectangleShape Board::GetBoard() const{
	return _board;
}

Piece* Board::GetPieces() const {
	return _pieces;
}

int Board::PositionToIndex(int column, int row){

	int pos = column + (row * Board::WIDTH);  // derived formula to convert position on board to corresponding index

	return pos;
}

int Board::GetColumnHover(int mouse_x) const{

	int mouse_col = 0;
	float columnScale = 1.0 / _boardX; // for conventional board, board columns are split 1/7 each, so it will be 91 pixels each column

	if (mouse_x < _boardXpixels) { // hover within board frame--4/5 of the window
		mouse_col = (mouse_x / (columnScale * _boardXpixels)); // cols 0-6 correspond to x position on board
	}

	return mouse_col;

}

void Board::SetPieceColor(Piece& piece) {

	if (piece.color != NONE) {
		if (piece.color == RED) {
			piece.coin.setFillColor(sf::Color::Red);
		}
		else {
			piece.coin.setFillColor(sf::Color::Yellow);
		}
	}

}

void Board::SetPieceColor(int color, int index) {

	_pieces[index].color = color;

}

void Board::SetPiecePlayer(int player, int index) {

	_pieces[index].player = player;

}

void Board::HoverPiece(Piece& currPiece, int column) {

	currPiece.pos_x = 7 + (90 * column);
	currPiece.pos_y = 15; // hovering height
	SetPieceColor(currPiece);
	currPiece.coin.setPosition(currPiece.pos_x, currPiece.pos_y);

}

// checks to see whether column is playable (not full)

bool Board::CheckValidDrop(int column) {

	int positionIndex = 0;
	bool validCol = false;

	for (int i = Board::HEIGHT - 1; i > -1; i--) {
		// check pieces from bottom up
		// turn slot's board (x,y) position into the corresponding index in array
		positionIndex = PositionToIndex(column, i);
		if (_pieces[positionIndex].color == NONE) {
			// found the open slot (row)
			validCol = true;
		}
	}

	return validCol;

}

bool Board::CheckValidDrop(const Piece* pieces, int column)  {

	int positionIndex = 0;
	bool validCol = false;

	for (int i = Board::HEIGHT - 1; i > -1; i--) {
		// check pieces from bottom up
		// turn slot's board (x,y) position into the corresponding index in array
		positionIndex = PositionToIndex(column, i);
		if (pieces[positionIndex].color == NONE) {
			// found the open slot (row)
			validCol = true;
		}
	}

	return validCol;

}

vector<int> Board::GetValidColumns(const Piece* pieces) {

	vector<int> validColumns;

	for (int x = 0; x < Board::WIDTH; x++) {
		if (CheckValidDrop(pieces, x)) {
			validColumns.push_back(x);
		}
	}

	return validColumns;

}

// returns the playable row in a column
int Board::FindValidRow(Piece* pieces, int column) {
	
	int positionIndex = 0;

	for (int i = Board::HEIGHT - 1; i > -1; i--) {
		// check pieces from bottom up
		// turn slot's board (x,y) position into the corresponding index in array
		positionIndex = PositionToIndex(column, i);
		if (pieces[positionIndex].color == NONE) {
			// return the open row
			return i;
		}
	}

	return -1; // column is not playable

}

// sets up (x,y) position of piece being dropped
void Board::DropPiece(Piece& currPiece, int column, int row) {

	currPiece.pos_x = column;
	currPiece.pos_y = row;

}

void Board::DrawBoard() {
	
	_window.draw(_board);

	// draw each piece/slot on the board
	for (int i = 0; i < _boardX * _boardY; i++) {
		_pieces[i].coin.setPosition(7 + 90 * (_pieces[i].pos_x), 75 + 90 * (_pieces[i].pos_y));
		SetPieceColor(_pieces[i]);

		_window.draw(_pieces[i].coin);
	}

}
