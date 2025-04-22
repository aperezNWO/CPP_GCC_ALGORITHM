///////////////////////////////////////////////////////////////////////////
// A C++ Program to play tic-tac-toe
// https://gist.github.com/amul-mehta/9ad947f41067cdbe2556
///////////////////////////////////////////////////////////////////////////

#ifndef TicTacToeManager_H // include guard
#define TicTacToeManager_H
#endif

#include "algorithm.h"

#define COMPUTER 1
#define HUMAN    2
#define SIDE     3        // Length of the board
#define COMPUTERMOVE 'O'  // Computer will move with 'O'
#define HUMANMOVE 'X'     // and human with 'X'

using namespace std;

#pragma hdrstop
#pragma argsused


class TicTacToeManager :
	public Algorithm
{
	public :
		void showBoard(char board[][SIDE]);
		void showInstructions();
		void initialise(char board[][SIDE]);
		void declareWinner(int whoseTurn);
		bool rowCrossed(char board[][SIDE]);
		bool columnCrossed(char board[][SIDE]);
		bool diagonalCrossed(char board[][SIDE]);
		bool gameOver(char board[][SIDE]);
		int minimax(char board[][SIDE], int depth, bool isAI);
		int bestMove(char board[][SIDE], int moveIndex);
		void playTicTacToe(int whoseTurn);
		int Run();
};




