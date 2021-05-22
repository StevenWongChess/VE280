#include "piece.h"

Piece::Piece(Height h, Color c, Shape s, Top t){
	this->h = h;
	this->c = c;
	this->s = s;
	this->t = t;
	used = false;
}

bool Piece::compareHeight(const Piece &p) const{
	return p.h == this->h;
}

bool Piece::compareColor(const Piece &p) const{
	return p.c == this->c;
}

bool Piece::compareShape(const Piece &p) const{
	return p.s == this->s;
}

bool Piece::compareTop(const Piece &p) const{
	return p.t == this->t;
}

bool Piece::isUsed() const{
	return this->used;
}

void Piece::setUsed(bool u){
	this->used = true;
}

std::string Piece::toString() const{
	return std::string(1,HCODE[h]) + CCODE[c] + SCODE[s] + TCODE[t];
}
