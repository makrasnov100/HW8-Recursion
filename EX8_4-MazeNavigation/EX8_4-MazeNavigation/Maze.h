//Author:Kostiantyn Makrasnov
//Maze definitions

#ifndef MAZE_H
#define MAZE_H

#include <windows.h> 
#include <iostream>

using std::cout;
using std::endl;

HANDLE hStdout, hStdin;

class Maze {
private:
	const int MED_MAZE_SIZE = 10;
	CONSOLE_SCREEN_BUFFER_INFO Info;
	HANDLE hStdout;
	WORD defaultConsoleAppearance;

public:
	Maze() {
		//Adapted from https://technet.microsoft.com/en-us/windows/ms686974(v=vs.60)
		//"Quick" way to get custom color in console
		hStdin = GetStdHandle(STD_INPUT_HANDLE);
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdin == INVALID_HANDLE_VALUE ||
			hStdout == INVALID_HANDLE_VALUE)
		{
			MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"),
				MB_OK);
		}
		//Adapted from https://stackoverflow.com/questions/25559077/how-to-get-background-color-back-to-previous-color-after-use-of-std-handle
		//Save original console appearence
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hStdout, &Info);
		defaultConsoleAppearance = Info.wAttributes;
	}

	int medium[10][10] = {{0,1,0,0,0,0,0,0,0,0},
					      {0,1,0,1,0,1,0,1,0,0},
					      {0,1,1,1,0,1,1,1,1,0},
				          {0,1,0,1,0,0,0,1,0,0},
				          {0,1,0,1,1,1,0,1,0,0},
				          {0,1,0,0,0,0,0,1,0,0},
				          {0,1,1,1,1,1,1,1,0,0},
				          {0,0,1,0,0,0,0,1,0,0},
					      {0,1,1,1,0,1,1,1,1,0},
					      {0,0,0,0,0,2,0,0,0,0}};


	//Draws out the defined maze defined above
	void displayGrid()
	{
		for (int y = 0; y < MED_MAZE_SIZE; y++) 
		{
			for (int x = 0; x < MED_MAZE_SIZE; x++) 
			{
				if (medium[y][x] == 0) {
					SetConsoleTextAttribute(hStdout, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY); //walls
					cout << " 0 ";
				}
				else if (medium[y][x] == 1) {
					SetConsoleTextAttribute(hStdout, BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY); //paths
					cout << " 1 ";
				}
				else {
					SetConsoleTextAttribute(hStdout, BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY); //finish
					cout << " F ";
				}
			}
			cout << endl;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultConsoleAppearance);
	}

	//Assesor more maze size constant
	int getMedMazeSize() {
		return MED_MAZE_SIZE;
	}
};

#endif
