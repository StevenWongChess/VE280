#include "simulation.h"
#include "world_type.h"
using namespace std;

void error_print(){

		cout << "Error: Missing arguments!\n
			Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]\n";

		cout << "Error: Number of simulation rounds is negative!\n";

//		cout << "Error: Cannot open file " <<  << "!\n";

		cout << "Error: Too many species!\n
			 Maximal number of species is " << MAXSPECIES << ".\n";

}
















