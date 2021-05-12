#include "simulation.h"
using namespace std;

void print_error(const error_t &error){
	switch(error.op){
	case 1:
		cout << "Error: Missing arguments!\n"
		     << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]\n";
		break;
	case 2:
		cout << "Error: Number of simulation rounds is negative!\n";
		break;
	case 3:
		cout << "Error: Cannot open file " << error.str1 << "!\n";
		break;
	case 4:
		cout << "Error: Too many species!\n"
		 	 << "Maximal number of species is " << MAXSPECIES << ".\n";
		break;
	case 5:
		cout << "Error: Too many instructions for species " << error.str1 << "!\n"
			 << "Maximal number of instructions is " << MAXPROGRAM << ".\n";
		break;
	case 6:
		cout << "Error: Instruction " << error.str1 << " is not recognized!\n";
		break;
	case 7:
		cout << "Error: Too many creatures!\n" 
			 << "Maximal number of creatures is " << MAXCREATURES <<".\n";
		break;
	case 8:
		cout << "Error: Species " << error.str1 << " not found!\n";
		break;
	case 9:
		cout << "Error: Direction " << error.str1 << " is not recognized!\n";
		break;
	case 10:
		cout << "Error: The grid height is illegal!\n";
		break;
	case 11:
		cout << "Error: The grid width is illegal!\n";
		break;
	case 12:
		cout << "Error: Creature ";
		print_creature_error(error.creatures);
		cout << " is out of bound!\n";
		cout << "The grid size is " << error.grid->height 
			 << "-by-" << error.grid->width << ".\n";
		break;
	case 13:
		cout << "Error: Creature ";
		print_creature_error(error.creatures_later);
		cout << " overlaps with creature ";
		print_creature_error(error.creatures);
		cout << "!\n";
		break;
	default:
		break;
	}
}

void print_creature_error(const creature_t *creatures){
	cout << "(" << creatures->species->name
		 << " " << directName[creatures->direction]
		 << " " << creatures->location.r
		 << " " << creatures->location.c
		 << ")";
}

void read_species(world_t &world, string summary_dir){
	ifstream summary_if;
	summary_if.open(summary_dir);
	if(!summary_if.is_open()){
		error_t error;
		error.op = 3;
		error.str1 = summary_dir;
		throw error;	
	}
	string upper_dir;
	getline(summary_if, upper_dir);
	string species_dir;
	while(getline(summary_if, species_dir)){
		if(world.numSpecies >= MAXSPECIES){
			error_t error;
			error.op = 4;
			throw error;
		}
		istringstream iStream;
		iStream.str(species_dir);
		string file_name;
		iStream >> file_name;
		world.species[world.numSpecies].name = file_name;
		read_instructions(world.species[world.numSpecies], upper_dir);
		world.numSpecies ++;
	}

	summary_if.close();
}

void read_instructions(species_t &species, string upper_dir){
	ifstream species_if;
	string full_dir = upper_dir + "/" + species.name;
	species_if.open(full_dir);
	if(!species_if.is_open()){
		error_t error;
		error.op = 3;
		error.str1 = full_dir;
		throw error;	
	}
	string line;
	while(getline(species_if, line)){
		if (line == "")
			break;
		if (species.programSize >= MAXPROGRAM){
			error_t error;
			error.op = 5;
			error.str1 = species.name;
			throw error;
		}
		istringstream iStream;
		iStream.str(line);
		string tmp;
		iStream >> tmp
				>> species.program[species.programSize].address;
		//transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
		species.program[species.programSize].op = trans_(tmp);
		species.programSize ++;
	}
	species_if.close();
}

opcode_t trans_(string tmp){
	for(auto i = 0; i < 9; i++){
		if (opName[i] == tmp)
			return static_cast<opcode_t>(i);
	}
	error_t error;
	error.op = 6;
	error.str1 = tmp;
	throw(error);
}

void read_world(world_t &world, string world_dir){
	ifstream world_if;
	world_if.open(world_dir);
	if(!world_if.is_open()){
		error_t error;
		error.op = 3;
		error.str1 = world_dir;
		throw error;	
	}
	world_if >> world.grid.height >> world.grid.width;
	if(world.grid.height > MAXHEIGHT || world.grid.height < 1){
		error_t error;
		error.op = 10;
		throw error;
	}
	if(world.grid.width > MAXWIDTH || world.grid.width < 1){
		error_t error;
		error.op = 11;
		throw error;
	}

	string line = "";
	getline(world_if, line);
	while(getline(world_if, line)){
		if(world.numCreatures >= MAXCREATURES){
			error_t error;
			error.op = 7;
			throw error;	
		}
		istringstream iStream;
		iStream.str(line);
		string direction_tmp;
		string kind;
		iStream >> kind
				>> direction_tmp
		 		>> world.creatures[world.numCreatures].location.r
		 		>> world.creatures[world.numCreatures].location.c;
		world.creatures[world.numCreatures].species = wao(world, kind);
		world.creatures[world.numCreatures].direction = trans(direction_tmp);
		if(world.creatures[world.numCreatures].location.r >= world.grid.height || 
		   world.creatures[world.numCreatures].location.c >= world.grid.width){
			error_t error;
			error.op = 12;
			error.grid = &world.grid;
			error.creatures = &world.creatures[world.numCreatures];
			throw error;
		}
		if (world.grid.squares[world.creatures[world.numCreatures].location.r]
						  	  [world.creatures[world.numCreatures].location.c] != nullptr){
			error_t error;
			error.op = 13;
			error.creatures = world.grid.squares[world.creatures[world.numCreatures].location.r]
						  	  									[world.creatures[world.numCreatures].location.c];
			error.creatures_later = &world.creatures[world.numCreatures];
			throw error;
		}

		world.grid.squares[world.creatures[world.numCreatures].location.r]
						  [world.creatures[world.numCreatures].location.c] 
						  = &world.creatures[world.numCreatures];
		world.numCreatures ++;
	}
	world_if.close();
}

species_t *wao(world_t &world, string kind){
	for(int i = 0; i < world.numSpecies; i++){
		if (kind == world.species[i].name)
			return &world.species[i];
	}
	error_t error;
	error.op = 8;
	error.str1 = kind;
	throw error;
}

direction_t trans(string l){
	if (l == "east"){
		return EAST;
	}
	if (l == "south"){
		return SOUTH;
	}
	if (l == "west"){
		return WEST;
	}
	if (l == "north"){ 
		return NORTH;
	}
	error_t error;
	error.op = 9;
	error.str1 = l;
	throw error;
}

void run_game(world_t &world, int rounds, bool print_mode){
	cout << "Initial state\n";
	print_grid(world.grid);
	//print_grid(world.grid, print_mode);
	for(int i = 0; i < rounds; i++){
		cout << "Round " << i + 1 << endl;
		for(int j = 0; j < world.numCreatures; j++){
			action(world.creatures[j], world.grid);		
		}
		print_grid(world.grid);
		//print_grid(world.grid, print_mode);
	}
}

void print_grid(const grid_t &grid, bool print_mode){

}

void action(creature_t &creature, grid_t &grid){
	bool flag = true;
	while(flag){
		switch (creature.species->program[creature.programID].op){
		case HOP:
			if(ifempty(creature, grid)){
				grid.squares[front(creature).r][front(creature).c] = &creature;
				grid.squares[creature.location.r][creature.location.c] = nullptr;
				creature.location = front(creature);
			}
			jump(creature, false);
			flag = false;
			break;
		case LEFT:
			creature.direction = static_cast<direction_t>((creature.direction - 1) % NUM_DIRECTIONS);
			jump(creature, false);
			flag = false; 
			break;
		case RIGHT:
			creature.direction = static_cast<direction_t>((creature.direction + 1) % NUM_DIRECTIONS); 
			jump(creature, false);
			flag = false;
			break;
		case INFECT:
			if(ifenemy(creature, grid)){
				grid.squares[front(creature).r][front(creature).c]->species = creature.species;
				grid.squares[front(creature).r][front(creature).c]->programID = 0;
			}
			jump(creature, false);
			flag = false;
			break;
		case IFEMPTY:
			jump(creature, ifempty(creature, grid));	
			break;
		case IFWALL:
			jump(creature, ifwall(creature, grid));
			break;
		case IFENEMY:
			jump(creature, ifenemy(creature, grid));
			break;
		case IFSAME:
			jump(creature, ifsame(creature, grid));
			break;
		case GO:
			jump(creature, true);
			break;
		default:
			break;
		}
	}
}

point_t front(const creature_t &creature){
	direction_t dir = creature.direction;
	point_t pt = creature.location;
	point_t pt_front = pt;
	if (dir == EAST){
		pt_front.c ++;
	}
	if (dir == SOUTH){
		pt_front.r ++;
	}
	if (dir == WEST){
		pt_front.c --;
	}
	if (dir == NORTH){
		pt_front.r --;
	}
	return pt_front;
}

void jump(creature_t &creature, bool flag){
	creature.programID = flag ? (creature.species->program[creature.programID].address - 1) : (creature.programID + 1);
}

bool ifwall(const creature_t &creature, const grid_t &grid){
	return front(creature).r < 0 
		|| front(creature).r >= grid.height
		|| front(creature).c < 0 
		|| front(creature).c >= grid.width;
}

bool ifempty(const creature_t &creature, const grid_t &grid){
	return !ifwall(creature, grid) && grid.squares[front(creature).r][front(creature).c] == nullptr;
}

bool ifenemy(const creature_t &creature, const grid_t &grid){
	return !ifempty(creature, grid) && creature.species != grid.squares[front(creature).r][front(creature).c]->species;
}

bool ifsame(const creature_t &creature, const grid_t &grid){
	return !ifempty(creature, grid) && creature.species == grid.squares[front(creature).r][front(creature).c]->species;
}

/************************ test *********************************/

void test_read_success(const world_t &world){
	cout << world.numSpecies << " species in the world\n";
	for(int i = 0; i < world.numSpecies; i++){
		//print_species(world.species[i]);
	}
	cout << world.numCreatures << " creatures in the world\n";
	for(int i = 0; i < world.numCreatures; i++){
		print_creatures(world.creatures[i]);
	}
	print_grid(world.grid);
}

void print_species(const species_t &species){
	cout << "species name is " << species.name
		 << ", program size is " << species.programSize << endl;
	for(int i = 0; i < species.programSize; i ++){
		cout << opName[species.program[i].op] << " " << species.program[i].address << endl;
	}
}	

void print_creatures(const creature_t &creatures){
	cout << "creature location is (" << creatures.location.r << "," 
		 << creatures.location.c << "), " 
		 << "direction is " << directName[creatures.direction] << ", ";
	// if(creatures.species != NULL)
	// 	print_species(*creatures.species);
	cout << "program id is " << creatures.programID << endl;
}

void print_grid(const grid_t &grid){
	cout << "grid size is " << grid.height << "*" << grid.width << endl;
	for(int i = 0; i < grid.height; i++){
		for(int j = 0; j < grid.width; j++){
			if (grid.squares[i][j] != nullptr)
				print_creatures(*grid.squares[i][j]);
		}
	}
}

/******************** initialization **********************/

void initialize_world(world_t &world){
	world.numSpecies = 0;
	for(int i = 0; i < MAXSPECIES; i++){
		initialize_species(world.species[i]);
	}
	world.numCreatures = 0;
	for(int i = 0; i < MAXCREATURES; i++){
		initialize_creatures(world.creatures[i]);
	}
	initialize_grid(world.grid);
}

void initialize_species(species_t &species){
	species.name = "";
	species.programSize = 0;
	for(int i = 0; i < MAXPROGRAM; i++){
		species.program[i] = instruction_t{HOP, 0};
	}
}

void initialize_creatures(creature_t &creatures){
	creatures.location = point_t{0, 0};
	creatures.direction = EAST;
	creatures.species = nullptr;
	creatures.programID = 0;
}

void initialize_grid(grid_t &grid){
	grid.height = 0;
	grid.width = 0;
	for(int i = 0; i < MAXHEIGHT; i++){
		for(int j = 0; j < MAXWIDTH; j++){
			grid.squares[i][j] = nullptr;
		}
	}
}







