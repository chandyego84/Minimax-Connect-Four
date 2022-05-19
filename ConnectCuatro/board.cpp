#include "Board.h"

Board::Board(sf::RenderWindow& window, int boardX, int boardY) : _window(window),
	_boardX(boardX), _boardY(boardY) {

	// get dimensions of the window
	int windowX = window.getSize().x;
	int windowY = window.getSize().y;

	// setting the up the board to be drawn
	// takes up 4/5 of width to potentially have more info on right-hand side of board
	_board.setSize(sf::Vector2f((float)(windowX * 4 / 5), (float)windowY));
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

		// positions of the pieces as (x,y) coordinates on the board
		_pieces[i].pos_x = i % 7;
		_pieces[i].pos_y = i / 7;
	}

};

// get dimensions of the board
int Board::getBoardX() const{
	return _boardX;
}

int Board::getBoardY() const {
	return _boardY;
}

Piece* Board::getPieces() const {
	return _pieces;
}

int Board::getColumnHover(int mouse_x) {

	int mouse_col = 0;
	int boardx_Pixels = _window.getSize().x * 4 / 5; // # of pixels of width of board
	float columnScale = 1.0 / _boardX; // for conventional board, board columns are split 1/7 each, so it will be 91 pixels each column

	if (mouse_x < boardx_Pixels) { // hover within board frame--4/5 of the window
		mouse_col = (mouse_x / (columnScale * boardx_Pixels)); // cols 0-6 correspond to x position on board
	}

	return mouse_col;

}

void Board::setPieceColor(Piece& piece) {
	if (piece.color != NONE) {
		if (piece.color == RED) {
			piece.coin.setFillColor(sf::Color::Red);
		}
		else {
			piece.coin.setFillColor(sf::Color::Yellow);
		}
	}
}

void Board::hoverPiece(Piece currPiece, int column) {

	currPiece.pos_x = 7 + (90 * column);
	currPiece.pos_y = 15;
	setPieceColor(currPiece);
	currPiece.coin.setPosition(currPiece.pos_x, currPiece.pos_y);
	_window.draw(currPiece.coin);

}

void Board::drawBoard() {

	_window.draw(_board);

	// draw each piece/slot on the board
	for (int i = 0; i < _boardX * _boardY; i++) {
		_pieces[i].coin.setPosition(7 + 90 * (_pieces[i].pos_x), 75 + 90 * (_pieces[i].pos_y));
		setPieceColor(_pieces[i]);

		_window.draw(_pieces[i].coin);
	}

}
