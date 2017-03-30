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
	//Mode: 1 = random, 2 = demonstration

private:
	char realBoard[24][75];
	char transitionBoard[24][75];
	char liveMarker;
	char deadMarker;
	int seedLevel;
	int sleepTime;

	int liveLowerBound;
	int liveUpperBound;
	int deadRevive;

	void pullBoard(void);
	void seedBoard(int mode);
	//Mode: 1 = random, 2 = demonstration
	void updateBoard(void);
	int checkCount(int x, int y);
	void printBoard(void);
	void wipeBoard(void);
};

