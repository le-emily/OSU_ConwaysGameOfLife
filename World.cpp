#include "World.h"

/*Constructor for World.
	Paramaters :
		option - Used to select the starting shape.
		startX - Used to set a starting X position.
		startY - Used to set a starting Y position.
	The starting shape and position, and game world is initialized here.
*/
World::World(int option, int startX, int startY){
	worldGrid.resize(COLS, vector<bool>(ROWS, 0));

	//Offset by 10. Starting position only for the visible world.
	startX = startX + 10;
	startY = startY + 10;

	//Initialize with Oscilator
	if (option == 1){
		for (int i = 0; i < 3; i++){
			worldGrid[startX + i][startY] = true;
		}
	}

	//Initialize with Glider
	else if (option == 2){
		for (int i = 0; i < 3; i++){
			worldGrid[startX + i][startY] = true;
			if (i == 1)
				worldGrid[startX + i][startY - 2] = true;
			if (i == 2)
				worldGrid[startX + i][startY - 1] = true;
		}
	}

	//Initialize with Glider Cannon
	else if (option == 3){
		worldGrid[startX][startY + 4] = true;
		worldGrid[startX + 1][startY + 4] = true;
		worldGrid[startX][startY + 5] = true;
		worldGrid[startX + 1][startY + 5] = true;

		worldGrid[startX + 10][startY + 4] = true;
		worldGrid[startX + 10][startY + 5] = true;
		worldGrid[startX + 10][startY + 6] = true;

		worldGrid[startX + 11][startY + 3] = true;
		worldGrid[startX + 11][startY + 7] = true;

		worldGrid[startX + 12][startY + 2] = true;
		worldGrid[startX + 12][startY + 8] = true;

		worldGrid[startX + 13][startY + 2] = true;
		worldGrid[startX + 13][startY + 8] = true;

		worldGrid[startX + 14][startY + 5] = true;

		worldGrid[startX + 15][startY + 3] = true;
		worldGrid[startX + 15][startY + 7] = true;

		worldGrid[startX + 16][startY + 4] = true;
		worldGrid[startX + 16][startY + 5] = true;
		worldGrid[startX + 16][startY + 6] = true;

		worldGrid[startX + 17][startY + 5] = true;

		worldGrid[startX + 20][startY + 2] = true;
		worldGrid[startX + 20][startY + 3] = true;
		worldGrid[startX + 20][startY + 4] = true;
		worldGrid[startX + 21][startY + 2] = true;
		worldGrid[startX + 21][startY + 3] = true;
		worldGrid[startX + 21][startY + 4] = true;

		worldGrid[startX + 22][startY + 1] = true;
		worldGrid[startX + 22][startY + 5] = true;

		worldGrid[startX + 24][startY ] = true;
		worldGrid[startX + 24][startY + 1] = true;
		worldGrid[startX + 24][startY + 5] = true;
		worldGrid[startX + 24][startY + 6] = true;

		worldGrid[startX + 34][startY + 2] = true;
		worldGrid[startX + 34][startY + 3] = true;
		worldGrid[startX + 35][startY + 2] = true;
		worldGrid[startX + 35][startY + 3] = true;
	}
	cout << "Done!" << endl;
}


/* displayGrid function
	Displays the grid. row and cols are offset by 10 so that only 40x20 is visible.
*/
void World::displayGrid(){
	cout << "\n\n\n\n\n";
	for (int i = 10; i < ROWS - 10; i++){
		for (int j = 10; j < COLS - 10; j++){
			if (!worldGrid[j][i])
				cout << ".";
			else if (worldGrid[j][i])
				cout << "*";
		}
		cout << "\n";
	}
}


/*	Update function
	Called to update 'worldGrid'. A new grid is created and 'worldGrid' is copied to it.
	All changes to the cells are first made in 'worldGridCpy'. Then when completed,
		'worldGrid' will be set to 'worldGridCpy'.
	The entire gridWorld is checked, including the non-visible rows and columns.
	This ensures that the shapes are properly following rules even if part of it is no
		longer visible. Each cell will be set to the value returned from the function 'applyRules()'
*/
void World::update(){
	vector<vector<bool> > worldGridCpy;
	worldGridCpy.resize(COLS, vector<bool>(ROWS, 0));
	worldGridCpy = worldGrid;

	for (int i = 0; i < ROWS; i++){
		for (int j = 0; j < COLS; j++){
			worldGridCpy[j][i] = applyRules(j, i);
		}
	}

	worldGrid = worldGridCpy;
}


/* getNeighbors function.
	Paramaters :
		x - the 'x' position of the cell being checked.
		y - the 'y' position of the cell being checked.
	Return the total number of neighbors.
	Neighbors are determined by the following : "...the cells directly above, below, to the right, to the left,
	diagonally above to the right and left, and diagonally below to the right and left."
	If the x or y position is 5 cells away from the visible grid then 0 is returned because it is
		far enough out of range of the visible grid to impact visible cells.
*/
int World::getNeighbors(int x, int y){
	if (x < 5 || x > 55)
		return 0;

	if (y < 5 || y > 35)
		return 0;

	int topLeftX = x - 1;
	int topLeftY = y - 1;
	int total = 0;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (i == 1 && j == 1)
				continue;
			else
				if (worldGrid[topLeftX + j][topLeftY + i])
					total++;
		}
	}

	return total;
}

/* applyRules function
	Paramaters :
		x - the 'x' position of the cell being checked.
		y - the 'y' position of the cell being checked.
	Returns a boolean indicating if the cell is dead or alive after the rule check.
	The rules are as follows :
	1.	If an occupied cell has zero or one neighbor, it dies of loneliness.
	2.	If an occupied cell has more than three neighbors, it dies of overcrowding.
	3.	If an empty cell has exactly three occupied neighbor cells, there is a birth of a new cell to replace the empty cell.
	4.	Births and deaths are instantaneous and occur at the changes of generation.
*/
bool World::applyRules(int x, int y){
	int neighbors = getNeighbors(x, y);

	//Check if cell is occupied to apply rules 1 and 2
	if (worldGrid[x][y] == true){
		//1.If an occupied cell has zero or one neighbor, it dies of loneliness.
		if (neighbors <= 1)
			return false;
		//2.If an occupied cell has more than three neighbors, it dies of overcrowding.
		if (neighbors > 3)
			return false;
		else
			return true;
	}
	//3.If an empty cell has exactly three occupied neighbor cells, there is a birth of a new cell to replace the empty cell.
	if (worldGrid[x][y] == false){
		if (neighbors == 3)
			return true;
		else
			return false;
	}

	return false;
}
