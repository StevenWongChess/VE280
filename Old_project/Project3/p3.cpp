#include "simulation.h"
#include "world_type.h"
using namespace std;

int main(int argc, char const *argv[])
{
	try{
		string summary_dir = argv[1];
		string world_dir = argv[2];
		int rounds = atoi(argv[3]);

		bool print_mode = false; 
		// true means verbose, while false is concise
		if (argc >= 5){
			string print_flag = argv[4];
			if (print_flag == "v" || print_flag == "verbose")
				print_mode = true;
		}
		ifstream summary_if;
		ifstream world_if;
		summary_if.open(argv[1]);
		world_if.open(argv[2]);

		

		print_world(, rounds, print_mode);

		summary_if.close();
		world_if.close();
	}
	catch(...){
		//error_print();
	}

	return 0;
}














