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
	_AiNodesExplored = 0;

};

// returns total number of moves made since start of the game
unsigned int Game::NumberOfMoves() const {
	return this->_numberMoves;
}


// checks if current board state has a win
// TODO: Make more efficient (e.g., bitboard, Convolution oepration on two dimensions of the board)
bool Game::CheckWin(const Board& gameBoard, const int playerPiece) const {
	
	Piece* pieces = gameBoard.GetPieces();

	// holds array index of each piece being checked
	int currIndex = 0;

	// check horizontal locations for win
	for (int c = 0; c < Board::WIDTH - 3; c++) {
		for (int r = 0; r < Board::HEIGHT; r++) {
			currIndex = gameBoard.PositionToIndex(c, r);
			if (pieces[currIndex].player == playerPiece && pieces[currIndex + 1].player == playerPiece
				&& pieces[currIndex + 2].player == playerPiece && pieces[currIndex + 3].player == playerPiece) {				
				return true;
			}
		}	
	}

	// check vertical locations for win 
	for (int c = 0; c < Board::WIDTH; c++) {
		for (int r = 0; r < Board::HEIGHT - 3; r++) {
			currIndex = gameBoard.PositionToIndex(c, r);
			if (pieces[currIndex].player == playerPiece && pieces[currIndex + 7].player == playerPiece
				&& pieces[currIndex + 14].player == playerPiece && pieces[currIndex + 21].player == playerPiece) {
				return true;
			}
		}
	}

	// check positive diagonals
	for (int c = 0; c < Board::WIDTH - 3; c++) {
		for (int r = 3; r < Board::HEIGHT; r++) {
			currIndex = gameBoard.PositionToIndex(c, r);
			if (pieces[currIndex].player == playerPiece && pieces[currIndex - 6].player == playerPiece
				&& pieces[currIndex - 12].player == playerPiece && pieces[currIndex - 18].player == playerPiece) {
				return true;
			}
		}
	}

	// check negative diagonals
	for (int c = 0; c < Board::WIDTH - 3; c++) {
		for (int r = 0; r < Board::HEIGHT - 3; r++) {
			currIndex = gameBoard.PositionToIndex(c, r);
			if (pieces[currIndex].player == playerPiece && pieces[currIndex + 8].player == playerPiece
				&& pieces[currIndex + 16].player == playerPiece && pieces[currIndex + 24].player == playerPiece) {
				return true;
			}
		}
	}

	return false;

}

bool Game::CheckWin(const Piece* pieces, const int playerPiece) {

	// holds array index of each piece being checked
	int currIndex = 0;

	// check horizontal locations for win
	for (int c = 0; c < Board::WIDTH - 3; c++) {
		for (int r = 0; r < Board::HEIGHT; r++) {
			currIndex = Board::PositionToIndex(c, r);
			if (pieces[currIndex].player == playerPiece && pieces[currIndex + 1].player == playerPiece
				&& pieces[currIndex + 2].player == playerPiece && pieces[currIndex + 3].player == playerPiece) {
				return true;
			}
		}
	}

	// check vertical locations for win 
	for (int c = 0; c < Board::WIDTH; c++) {
		for (int r = 0; r < Board::HEIGHT - 3; r++) {
			currIndex = Board::PositionToIndex(c, r);
			if (pieces[currIndex].player == playerPiece && pieces[currIndex + 7].player == playerPiece
				&& pieces[currIndex + 14].player == playerPiece && pieces[currIndex + 21].player == playerPiece) {
				return true;
			}
		}
	}

	// check positive diagonals
	for (int c = 0; c < Board::WIDTH - 3; c++) {
		for (int r = 3; r < Board::HEIGHT; r++) {
			currIndex = Board::PositionToIndex(c, r);
			if (pieces[currIndex].player == playerPiece && pieces[currIndex - 6].player == playerPiece
				&& pieces[currIndex - 12].player == playerPiece && pieces[currIndex - 18].player == playerPiece) {
				return true;
			}
		}
	}

	// check negative diagonals
	for (int c = 0; c < Board::WIDTH - 3; c++) {
		for (int r = 0; r < Board::HEIGHT - 3; r++) {
			currIndex = Board::PositionToIndex(c, r);
			if (pieces[currIndex].player == playerPiece && pieces[currIndex + 8].player == playerPiece
				&& pieces[currIndex + 16].player == playerPiece && pieces[currIndex + 24].player == playerPiece) {
				return true;
			}
		}
	}

	return false;

}

// board state has a win or draw 
bool Game::IsTerminalNode(const Board& gameBoard) const {
	return CheckWin(gameBoard, PLAYER) || CheckWin(gameBoard, AI) || Board::GetValidColumns(gameBoard.GetPieces()).empty();
}

bool Game::IsTerminalNode(const Piece* pieces) {
	return CheckWin(pieces, PLAYER) || CheckWin(pieces, AI) || Board::GetValidColumns(pieces).empty();
}

// Recursively solve a connect 4 position using minimax algorithm
// RETURNS: score, column to drop in
int* Game::Minimax(Piece* gameState, int depth, int alpha, int beta, int maximizingPlayer) {

	_AiNodesExplored++;
	int* columnAndScore = new int[2]; // stores column to drop and the score

	// if depth is zero or terminal node
	// only calculates the score
	bool isTerminalNode = IsTerminalNode(gameState);
	if (depth == 0 || isTerminalNode) {
		if (isTerminalNode) {
			if (CheckWin(gameState, AI)) {
				// AI is winner in this board state
				columnAndScore[0] = -1;
				columnAndScore[1] = 10000;
				return columnAndScore;
			}
			else if (CheckWin(gameState, PLAYER)) {
				// PLAYER is winner in this board state
				columnAndScore[0] = -1;
				columnAndScore[1] = -10000;
				return columnAndScore;
			}
			else {
				// DRAW in this board state
				columnAndScore[0] = -1;
				columnAndScore[1] = 0;
				return columnAndScore;
			}
		}
		else {
			columnAndScore[0] = -1;
			columnAndScore[1] = ScorePosition(gameState, maximizingPlayer);
			return columnAndScore;
		}
	}

	// AI player
	if (maximizingPlayer) {
		int value = -10000;
		int column = 0; // column to drop it in
		// check each drop
		for (int col = 0; col < Board::WIDTH; col++) {
			// make copy of the board state
			Piece* piecesCopy = new Piece[42];
			copy(gameState, gameState + 42, piecesCopy);
			
			// drop piece if column is valid
			if (Board::CheckValidDrop(piecesCopy, col)) {
				int row = Board::FindValidRow(gameState, col);
				int dropIndex = Board::PositionToIndex(col, row);
				piecesCopy[dropIndex].color = YELLOW;
				piecesCopy[dropIndex].player = AI;
			}

			int newScore = Minimax(piecesCopy, depth - 1, alpha, beta, false)[1];
			if (newScore > value) {
				value = newScore;
				column = col;
			}
			alpha = max(alpha, value);
			if (alpha >= beta) {
				break;
			}
		}
		columnAndScore[0] = column;
		columnAndScore[1] = value;
		return columnAndScore;
	}

	else {
		// minimizing player
		int value = 10000;
		int column = 0;
		for (int col = 0; col < Board::WIDTH; col++) {
			// make copy of the board state
			Piece* piecesCopy = new Piece[42];
			copy(gameState, gameState + 42, piecesCopy);

			if (Board::CheckValidDrop(piecesCopy, col)) {
				int row = Board::FindValidRow(gameState, col);
				int dropIndex = Board::PositionToIndex(col, row);
				piecesCopy[dropIndex].color = RED;
				piecesCopy[dropIndex].player = PLAYER;
			}

			int newScore = Minimax(piecesCopy, depth - 1, alpha, beta, true)[1];
			if (newScore < value) {
				value = newScore;
				column = col;
			}
			beta = min(beta, value);
			if (alpha >= beta) {
				break;
			}
		}
		columnAndScore[0] = column;
		columnAndScore[1] = value;
		return columnAndScore;
	}

}

int Game::EvaluateWindow(const int window[WINDOW_LENGTH], const int playerPiece)  {

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
	Piece* pieces = gameBoard.GetPieces();

	int currIndex = 0;

	// score for center column
	int centerCol = Board::WIDTH / 2;
	int centerCount = 0;
	// get player piece for each piece in center column
	for (int r = 0; r < Board::HEIGHT; r++) {
		currIndex = gameBoard.PositionToIndex(centerCol, r);
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
			currIndex = gameBoard.PositionToIndex(c, r);
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
			currIndex = gameBoard.PositionToIndex(c, r);
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
				window[i] = pieces[gameBoard.PositionToIndex(c + i, r - i)].player;
			}
			score += EvaluateWindow(window, playerPiece);
		}
	}
	
	// score negative diagonal
	for (int c = 0; c < Board::WIDTH - 3; c++) {
		for (int r = 0; r < Board::HEIGHT - 3; r++) {
			// go through each diagonal
			for (int i = 0; i < WINDOW_LENGTH; i++) {
				window[i] = pieces[gameBoard.PositionToIndex(c + i, r + i)].player;
			}
			score += EvaluateWindow(window, playerPiece);
		}
	}

	
	return score;
}

int Game::ScorePosition(const Piece* pieces, const int playerPiece) {

	int score = 0;
	int window[WINDOW_LENGTH] = {};

	int currIndex = 0;

	// score for center column
	int centerCol = Board::WIDTH / 2;
	int centerCount = 0;
	// get player piece for each piece in center column
	for (int r = 0; r < Board::HEIGHT; r++) {
		currIndex = Board::PositionToIndex(centerCol, r);
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
			currIndex = Board::PositionToIndex(c, r);
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
			currIndex = Board::PositionToIndex(c, r);
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
				window[i] = pieces[Board::PositionToIndex(c + i, r - i)].player;
			}
			score += EvaluateWindow(window, playerPiece);
		}
	}

	// score negative diagonal
	for (int c = 0; c < Board::WIDTH - 3; c++) {
		for (int r = 0; r < Board::HEIGHT - 3; r++) {
			// go through each diagonal
			for (int i = 0; i < WINDOW_LENGTH; i++) {
				window[i] = pieces[Board::PositionToIndex(c + i, r + i)].player;
			}
			score += EvaluateWindow(window, playerPiece);
		}
	}

	return score;

}


void Game::Run() {

	Board gameBoard(_window);
	Piece* pieces = gameBoard.GetPieces();

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
				colHover = gameBoard.GetColumnHover(mouse_x); // current piece to be dropped
				gameBoard.HoverPiece(_hoverPiece, colHover);

				break;
			
			case event.MouseButtonPressed:
				// human player drops their piece
				if (mouse_x < gameBoard.GetBoardXpixels() && !isWon) { // mouse is within board frame; dropping event
					// find row in the column to drop
					// checks if column is playable
					isPlayableCol = gameBoard.CheckValidDrop(colHover);
					
					if (isPlayableCol) {
						int validRow = gameBoard.FindValidRow(pieces, colHover);
						int posIndex = gameBoard.PositionToIndex(colHover, validRow);

						pieces[posIndex].color = _hoverPiece.color; // change color of slot being dropped in
						pieces[posIndex].player = _hoverPiece.player; // change state of that slot to which player played it
						isWon = CheckWin(pieces, _hoverPiece.player);

						_numberMoves++;

						// switch to other player
						if (_hoverPiece.player == PLAYER) {
							_hoverPiece.player = AI;
							_hoverPiece.color = YELLOW;
						}
						else {
							_hoverPiece.player = PLAYER;
							_hoverPiece.color = RED;
						}

						// AI plays
						if (_numberMoves == 7) {
							cout << "MOVE 8" << endl;
							auto start = high_resolution_clock::now();
							int bestColumn = Minimax(pieces, 6, -1000, 1000, true)[0];
							auto end = high_resolution_clock::now();
							auto duration = duration_cast<seconds>(end - start);
							cout << "Best Col for AI: " << bestColumn << endl;
							cout << "AI Execution Time: " << duration.count() << " seconds" << endl;
							if (Board::CheckValidDrop(pieces, bestColumn)) {
								// drop AI piece if it is valid
								int validAiRow = Board::FindValidRow(pieces, bestColumn);
								int bestIndex = Board::PositionToIndex(bestColumn, validAiRow);
								pieces[bestIndex].color = YELLOW;
								pieces[bestIndex].player = AI;
								isWon = CheckWin(pieces, AI);
							}
							cout << "Game states explored: " << _AiNodesExplored << endl;
						}

						if (isWon) {
							cout << "Beat by low IQ search tree" << endl;
						}

						
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
		gameBoard.DrawBoard();
		_window.draw(_hoverPiece.coin);

		// end current frame
		_window.display();
	}

};