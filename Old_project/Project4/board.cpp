#include "board.h"

Board::Board(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			grid[i][j] = Square(static_cast<Vaxis>(i), static_cast<Haxis>(j));
		}
	}
}

Square &Board::getSquare(Vaxis v, Haxis h){
	return grid[static_cast<int>(v)][static_cast<int>(h)];
}

Square &Board::getEmptySquare(Vaxis v, Haxis h){
	if (!grid[v][h].isEmpty()){
		throw SquareException(grid[v][h], "not empty");
	}
	return grid[v][h];
}

Square &Board::getEmptySquare(const std::string &s){
	return getEmptySquare(static_cast<Vaxis>(s[0] - 'A'), static_cast<Haxis>(s[1] - '1'));
}

void Board::place(Piece &p, Square &sq){
	sq.setPiece(&p);
	p.setUsed(true);
}

bool Board::isWinning(const Piece &p, const Square &sq){

}
// REQUIRES: if "p" is used, then it is already placed on "sq".
//           Otherwise, "sq" is empty.
// EFFECTS: return true if piece "p" on square "sq" yields a
// winning position (i.e., 4 pieces with at least one common 
// attribute, which are aligned horizontally, vertically, or 
// diagonally
// REMARK: "p" may or may not have been placed on "sq"
// (Please think about why), which may be empty.

std::string Board::toString() const{
	std::string str = "    1    2    3    4\n";
	for(int i = 0; i < N; i++){
		str += "  +----+----+----+----+\n";
		for(int j = 0; j < 2; j++){
			str += "  |    |    |    |    |\n";
		}
	}
	str += "  +----+----+----+----+\n";
	return str;
}
// EFFECTS: return a string that represents the board
// e.g., at the beginning of the game, the returned string
//       prints as follows:
//     1    2    3    4
//   +----+----+----+----+
// a |    |    |    |    |
//   |    |    |    |    |
//   +----+----+----+----+
// b |    |    |    |    |
//   |    |    |    |    |
//   +----+----+----+----+
// c |    |    |    |    |
//   |    |    |    |    |
//   +----+----+----+----+
// d |    |    |    |    |
//   |    |    |    |    |
//   +----+----+----+----+
//       after placing, SBCH on A1 and TBQO on C2, we get:
//     1    2    3    4
//   +----+----+----+----+
// a | SB |    |    |    |
//   | CH |    |    |    |
//   +----+----+----+----+
// b |    |    |    |    |
//   |    |    |    |    |
//   +----+----+----+----+
// c |    | TB |    |    |
//   |    | QO |    |    |
//   +----+----+----+----+
// d |    |    |    |    |
//   |    |    |    |    |
//   +----+----+----+----+









