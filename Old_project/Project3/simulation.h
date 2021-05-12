#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "world_type.h"

typedef struct error_type{
	error_type():
		op(-1), str1(""), str2(""), grid(nullptr), creatures(nullptr){
	};
	int op;
	string str1;
	string str2;
	const grid_t *grid;
	const creature_t *creatures;
	const creature_t *creatures_later;
}error_t;

void print_error(const error_t &error);
void print_creature_error(const creature_t *creatures);

void read_species(world_t &world, string summary_dir);
void read_instructions(species_t &species, string summary_dir);
opcode_t trans_(string tmp);
void read_world(world_t &world, string world_dir);
species_t *wao(world_t &world, string kind);
direction_t trans(string l);
void run_game(world_t &world, int rounds, bool print_mode);
void print_world(const world_t &world, int rounds, bool print_mode);

void test_read_success(const world_t &world);
void print_species(const species_t &species);
void print_creatures(const creature_t &creatures);
void print_grid(const grid_t &grid);

void initialize_world(world_t &world);
void initialize_species(species_t &species);
void initialize_creatures(creature_t &creatures);
void initialize_grid(grid_t &grid);

#endif

