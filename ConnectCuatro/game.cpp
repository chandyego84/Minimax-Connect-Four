#pragma once

#include "Game.h"

Game::Game(sf::RenderWindow& window) : _window(window) {

	_hoverPiece.coin.setRadius(float(window.getSize().x * 1 / 25));
	_hoverPiece.coin.setPointCount(300);
	_hoverPiece.coin.setOutlineThickness(-3);
	_hoverPiece.coin.setOutlineColor(sf::Color::Black);
	_hoverPiece.color = RED; // starting color is red
	_hoverPiece.player = PLAYER;
	_hoverPiece.pos_x = 0;
	_hoverPiece.pos_y = 0;
	_numberMoves = 0;

};

// returns total number of moves made since start of the game
unsigned int Game::NumberOfMoves() const {
	return this->_numberMoves;
}

// checks if a column drop leads to a win using (col, row) position on board
//bool Game::CheckWin(Board gameBoard, int column, int row) const{
//	
//	Piece* pieces = gameBoard.getPieces();
//
//	int arrPosition = gameBoard.positionToIndex(column, row);
//
//	// (x,y) position of the dropped piece
//	int droppedCol = pieces[arrPosition].pos_x;
//	int droppedRow = pieces[arrPosition].pos_y;
//
//	// holds array index of each piece being checked
//	int currIndex = 0;
//
//	int checkIterator = 0;
//	// vertically down
//	while (droppedRow + checkIterator < 6 && checkIterator < 4) { // make the 4 checks as long as within board frame
//		currIndex = gameBoard.positionToIndex(droppedCol, droppedRow + checkIterator);
//		if (pieces[currIndex].color == pieces[arrPosition].color) {
//			// matching slot add to streak
//			checkIterator++;
//		}
//		else {
//			// mismatch, stop checking
//			break;
//		}	
//	}
//	if (checkIterator == 4) {
//		// win
//		return true;
//	}
//
//	// horizontally left
//	while (droppedCol - checkIterator >= 0 && checkIterator < 4) { // make the 4 checks as long as within board frame
//		currIndex = gameBoard.positionToIndex(droppedCol - checkIterator, droppedRow);
//		if (pieces[currIndex].color == pieces[arrPosition].color) {
//			// matching slot, add to streak
//			checkIterator++;
//		}
//		else {
//			// mismatch, stop checking
//			break;
//		}
//	}
//	if (checkIterator == 4) {
//		// win
//		return true;
//	}
//
//	checkIterator = 0;
//	// horizontal right
//	while (droppedCol + checkIterator < 7 && checkIterator < 4) { // make the 4 checks as long as within board frame
//		currIndex = gameBoard.positionToIndex(droppedCol + checkIterator, droppedRow);
//		if (pieces[currIndex].color == pieces[arrPosition].color) {
//			// matching slot, add to streak
//			checkIterator++;
//		}
//		else {
//			// mismatch, stop checking
//			break;
//		}
//	}
//	if (checkIterator == 4) {
//		// win
//		return true;
//	}
//
//	checkIterator = 0;
//	// down-diagonal left
//	while (droppedRow + checkIterator < 6 && droppedCol - checkIterator >= 0 && checkIterator < 4) { // make the 4 checks as long as within board frame
//		currIndex = gameBoard.positionToIndex(droppedCol - checkIterator, droppedRow + checkIterator);
//		if (pieces[currIndex].color == pieces[arrPosition].color) {
//			// matching slot, add to streak
//			checkIterator++;
//		}
//		else {
//			// mismatch, stop checking
//			break;
//		}
//	}
//	if (checkIterator == 4) {
//		// win
//		return true;
//	}
//
//	checkIterator = 0;
//	// down-diagonal right
//	while (droppedRow + checkIterator < 6 && droppedCol + checkIterator < 7 && checkIterator < 4) { // make the 4 checks as long as within board frame
//		currIndex = gameBoard.positionToIndex(droppedCol + checkIterator, droppedRow + checkIterator);
//		if (pieces[currIndex].color == pieces[arrPosition].color) {
//			// matching slot, add to streak
//			checkIterator++;
//		}
//		else {
//			// mismatch, stop checking
//			break;
//		}
//	}
//	if (checkIterator == 4) {
//		// win 
//		return true;
//	}
//
//	checkIterator = 0;
//	// up-diagonal left
//	while (droppedRow - checkIterator >= 0 && droppedCol - checkIterator >= 0 && checkIterator < 4) {
//		currIndex = gameBoard.positionToIndex(droppedCol - checkIterator, droppedRow - checkIterator);
//		if (pieces[currIndex].color == pieces[arrPosition].color) {
//			// matching slot, add to streak
//			checkIterator++;
//		}
//		else {
//			// mismatch, stop checking
//			break;
//		}
//	}
//	if (checkIterator == 4) {
//		// win
//		return true;
//	}
//
//	checkIterator = 0;
//	// up-diagonal right
//	while (droppedRow - checkIterator >= 0 && droppedCol + checkIterator < 7 && checkIterator < 4) {
//		currIndex = gameBoard.positionToIndex(droppedRow - checkIterator, droppedCol + checkIterator);
//		if (pieces[currIndex].color == pieces[arrPosition].color) {
//			// matching slot, add to streak
//			checkIterator++;
//		}
//		else {
//			// mismatch, stop checking
//			break;
//		}
//	}
//	if (checkIterator == 4) {
//		// win
//		return true;
//	}
//
//	return false;
//}

// checks if current board state has a win
// TODO: Make more efficient (e.g., bitboard, Convolution oepration on two dimensions of the board)
bool Game::CheckWin(const Board& gameBoard, const int playerPiece) const {
	
	Piece* pieces = gameBoard.getPieces();

	// holds array index of each piece being checked
	int currIndex = 0;

	// check horizontal locations for win
	for (int c = 0; c < Board::WIDTH - 3; c++) {
		for (int r = 0; r < Board::HEIGHT; r++) {
			currIndex = gameBoard.positionToIndex(c, r);
			if (pieces[currIndex].player == playerPiece && pieces[currIndex + 1].player == playerPiece
				&& pieces[currIndex + 2].player == playerPiece && pieces[currIndex + 3].player == playerPiece) {				
				return true;
			}
		}	
	}

	// check vertical locations for win 
	for (int c = 0; c < Board::WIDTH; c++) {
		for (int r = 0; r < Board::HEIGHT - 3; r++) {
			currIndex = gameBoard.positionToIndex(c, r);
			if (pieces[currIndex].player == playerPiece && pieces[currIndex + 7].player == playerPiece
				&& pieces[currIndex + 14].player == playerPiece && pieces[currIndex + 21].player == playerPiece) {
				cout << "Vertical Win" << endl;
				return true;
			}
		}
	}

	// check positive diagonals
	for (int c = 0; c < Board::WIDTH - 3; c++) {
		for (int r = 3; r < Board::HEIGHT; r++) {
			currIndex = gameBoard.positionToIndex(c, r);
			if (pieces[currIndex].player == playerPiece && pieces[currIndex - 6].player == playerPiece
				&& pieces[currIndex - 12].player == playerPiece && pieces[currIndex - 18].player == playerPiece) {
				cout << "Positive Diagonal Win" << endl;
				return true;
			}
		}
	}

	// check negative diagonals
	for (int c = 0; c < Board::WIDTH - 3; c++) {
		for (int r = 0; r < Board::HEIGHT - 3; r++) {
			currIndex = gameBoard.positionToIndex(c, r);
			if (pieces[currIndex].player == playerPiece && pieces[currIndex + 8].player == playerPiece
				&& pieces[currIndex + 16].player == playerPiece && pieces[currIndex + 24].player == playerPiece) {
				cout << "Negative Diagonal Win" << endl;
				return true;
			}
		}
	}

	return false;

}

// Recursively solve a connect 4 position using minimax algorithm
// RETURNS: score of a position
// - 0 for draw game
// - Positive Score: if can win with whatever opponent is playing
//		- Score is number of moves left before you win. CHECK README (faster you can win, higher your score)
// - Negative Score: if opponent can force you to lose
//		- Score is opposite of the number of moves before you lose. CHECK README (faster you can lose, lower your score)
// PARAMETERS: Board object (to get positions), number of moves made so far, maximizingPlayer or minimizingPlayer 
// AI will be considered the maximizing player
// we will be checking every position (depth is max as possible); definitely going to be slow or fail
//int Game::Minimax(const Board& B, int numberOfMoves, bool isMaximizing) {

	//// 1. terminating point
	//// if game over in current position

	//// check for draw game
	//if (numberOfMoves == Board::WIDTH * Board::HEIGHT) {
	//	return 0;
	//}

	//// check if current player can win with next move
	//for (int x = 0; x < Board::WIDTH; x++) {
	//	if (B.checkValidDrop(x) && CheckWin(B, x, isMaximizing)) { // check if col is playable and if it can win
	//		return (Board::WIDTH * Board::HEIGHT + 1 - numberOfMoves) / 2;
	//	}
	//}

	//// 2. if maximizing player; find highest evaluation that can be obtained from this position
	//// loop through all children (positions that can be reached in single move) of current position
	//// eval = minimax(child, depth - 1, false)
	//// maxEval = max(maxEval, eval)
	//// return maxEval
	//if (isMaximizing) {
	//	cout << "maximizing player: " << numberOfMoves << endl;
	//	int maxEval = -Board::WIDTH * Board::HEIGHT; // init best possible score with lower bound on score
	//	int column = 0;
	//	for (int x = 0; x < Board::WIDTH; x++) { // loop through each possible next move
	//		int eval = Minimax(B, numberOfMoves + 1, false);
	//		if (eval > maxEval) {
	//			maxEval = eval;
	//			column = x;
	//		}
	//	}
	//	return column;
	//}

	//// 3. if minimizing player;
	//// loop through all children of current position
	//// eval = minimax(child, depth - 1, true)
	//// minEval = min(minEval, eval)
	//// return minEval
	//else {
	//	int minEval = Board::WIDTH * Board::HEIGHT; // init min possible score with higher bound on score
	//	int column = 0;
	//	for (int x = 0; x < Board::WIDTH; x++) { // loop through each possible next move
	//		int eval = Minimax(B, numberOfMoves + 1, true);
	//		if (eval < minEval) {
	//			minEval = eval;
	//			column = x;
	//		}
	//	}
	//	return column;
	//}

//}

int Game::EvaluateWindow(const int window[WINDOW_LENGTH], const int playerPiece) const {

	int score = 0;
	int opponent = PLAYER;
	if (playerPiece == PLAYER) {
		opponent = AI;
	}

	int numCurrentPlayer = 0;
	int numOpponentPlayer = 0;
	int numEmptyPlayer = 0;

	// checks the type of piece in each window
	for (int piece = 0; piece < WINDOW_LENGTH; piece++) {
		if (window[piece] == playerPiece) {
			// current piece is the current player
			numCurrentPlayer++;
		}
		else if (window[piece] == opponent) {
			// current piece is the opponent player
			numOpponentPlayer++;
		}
		else {
			// current piece is empty
			numEmptyPlayer++;
		}
	}

	if (numCurrentPlayer == 4) {
		score += 100;
	}
	else if (numCurrentPlayer == 3 && numEmptyPlayer == 1) {
		score += 5;
	}
	else if (numCurrentPlayer == 2 && numEmptyPlayer == 2) {
		score += 2;
	}

	if (numOpponentPlayer == 3 && numEmptyPlayer == 1) {
		// window has opponent at an advantage
		score -= 4;
	}

	return score;

}

int Game::ScorePosition(const Board& gameBoard, const int playerPiece) const {

	int score = 0;
	int window[WINDOW_LENGTH] = {};
	Piece* pieces = gameBoard.getPieces();

	int currIndex = 0;

	// score for center column
	int centerCol = Board::WIDTH / 2;
	int centerCount = 0;
	// get player piece for each piece in center column
	for (int r = 0; r < Board::HEIGHT; r++) {
		currIndex = gameBoard.positionToIndex(centerCol, r);
		if (pieces[currIndex].player == playerPiece) {
			centerCount++;
		}
	} 
	score += centerCount * 3;

	// score horizontal
	int rowArray[Board::WIDTH] = {};
	for (int r = 0; r < Board::HEIGHT; r++) {
		// go through each row, make array of that row
		for (int c = 0; c < Board::WIDTH; c++) {
			currIndex = gameBoard.positionToIndex(c, r);
			rowArray[c] = pieces[currIndex].player;
		}

		// check each window in the row array
		for (int c = 0; c < Board::WIDTH - 3; c++) {
			for (int i = 0; i < WINDOW_LENGTH; i++) {
				// create next window in the row
				window[i] = rowArray[i + c];
			}
			score += EvaluateWindow(window, playerPiece);
		}
	}

	// score vertical
	int colArray[Board::HEIGHT] = {};
	for (int c = 0; c < Board::WIDTH; c++) {
		// go through each column, make array for that column
		for (int r = 0; r < Board::HEIGHT; r++) {
			currIndex = gameBoard.positionToIndex(c, r);
			colArray[r] = pieces[currIndex].player;
		}

		// check each window in the col array
		for (int r = 0; r < Board::HEIGHT - 3; r++) {
			for (int i = 0; i < WINDOW_LENGTH; i++) {
				// create next window in the column
				window[i] = colArray[i + r];
			}
			score += EvaluateWindow(window, playerPiece);
		}

	}

	// score positive diagonal
	for (int c = 0; c < Board::WIDTH - 3; c++) {
		for (int r = 3; r < Board::HEIGHT; r++) {
			// go through each diagonal
			for (int i = 0; i < WINDOW_LENGTH; i++) {
				// create next window
				window[i] = pieces[gameBoard.positionToIndex(c + i, r - i)].player;
			}
			score += EvaluateWindow(window, playerPiece);
		}
	}
	
	// score negative diagonal
	for (int c = 0; c < Board::WIDTH - 3; c++) {
		for (int r = 0; r < Board::HEIGHT - 3; r++) {
			// go through each diagonal
			for (int i = 0; i < WINDOW_LENGTH; i++) {
				/*if (c == 3 && r == 2) {
					cout << c + i << ", " << r + i << endl;
				}*/
				// create next window
				window[i] = pieces[gameBoard.positionToIndex(c + i, r + i)].player;
			}
			score += EvaluateWindow(window, playerPiece);
		}
	}

	
	return score;
}


void Game::Run() {

	Board gameBoard(_window);
	Piece* pieces = gameBoard.getPieces();

	bool isWon = false;

	int mouse_x = 0; // x-position of the mouse
	int colHover = 0; // corresponding column position of mouse
	int isPlayableCol = 0;

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
					isPlayableCol = gameBoard.checkValidDrop(colHover);

					if (isPlayableCol) {
						int validRow = gameBoard.findValidRow(colHover);
						int posIndex = gameBoard.positionToIndex(colHover, validRow);

						pieces[posIndex].color = _hoverPiece.color; // change color of slot being dropped in
						pieces[posIndex].player = _hoverPiece.player; // change state of that slot to which player played it
						isWon = CheckWin(gameBoard, _hoverPiece.player);
						cout << ScorePosition(gameBoard, _hoverPiece.player);

						this->_numberMoves++;

						// change token color for next player
						if (_hoverPiece.color == YELLOW) {
							// switch to human player
							_hoverPiece.color = RED;
							_hoverPiece.player = PLAYER;
						}
						else {
							// switch to AI player
							_hoverPiece.color = YELLOW;
							_hoverPiece.player = AI;
						}

						// AI's turn
						//if (NumberOfMoves() == 5 || NumberOfMoves() == 7) {
						//	cout << "AIS TURN" << endl;
						//	isPlayableCol = 0;
						//	_hoverPiece.color = YELLOW;
						//	_hoverPiece.player = AI;


						//	// making best move for AI
						//	int aiColumn = 0;
						//	aiColumn = Minimax(gameBoard, this->NumberOfMoves(), true); // AI makes best move
						//	isPlayableCol = gameBoard.checkValidDrop(aiColumn); // make sure move is valid
						//	if (isPlayableCol) {
						//		int validRow = gameBoard.findValidRow(aiColumn);
						//		int posIndex = gameBoard.positionToIndex(aiColumn, validRow);

						//		pieces[posIndex].player = AI;
						//		isWon = CheckWin(gameBoard, aiColumn, AI);
						//		pieces[posIndex].color = _hoverPiece.color;

						//		this->_numberMoves++;
						//	}

						//	// switch to human player
						//	_hoverPiece.color = RED;
						//	_hoverPiece.player = PLAYER;
						//	
						//}
						
					}

					else {
						cout << "Not valid column on the board" << endl;
					}


					break;
				}

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