#include "player.h"
#include <iostream>
#include <string>

class HumanPlayer: public Player{
public:
	HumanPlayer(): Player(nullptr, nullptr){};
	void set(Board *board, Pool *pool){
		// if (!this->board){
			this->board = board;
			this->pool = pool;
		// }
	}
	Piece & selectPiece() override;
	Square & selectSquare(const Piece &p) override;
};

class MyopicPlayer: public Player{
private:
	int seed;
public:
	void set(Board *board, Pool *pool, unsigned int seed){
		// if (!this->board){
			this->board = board;
			this->pool = pool;
			this->seed = seed;
			std::srand(seed);
		// }
	}
	MyopicPlayer(): Player(nullptr, nullptr){};
	Piece & selectPiece() override;
	Square & selectSquare(const Piece &p) override;
};

Piece &HumanPlayer::selectPiece(){
	std::string str = "";
	while(true){
		std::cout << "Enter a piece:";
		std::cin >> str;
		try{
			return pool->getUnusedPiece(str);
		}
		catch(InvalidInputException e){
			std::cout << e.what() << std::endl;
		}
		catch(UsedPieceException e){
			std::cout << e.what() << std::endl;
		}
	}
}

Square &HumanPlayer::selectSquare(const Piece &p){
	// std::cout << "haha\n";
	std::string str;
	while(true){
		// std::cout << "haha\n";
		std::cout << "Enter a position:";
		std::cin >> str;
		try{
			return board->getEmptySquare(str);
		}
		catch(InvalidInputException e){
			std::cout << e.what() << std::endl;
		}
		catch(SquareException e){
			std::cout << e.what() << std::endl;
		}	
	}
}

Piece & MyopicPlayer::selectPiece(){
	bool unused[NP] = {[0 ... NP-1] = false};
	bool bad[NP] = {[0 ... NP-1] = false};
	int count_unused = 0;
	int count_bad = 0;
	for(int i = 0; i < NP; i++){
		std::string str = std::string(1, HCODE[i/8]) + CCODE[(i%8)/4] + SCODE[(i%4)/2] + TCODE[i%2];
		try{
			Piece &p = pool->getUnusedPiece(str);
			unused[i] = true;
			count_unused++;
			for(int j = 0; j < N; j++){
				for(int k = 0; k < N; k++){
					Square &sq = board->getSquare(static_cast<Vaxis>(j), static_cast<Haxis>(k));
					if(board->isWinning(p, sq)){
						bad[i] = true;
					}
				}
			}
			if(bad[i]){
				count_bad++;
			}
		}
		catch(...){
			continue;
		}
	}
	std::cout << "haha\n";
	std::cout << count_bad << " " << count_unused << std::endl;
	if(count_bad != count_unused){
		int nth = std::rand()%(count_unused - count_bad) + 1;
		while(nth > 0){
			for(int i = 0; i < NP; i++){
				if(unused[i] && !bad[i]){
					nth--;
				}
				if(nth == 0){
					std::string str = std::string(1, HCODE[i/8]) + CCODE[(i%8)/4] + SCODE[(i%4)/2] + TCODE[i%2];
					return pool->getUnusedPiece(str);
				}
			}
		}	
	}
	else{
		int nth = std::rand()%count_bad + 1;
		while(nth > 0){
			for(int i = 0; i < NP; i++){
				if(unused[i] && bad[i]){
					nth--;
				}
				if(nth == 0){
					std::string str = std::string(1, HCODE[i/8]) + CCODE[(i%8)/4] + SCODE[(i%4)/2] + TCODE[i%2];
					return pool->getUnusedPiece(str);
				}
			}
		}
	}
	return pool->getUnusedPiece("");
}

Square & MyopicPlayer::selectSquare(const Piece &p){
	bool empty[N][N];
	int count = 0;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			Square &sq = board->getSquare(static_cast<Vaxis>(i), static_cast<Haxis>(j));
			if(sq.isEmpty() && board->isWinning(p, sq)){
				return sq;
			}
			empty[i][j] = sq.isEmpty();
			if (empty[i][j]){
				count++;
			}
		}
	}
	int nth = std::rand()%count + 1;
	while(nth > 0){
		for(int i = 0; i < N; i++){
			for(int j = 0; j < N; j++){
				if (empty[i][j]){
					nth--;
					if(nth == 0){
						return board->getSquare(static_cast<Vaxis>(i), static_cast<Haxis>(j));
					}
				}
			}
		}
	}
	return board->getEmptySquare("");
}

static HumanPlayer hplayer;
static MyopicPlayer mplayer;

extern Player *getHumanPlayer(Board *b, Pool *p){
	hplayer.set(b, p);
	return &hplayer;
}

extern Player *getMyopicPlayer(Board *b, Pool *p, unsigned int seed){
	mplayer.set(b, p, seed);
	return &mplayer;
}

















