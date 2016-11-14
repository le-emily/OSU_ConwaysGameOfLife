//World Class: All of the core functions which run Conway's Game of life
//	are here. Constructor takes input to initialize the 'world' with specific shape
//	and starting position. 
#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <iostream>
using namespace std;

//Visible grid size will be 40x20. +20 for non-visible cells on all sides.
const int COLS = 60;
const int ROWS = 40;

class World
{
public:
	World(int option, int startX, int startY);

	void displayGrid();
	void update();
	int getNeighbors(int x, int y);
	bool applyRules(int x, int y);

private:
	//worldGrid is a 2d vector of bools which contains the 'world'
	vector<vector<bool> >worldGrid;
};

#endif //WORLD_H