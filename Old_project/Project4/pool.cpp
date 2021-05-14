#include "pool.h"

Piece pieces[NP];

Piece & Pool::getUnusedPiece(int index){
	if(pieces[index].isUsed())
		throw UsedPieceException(pieces[index]);
	return pieces[index];
}

Pool(){
	for()
}
// EFFECTS: creates a pool of the 16 unused Quarto pieces
// "unused" means "not placed on the board"

Piece & Pool::getUnusedPiece(Height h, Color c, Shape s, Top t){
	

}
// EFFECTS: return the reference to a piece "p" given its attributes
//          throw UsedPieceException if "p" is placed on the board

Piece & Pool::getUnusedPiece(const std::string &in){

}
// EFFECTS: return the reference to a piece "p" given its encoding
//          throw UsedPieceException if "p" is placed on the board
// see file "quarto.h/cpp" for the encoding of each attribute
// e.g., "SEQO" encodes a piece that is short, sepia, square, and solid

std::string Pool::toString() const;
// EFFECTS: returns a string that lists all the unused pieces
// preceded by string "Available:\n" if the list is not empty
//          returns the empty string otherwise
// e.g., when the game starts, the returned string would print as follows:
// Available:
// SB SB SB SB SE SE SE SE TB TB TB TB TE TE TE TE 
// CH CO QH QO CH CO QH QO CH CO QH QO CH CO QH QO
//
// Note that all the 4-character strings have been split over two
// lines (i.e., SBCH is the first piece, SBCO is the second...)