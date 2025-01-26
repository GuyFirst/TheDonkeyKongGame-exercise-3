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
void reportResultError(const std::string& message, const std::string& filename, size_t iteration) {
	system("cls");
	std::cout << "Screen " << filename << " - " << message << '\n';
	std::cout << "Iteration: " << iteration << '\n';
	std::cout << "Press any key to continue to next screens (if any)" << std::endl;
	_getch();
}
void reportResult(const std::string& message) {
	system("cls");
	std::cout << message << std::endl;
	std::cout << "Press any key to continue to next screens (if any)" << std::endl;
	_getch();
}
