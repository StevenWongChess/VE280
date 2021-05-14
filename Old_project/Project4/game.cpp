#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>
#include "piece.h"
#include "square.h"
using namespace std;

int main(int argc, char const *argv[])
{
	Piece a(SHORT, SEPIA, SQUARE, HOLLOW);
	Square b(B, H3);
	cout << b.getV() << " " << b.getH() << endl;
	cout << b.isOnSecondDiagonal() << endl;
	cout << b.toString() << endl;

	return 0;
}









