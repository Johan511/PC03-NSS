#pragma once

#include <stdio.h>
namespace namespace_organism
{
	struct cordinates2D
	{
		int x;
		int y;
	};

	struct speed_structure
	{
		int *speed_list;
		// list of numbers which on averaging gives speed.
		// Example : [1,1,2,3] => avg speed would be 1.75
		// we can choose how many steps to move per iteration using random or RR
		int len_of_speed_list;
		int rr_count;
		// round robin count in case we use it
		// rr_count needs to be lower than len_of_speed_list always
	};

	class Organism
	{

	private:
		// add reference to unvierse
		struct cordinates2D position;
		struct speed_structure organism_speed;

		int vision_radius;
		int max_energy;
		int current_energy;
		unsigned short int aadhar_number; // name of organism like John Doe
		int speciesID;

	public:
		Organism(int x, int y, int vision_radius, int *speed_list, int length_of_speed_list, int max_energy, int current_energy, unsigned short int aadhar_number, int speciesID);
		~Organism();
		int get_x() { return position.x; };										 // kumeresan
		int get_y() { return position.y; };										 // kumeresan
		int get_vision_radius() { return vision_radius; };						 // kumeresan
		struct speed_structure get_speed_structure() { return organism_speed; }; // kumeresan
		int get_max_energy() { return max_energy; };							 // kumeresan
		int get_current_energy() { return current_energy; };					 // kumeresan
		unsigned short int get_aadhar_number() { return aadhar_number; };		 // kumeresan
		int get_speciesID();
	};

	class Insect : public Organism
	{

	private:
		int organism_ID;

	public:
		Insect(int x, int y, int vision_radius, int *speed_list, int length_of_speed_list, int max_energy, int current_energy, unsigned short int aadhar_number, int organism_ID1, int speciesID);
		~Insect();
		int get_organism_ID();
	};

	class Plant : public Organism
	{

	public:
		Plant(int x, int y, int vision_radius, int *speed_list, int length_of_speed_list, int max_energy, int current_energy, unsigned short int aadhar_number, int speciesID);
	};
}