#include "World.h"
#include <iostream>
#include <stdio.h>

int main(){
	int shape = 0;
	int xPos = 0;
	int yPos = 0;
	char c = 'c';
	//Starting Menu
	cout << "Conway's Game of Life" << endl;
	cout << "---------------------" << endl;
	cout << "Starting Shapes" << endl;
	cout << "1: Oscillator" << endl;
	cout << "2: Glider" << endl;
	cout << "3: Glider Cannon" << endl;
	cout << "---------------------" << endl;
	cout << "Pick starting shape : " << endl;
	cin >> shape;

	//User selects shape.
	while (shape < 1 || shape > 3){
		cout << "Invalid Option. Pick starting shape : " << endl;
		cin >> shape;
	}

	//User selects starting X position for shape within a valid range.
	cout << "Input starting X position ";
	if (shape == 1 || shape == 2){
		cout << "between 1 - 38. " << endl;
		cin >> xPos;
		while (xPos < 1 || xPos > 38){
			cout << "Invalid position. Input between 1-38." << endl;
			cin >> xPos;
		}
	}

	if (shape == 3){
		cout << "between 1 - 5 so that it fits on the display. " << endl;
		cin >> xPos;
		while (xPos < 1 || xPos > 5){
			cout << "Invalid position. Input between 1-5." << endl;
			cin >> xPos;
		}
	}

	//User selects a starting Y position within a valid range.
	cout << "Input starting Y position ";
	if (shape == 1){
		cout << "between 1 - 20. " << endl;
		cin >> yPos;
		while (yPos < 1 || yPos > 20){
			cout << "Invalid position. Input between 1-20." << endl;
			cin >> yPos;
		}
	}

	if (shape == 2){
		cout << "between 3 - 20. " << endl;
		cin >> yPos;
		while (yPos < 3 || yPos > 20){
			cout << "Invalid position. Input between 3-20." << endl;
			cin >> yPos;
		}
	}

	if (shape == 3){
		cout << "between 1 - 11 so that it fits on the display. " << endl;
		cin >> yPos;
		while (yPos < 1 || yPos > 11){
			cout << "Invalid position. Input between 1-11." << endl;
			cin >> yPos;
		}
	}

	cout << "Initializing... " << endl;

	//Initialize the 'world' with the users selected options. Offset by -1 for both x and y since (0,0 = 1)
	World world(shape, xPos-1, yPos-1);

	//Game loop : Outputs the visible grid and updates the grid after the user presses a key until '0' is pressed.

	while (c != '0'){
		world.displayGrid();
		cout << "Input or any key to continue or '0' to exit.";
		world.update();
		c = getchar();
	}

	return 0;
}
