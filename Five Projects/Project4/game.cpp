#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>

#include "piece.h"
#include "pool.h"
#include "square.h"
#include "board.h"
#include "player.h"

using namespace std;

void test();
// void play_game();

int main(int argc, char const *argv[])
{
	test();
	// play_game();
	if (argc > 4 || argc < 3){
		cout << "wrong amount of arg!\n";
		return 0;
	}
	Pool pool;
	Board board;
	Player *player[2] = {nullptr, nullptr};
	int seed = (argc == 4) ? atoi(argv[3]) : 0;
	for(int i = 0; i < 2; i++){
		if(argv[i + 1] == string(1, 'h')){
			player[i] = getHumanPlayer(&board, &pool);
		}
		else if(argv[i + 1] == string(1, 'm')){
			player[i] = getMyopicPlayer(&board, &pool, seed);
		}
	}

	cout << board.toString();
	cout << pool.toString();

	for(int i = 0; i < NP; i++){
		cout << "Player " <<  i%2 + 1 << "\'s turn to select a piece:\n";
		Piece &p = player[i%2]->selectPiece();
		p.setUsed(true);
		cout << p.toString() <<  " selected.\n";

		cout << "Player " <<  2 - i%2 << "\'s turn to select a square:\n";
		Square &sq = player[1 - i%2]->selectSquare(p);
		cout << sq.toString() <<  " selected.\n";

		board.place(p, sq);
		cout << board.toString();
		cout << pool.toString();

		if(board.isWinning(p, sq)){
			cout << "Player " << 2 - i%2 << " has won!\n";
			return 0;
		}
	}
	
	cout << "It is a draw.\n";
	return 0;
}

void test(){
	/*************piece test**************/
	// Piece a(SHORT, SEPIA, SQUARE, HOLLOW);
	// Piece b;
	// assert(a.toString() == "SEQH");
	// assert(b.toString() == "SBCH");
	// assert(a.compareHeight(b));
	// assert(!a.compareColor(b));
	// assert(!a.compareShape(b));
	// assert(a.compareTop(b));
	// b.setUsed(true);
	// assert(b.isUsed());

	/************pool test***************/
	// Pool c;
	// cout << c.toString();
	// assert(c.getUnusedPiece(SHORT, BEIGE, CIRCLE, HOLLOW).toString() == "SBCH");
	// assert(c.getUnusedPiece("TEQO").toString() == "TEQO");

	/************square test***************/
	// Square d;
	// Square e(B, H3);
	// assert(e.getV() == B);
	// assert(d.isEmpty());
	// assert(d.isOnFirstDiagonal());
	// assert(e.isOnSecondDiagonal());
	// d.setPiece(&a);
	// assert(d.toString() == "A1");

	/***********board test****************/
	// Board f;
	// Square &g = f.getSquare(A, H1);
	// Square &h = f.getSquare(B, H2);
	// Square &i = f.getSquare(C, H3);
	// Square &j = f.getSquare(D, H4);
	// Piece k(SHORT, SEPIA, SQUARE, HOLLOW);
	// Piece l(SHORT, BEIGE, SQUARE, HOLLOW);
	// Piece m(SHORT, SEPIA, CIRCLE, HOLLOW);
	// Piece n(SHORT, SEPIA, SQUARE, SOLID);
	// f.place(k, g);
	// f.place(l, h);
	// f.place(m, i);
	// cout << f.toString();
	// assert(f.isWinning(n, j));

	/***********player test****************/
}







