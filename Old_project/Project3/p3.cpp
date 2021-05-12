#include "simulation.h"
#include "world_type.h"
using namespace std;

int main(int argc, char const *argv[])
{
	// Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]
	try{
		if (argc < 4){
			error_t error;
			error.op = 1;
			throw error;
		}
		if (atoi(argv[3]) < 0){
			error_t error;
			error.op = 2;
			throw error;
		}

		bool print_mode = false; 
		// true means verbose, while false is concise
		if (argc >= 5){
			string print_flag = argv[4];
			if (print_flag == "v" || print_flag == "verbose")
				print_mode = true;
		}

		world_t world;
		initialize_world(world);
		read_species(world, argv[1]);
		read_world(world, argv[2]);
		run_game(world, atoi(argv[3]), print_mode);
		//test_read_success(world);
	}
	catch(error_t error){
		print_error(error);
	}
	return 0;
}












