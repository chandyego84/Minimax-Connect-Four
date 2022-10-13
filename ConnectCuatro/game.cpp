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
	isAiPlaying = false; // game starts with human
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

// checks if current player can win with next move using col position of piece being dropped
bool Game::CheckWin(const Board &gameBoard, int column, bool isAI) const {
	
	// given the board state	
	// check all possible orientations of connect 4 from drop position
		// checking to see if each slot matches the color of the current player's color (isAI)
	Piece* pieces = gameBoard.getPieces();

	int validRow = gameBoard.findValidRow(column);
	int arrPosition = gameBoard.positionToIndex(column, validRow);

	// (x,y) position of the dropped piece
	int droppedCol = pieces[arrPosition].pos_x;
	int droppedRow = pieces[arrPosition].pos_y;

	// holds array index of each piece being checked
	int currIndex = 0;

	int checkIterator = 0;
	// vertically down
	while (droppedRow + checkIterator < 6 && checkIterator < 4) { // make the 4 checks as long as within board frame
		currIndex = gameBoard.positionToIndex(droppedCol, droppedRow + checkIterator + 1);
		if (currIndex < 42 && pieces[currIndex].player == isAI) {
			// matching slot add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}
	}
	if (checkIterator == 3) {
		// win
		cout << "WIN";
		return true;
	}

	// horizontally left
	while (droppedCol - checkIterator >= 0 && checkIterator < 4) { // make the 4 checks as long as within board frame
		currIndex = gameBoard.positionToIndex(droppedCol - checkIterator - 1, droppedRow);
		if (currIndex < 42 && pieces[currIndex].player == isAI) {
			// matching slot, add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}
	}
	if (checkIterator == 3) {
		// win
		cout << "WIN";
		return true;
	}

	checkIterator = 0;
	// horizontal right
	while (droppedCol + checkIterator < 7 && checkIterator < 4) { // make the 4 checks as long as within board frame
		currIndex = gameBoard.positionToIndex(droppedCol + checkIterator + 1, droppedRow);
		if (currIndex < 42 && pieces[currIndex].player == isAI) {
			// matching slot, add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}
	}
	if (checkIterator == 3) {
		// win
		cout << "WIN";
		return true;
	}

	checkIterator = 0;
	// down-diagonal left
	while (droppedRow + checkIterator < 6 && droppedCol - checkIterator >= 0 && checkIterator < 4) { // make the 4 checks as long as within board frame
		currIndex = gameBoard.positionToIndex(droppedCol - checkIterator - 1, droppedRow + checkIterator + 1);
		if (currIndex < 42 && pieces[currIndex].player == isAI) {
			// matching slot, add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}
	}
	if (checkIterator == 3) {
		// win
		cout << "WIN";
		return true;
	}

	checkIterator = 0;
	// down-diagonal right
	while (droppedRow + checkIterator < 6 && droppedCol + checkIterator < 7 && checkIterator < 4) { // make the 4 checks as long as within board frame
		currIndex = gameBoard.positionToIndex(droppedCol + checkIterator + 1, droppedRow + checkIterator + 1);
		if (currIndex < 42 && pieces[currIndex].player == isAI) {
			// matching slot, add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}
	}
	if (checkIterator == 3) {
		// win 
		cout << "WIN";
		return true;
	}

	checkIterator = 0;
	// up-diagonal left
	while (droppedRow - checkIterator >= 0 && droppedCol - checkIterator >= 0 && checkIterator < 4) {
		currIndex = gameBoard.positionToIndex(droppedCol - checkIterator - 1, droppedRow - checkIterator - 1);
		if (currIndex < 42 && pieces[currIndex].player == isAI) {
			// matching slot, add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}
	}
	if (checkIterator == 3) {
		// win
		cout << "WIN";
		return true;
	}

	checkIterator = 0;
	// up-diagonal right
	while (droppedRow - checkIterator >= 0 && droppedCol + checkIterator < 7 && checkIterator < 4) {
		currIndex = gameBoard.positionToIndex(droppedRow - checkIterator - 1, droppedCol + checkIterator - 1);
		if (currIndex < 42 && pieces[currIndex].player == isAI) {
			// matching slot, add to streak
			checkIterator++;
		}
		else {
			// mismatch, stop checking
			break;
		}
	}
	if (checkIterator == 3) {
		// win
		cout << "WIN";
		return true;
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
int Game::Minimax(const Board& B, int numberOfMoves, bool isMaximizing) {

	// 1. terminating point
	// if game over in current position

	// check for draw game
	if (numberOfMoves == Board::WIDTH * Board::HEIGHT) {
		return 0;
	}

	// check if current player can win with next move
	for (int x = 0; x < Board::WIDTH; x++) {
		if (B.checkValidDrop(x) && CheckWin(B, x, isMaximizing)) { // check if col is playable and if it can win
			return (Board::WIDTH * Board::HEIGHT + 1 - numberOfMoves) / 2;
		}
	}
	// 2. if maximizing player; find highest evaluation that can be obtained from this position
	// loop through all children (positions that can be reached in single move) of current position
	// eval = minimax(child, depth - 1, false)
	// maxEval = max(maxEval, eval)
	// return maxEval
	//if (isMaximizing) {
	//	int maxEval = -Board::WIDTH * Board::HEIGHT; // init best possible score with lower bound on score
	//	int column = 0;
	//	for (int x = 0; x < Board::WIDTH; x++) { // loop through each possible next move
	//		int eval = Minimax(B, numberOfMoves + 1, false);
	//		maxEval = max(maxEval, eval);
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

						pieces[posIndex].player = isAiPlaying; // change state of that slot to which player played it
						isWon = CheckWin(gameBoard, colHover, isAiPlaying); // will this drop lead to a win?
						pieces[posIndex].color = _hoverPiece.color; // change color of slot being dropped in

						this->_numberMoves++;

						// change token color for next player
						if (_hoverPiece.color == YELLOW) {
							// switch to human player
							_hoverPiece.color = RED;
							isAiPlaying = false;
						}
						else {
							// switch to AI player
							_hoverPiece.color = YELLOW;
							isAiPlaying = true;
						}

						// AI's turn
						//if (_numberMoves == 7) {
						//	cout << "AIS TURN" << endl;
						//	isPlayableCol = 0;
						//	_hoverPiece.color = YELLOW;
						//	_hoverPiece.player = true;
						//	isAiPlaying = true;

						//	// making best move for AI
						//	int aiColumn = 0;
						//	aiColumn = Minimax(gameBoard, this->NumberOfMoves(), true); // find best move
						//	isPlayableCol = gameBoard.checkValidDrop(aiColumn); // make sure move is valid
						//	if (isPlayableCol) {
						//		int validRow = gameBoard.findValidRow(aiColumn);
						//		int posIndex = gameBoard.positionToIndex(aiColumn, validRow);

						//		pieces[posIndex].player = isAiPlaying;
						//		isWon = CheckWin(gameBoard, aiColumn, isAiPlaying);
						//		pieces[posIndex].color = _hoverPiece.color;

						//		this->_numberMoves++;
						//	}
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