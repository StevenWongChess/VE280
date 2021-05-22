#include "square.h"

Square::Square(Vaxis v, Haxis h){
	this->v = v;
	this->h = h;
	this->p = nullptr;
};

Vaxis Square::getV() const{
	return this->v;
}

void Square::setV(Vaxis v){
	this->v = v;
}

Haxis Square::getH() const{
	return this->h;
}

void Square::setH(Haxis h){
	this->h = h;
}

const Piece &Square::getPiece() const{
	if(this->p == nullptr)
		throw SquareException(*this, "empty");
	return *this->p;
}

void Square::setPiece(const Piece *p){
	this->p = p;
}

bool Square::isEmpty() const{
	return this->p == nullptr;
}

bool Square::isOnFirstDiagonal() const{
	return static_cast<int>(v) == static_cast<int>(h); 
}

bool Square::isOnSecondDiagonal() const{
	return (static_cast<int>(v) + static_cast<int>(h)) == (N - 1);
}

std::string Square::toString() const{
	return std::string(1, 'A' + v) + static_cast<char>('1' + h);
}


