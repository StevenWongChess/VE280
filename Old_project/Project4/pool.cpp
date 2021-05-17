#include "pool.h"

Piece pieces[NP];

Piece & Pool::getUnusedPiece(int index){
	if(pieces[index].isUsed())
		throw UsedPieceException(pieces[index]);
	return pieces[index];
}

Pool::Pool(){
	for(int i = 0; i < NP; i++){
		pieces[i] = Piece(static_cast<Height>(i/8), static_cast<Color>((i%8)/4),
						  static_cast<Shape>((i%4)/2), static_cast<Top>(i%2) );
	}
}

Piece & Pool::getUnusedPiece(Height h, Color c, Shape s, Top t){
	return getUnusedPiece(8 * h + 4 * c + 2 * s + t);
}

Piece & Pool::getUnusedPiece(const std::string &in){
	int num = static_cast<int>(in[0] == 'T') * 8
			+ static_cast<int>(in[1] == 'E') * 4
			+ static_cast<int>(in[2] == 'Q') * 2
			+ static_cast<int>(in[3] == 'O');
	return getUnusedPiece(num);
}

std::string Pool::toString() const{
	std::string prompt = "";
	std::string first_line = "";
	std::string second_line = "";
	for(int i = 0; i < NP; i++){
		if(!pieces[i].isUsed()){
			first_line += pieces[i].toString().substr(0,2) + " ";
			second_line += pieces[i].toString().substr(2,2) + " ";
		}
	}
	if(first_line != ""){
		prompt = "Available:\n";
		first_line += "\n";
		second_line += "\n";
	}
	return prompt + first_line + second_line;
}





