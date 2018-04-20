//Author: Kostiantyn Makrasnov
//Program: Recursive Maze Solver (EX8_4)

#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include "Maze.h"

using std::string;
using std::queue;
using std::endl;
using std::cout;

Maze * maze;
std::stack<string> instructions;

//Recursive function that finds its way through the maze and outputs directions
//@param: x - horizontal index of current position
//@param: y - vertical index of current position
//@param: lastDir - what was the last action performed  (may revise to be ints - 1 = down | 2 = up | 3 = left | 4 = right)
//return: true if found the full path | false if dead end or no path exist at all
bool RunThruMaze(int x, int y, string lastDir = "enter maze") {

	//Base case (finish reached)
	if ((*maze).medium[y][x] == 2)
	{
		instructions.push(lastDir);
		return true;
	}

	//Get possible pathways
	queue<int> availPathsX;
	queue<int> availPathsY;
	queue<string> availPathsDir;
	if((lastDir != "down") && (y-1 != -1)) //checking up
		if ((*maze).medium[y-1][x] != 0)
		{
			availPathsX.push(x);
			availPathsY.push(y-1);
			availPathsDir.push("up");
		}
	if ((lastDir != "up") && (y+1 != (*maze).getMedMazeSize())) //checking down
		if ((*maze).medium[y+1][x] != 0)
		{
			availPathsX.push(x);
			availPathsY.push(y+1);
			availPathsDir.push("down");
		}
	if ((lastDir != "left") && (x+1 != (*maze).getMedMazeSize())) //checking right
		if ((*maze).medium[y][x+1] != 0)
		{
			availPathsX.push(x + 1);
			availPathsY.push(y);
			availPathsDir.push("right");
		}
	if ((lastDir != "right") && (x-1 != -1)) //checking left
		if ((*maze).medium[y][x-1] != 0)
		{
			availPathsX.push(x-1);
			availPathsY.push(y);
			availPathsDir.push("left");
		}

	//Dead end scenario - go back a step
	if (availPathsDir.empty())
		return false;

	//Intersection/Path scenario - delete paths one by one until correct one is found
	while (!RunThruMaze(availPathsX.front(), availPathsY.front(), availPathsDir.front()))
	{
		availPathsX.pop();
		availPathsY.pop();
		availPathsDir.pop();
		if (availPathsDir.empty())
			return false;
	}

	//Push correct instructions onto the stack
	instructions.push(lastDir);
	return true;
}

//Print the directions found for a maze (may rewrite stack during printing if need to save instructions)
void printDirections() {
	int stepCount = 1;
	while (!instructions.empty()) 
	{
		cout << stepCount << ". " << instructions.top() << endl;
		instructions.pop();
		stepCount++;
	}
}


int main() 
{
	maze = new Maze();

	//Perform the test maze escape
	//Start at the entrance of maze pos x is to the right, pos y down | initial pos - (x,y) | array access - [y][x]
	if (RunThruMaze(1, 0)) {
		(*maze).displayGrid();
		cout << "_____________________________" << endl;
		cout << "Maze exit successfully found!" << endl;
		printDirections();
	}
	else {
		cout << "_____________________________" << endl;
		cout << "Maze exit not fount! :(" << endl;
	}

	//Clear allocated memory
	delete maze;
	maze = NULL;

	return 0;
}