#pragma once
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <Windows.h>


class CBoard
{
public:
	CBoard();
	~CBoard(void);

	void playGameOfLife(int mode);


private:
	char realBoard[24][75];
	char transitionBoard[24][75];
	char liveMarker;
	char deadMarker;
	int seedLevel;
	int sleepTime;

	void pullBoard(void);
	void seedBoard(int mode);
	void updateBoard(void);
	int checkCount(int x, int y);
	void printBoard(void);
	void wipeBoard(void);
};

