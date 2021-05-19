#include "board.h"

Board::Board(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			grid[i][j] = Square(static_cast<Vaxis>(i), static_cast<Haxis>(j));
		}
	}
}

Square &Board::getSquare(Vaxis v, Haxis h){
	return grid[v][h];
}

Square &Board::getEmptySquare(Vaxis v, Haxis h){
	if (!grid[v][h].isEmpty()){
		throw SquareException(grid[v][h], "not empty");
	}
	return grid[v][h];
}

Square &Board::getEmptySquare(const std::string &s){
	if (s.length() != 2 || s[0] - 'A' >= N || s[0] - 'A' < 0 || s[1] - '1' >= N || s[0] - '1' < 0){
		throw InvalidInputException(s);
	}
	return getEmptySquare(static_cast<Vaxis>(s[0] - 'A'), static_cast<Haxis>(s[1] - '1'));
}

void Board::place(Piece &p, Square &sq){
	sq.setPiece(&p);
	p.setUsed(true);
}

// Variadic Template and Parameter Pack 
// https://tjsw.medium.com/(chaoshandechao)-c-variadic-template-parameter-pack-d76c0a4ffcdd

static bool funH(const Piece &p, const Square &a){
	return p.compareHeight(a.getPiece());
}

static bool funC(const Piece &p, const Square &a){
	return p.compareColor(a.getPiece());
}

static bool funS(const Piece &p, const Square &a){
	return p.compareShape(a.getPiece());
}

static bool funT(const Piece &p, const Square &a){
	return p.compareTop(a.getPiece());
}

typedef bool (*comp)(const Piece&, const Square&);

bool SameAttribute(comp fun, const Piece &p, const Square &sq, const Square &a){
	return (sq.getV() == a.getV() && sq.getH() == a.getH()) ? 
			true /*a.isEmpty()*/ : (!a.isEmpty() && fun(p, a));
}

bool SameAttributes(comp fun, const Piece &p, const Square &sq, const Square &a, 
					const Square &b, const Square &c, const Square &d){
	return SameAttribute(fun, p, sq, a) && SameAttribute(fun, p, sq, b) &&
			SameAttribute(fun, p, sq, c) && SameAttribute(fun, p, sq, d);
}

bool SameRow(const Piece &p, const Square &sq, const Square &a, 
			const Square &b, const Square &c, const Square &d){
	//comp funH_ = funH;
	return SameAttributes(funH, p, sq, a, b, c, d) || SameAttributes(funC, p, sq, a, b, c, d) ||
		   SameAttributes(funS, p, sq, a, b, c, d) || SameAttributes(funT, p, sq, a, b, c, d);
}

bool Board::isWinning(const Piece &p, const Square &sq){
	Vaxis v = sq.getV();
	Haxis h = sq.getH();
	return SameRow(p, sq, grid[v][0], grid[v][1], grid[v][2], grid[v][3]) ||
		   SameRow(p, sq, grid[0][h], grid[1][h], grid[2][h], grid[3][h]) ||
		(sq.isOnFirstDiagonal() && SameRow(p, sq, grid[0][0], grid[1][1], grid[2][2], grid[3][3])) ||
		(sq.isOnSecondDiagonal() && SameRow(p, sq, grid[0][3], grid[1][2], grid[2][1], grid[3][0]));
}

std::string Board::toString() const{
	std::string str = "    1    2    3    4\n";
	for(int i = 0; i < N; i++){
		str += "  +----+----+----+----+\n";
		std::string first_line = "  |    |    |    |    |\n";
		std::string second_line = "  |    |    |    |    |\n";
		first_line[0] = static_cast<char>('a' + i);
		for(int j = 0; j < N; j++){
			if(!grid[i][j].isEmpty()){
				std::string tmp = grid[i][j].getPiece().toString();
				first_line.replace(4+5*j,2,tmp.substr(0,2));
				second_line.replace(4+5*j,2,tmp.substr(2,2));
			}
		}
		str += first_line + second_line;
	}
	str += "  +----+----+----+----+\n";
	return str;
}







