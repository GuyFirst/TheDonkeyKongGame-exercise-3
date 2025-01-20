#include "gameConfig.h"
#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
#include <conio.h>


void gotoxy(int x, int y) {

	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void clrsrc()
{
	system("cls");
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void clearBuffer()
{
	while (_kbhit())
		char garbage = _getch();
}

void printSlow(int delay, const std::string& text)
{
	for (size_t i = 0; i < text.length(); ++i) {
		std::cout << text[i];
		std::cout.flush();  // Ensures the character is printed immediately
		Sleep(delay);  // Delay in milliseconds
	}
}

