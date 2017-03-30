#include "Board.h"


CBoard::CBoard()
{
	liveMarker = 'O';
	deadMarker = ' ';
	/*Seed Level will determine odds of a
	cell being dead when board is seeded*/
	seedLevel = 75;
	/*Sleep Time is the time in miliseconds
	between update-print cylces. Intended to
	make viewing easier*/
	sleepTime = 200;

	/*Three Rules:
	If cell is Live:
	 1- count < liveLowerBound, cell dies
	 2- count > liveUpperBound, cell dies
	If cell is Dead:
	 3- count == deadRevive, cell lives
	*/
	liveLowerBound = 2; //Standard is 2
	liveUpperBound = 3; //Standard is 3
	deadRevive = 3;     //Standard is 3
}


CBoard::~CBoard(void)
{
}

//Mode: 1 = random, 2 = demonstration
void CBoard::playGameOfLife(int mode){
	seedBoard(mode);
	pullBoard();
	for (int i = 0; i < 200; i++){
		updateBoard();
		pullBoard();
		printBoard();
		Sleep(sleepTime);
	}
	wipeBoard();
	pullBoard();
}

void CBoard::pullBoard(void){
	for (int i = 0; i < 24; i++){
		for (int j = 0; j < 75; j++){
			realBoard[i][j] = transitionBoard[i][j];
		}
	}
}

//Mode: 1 = random, 2 = demonstration
void CBoard::seedBoard(int mode){
	if (mode == 1){
		int temp = 0;
		std::mt19937 randGen(time(NULL));
		std::uniform_int_distribution<int> roll(1,100);

		for (int i = 0; i < 24; i++){
			for (int j = 0; j < 75; j++){
				temp = roll(randGen);
				if (temp >= seedLevel){
					transitionBoard[i][j] = liveMarker;
				} else {
					transitionBoard[i][j] = deadMarker;
				}
			}
		}
	} else if (mode == 2) {
		for (int i = 0; i < 24; i++){
			for (int j = 0; j < 75; j++){
				transitionBoard[i][j] = deadMarker;
			}
		}
		transitionBoard[7][24] = liveMarker;
		transitionBoard[7][25] = liveMarker;
		transitionBoard[7][35] = liveMarker;
		transitionBoard[7][36] = liveMarker;
		transitionBoard[8][23] = liveMarker;
		transitionBoard[8][25] = liveMarker;
		transitionBoard[8][35] = liveMarker;
		transitionBoard[8][36] = liveMarker;
		transitionBoard[9][1] = liveMarker;
		transitionBoard[9][2] = liveMarker;
		transitionBoard[9][10] = liveMarker;
		transitionBoard[9][11] = liveMarker;
		transitionBoard[9][23] = liveMarker;
		transitionBoard[9][24] = liveMarker;
		transitionBoard[10][1] = liveMarker;
		transitionBoard[10][2] = liveMarker;
		transitionBoard[10][9] = liveMarker;
		transitionBoard[10][11] = liveMarker;
		transitionBoard[11][9] = liveMarker;
		transitionBoard[11][10] = liveMarker;
		transitionBoard[11][17] = liveMarker;
		transitionBoard[11][18] = liveMarker;
		transitionBoard[12][17] = liveMarker;
		transitionBoard[12][19] = liveMarker;
		transitionBoard[13][17] = liveMarker;
		transitionBoard[14][36] = liveMarker;
		transitionBoard[14][37] = liveMarker;
		transitionBoard[15][36] = liveMarker;
		transitionBoard[15][38] = liveMarker;
		transitionBoard[16][36] = liveMarker;
		transitionBoard[19][25] = liveMarker;
		transitionBoard[19][26] = liveMarker;
		transitionBoard[19][27] = liveMarker;
		transitionBoard[20][25] = liveMarker;
		transitionBoard[21][26] = liveMarker;
	}
}

void CBoard::updateBoard(void){
	for (int i = 0; i < 24; i++){
		for (int j = 0; j < 75; j++){
			int count = checkCount(j,i);
			if (realBoard[i][j] == liveMarker){
				if ((count < liveLowerBound)||(count > liveUpperBound)){
					transitionBoard[i][j] = deadMarker;
				}
			} else {
				if (count == deadRevive){
					transitionBoard[i][j] = liveMarker;
				}
			}
		}
	}
}

//X and Y: denotes a cell in the realBoard array = realBoard[y][x]
int CBoard::checkCount(int x, int y){
	int count = 0;

	if (x == 0){
		if (y == 0){
			if (realBoard[y][x+1] == liveMarker){count++;}
			if (realBoard[y+1][x] == liveMarker){count++;}
			if (realBoard[y+1][x+1] == liveMarker){count++;}
		} else if (y == 23) {
			if (realBoard[y][x+1] == liveMarker){count++;}
			if (realBoard[y-1][x] == liveMarker){count++;}
			if (realBoard[y-1][x+1] == liveMarker){count++;}
		} else {
			if (realBoard[y-1][x] == liveMarker){count++;}
			if (realBoard[y-1][x+1] == liveMarker){count++;}
			if (realBoard[y][x+1] == liveMarker){count++;}
			if (realBoard[y+1][x+1] == liveMarker){count++;}
			if (realBoard[y+1][x] == liveMarker){count++;}
		}
	} else if (x == 74) {
		if (y == 0){
			if (realBoard[y][x-1] == liveMarker){count++;}
			if (realBoard[y+1][x] == liveMarker){count++;}
			if (realBoard[y+1][x-1] == liveMarker){count++;}
		} else if (y == 23) {
			if (realBoard[y][x-1] == liveMarker){count++;}
			if (realBoard[y-1][x] == liveMarker){count++;}
			if (realBoard[y-1][x-1] == liveMarker){count++;}
		} else {
			if (realBoard[y-1][x] == liveMarker){count++;}
			if (realBoard[y-1][x-1] == liveMarker){count++;}
			if (realBoard[y][x-1] == liveMarker){count++;}
			if (realBoard[y+1][x-1] == liveMarker){count++;}
			if (realBoard[y+1][x] == liveMarker){count++;}
		}
	} else if ((x > 0)&&(x < 74)&&(y == 0)){
		if (realBoard[y][x-1] == liveMarker){count++;}
		if (realBoard[y+1][x-1] == liveMarker){count++;}
		if (realBoard[y+1][x] == liveMarker){count++;}
		if (realBoard[y+1][x+1] == liveMarker){count++;}
		if (realBoard[y][x+1] == liveMarker){count++;}
	} else if ((x > 0)&&(x < 74)&&(y == 23)){
		if (realBoard[y][x-1] == liveMarker){count++;}
		if (realBoard[y-1][x-1] == liveMarker){count++;}
		if (realBoard[y-1][x] == liveMarker){count++;}
		if (realBoard[y-1][x+1] == liveMarker){count++;}
		if (realBoard[y][x+1] == liveMarker){count++;}
	}else {
		if (realBoard[y-1][x] == liveMarker){count++;}
		if (realBoard[y-1][x-1] == liveMarker){count++;}
		if (realBoard[y][x-1] == liveMarker){count++;}
		if (realBoard[y+1][x-1] == liveMarker){count++;}
		if (realBoard[y+1][x] == liveMarker){count++;}
		if (realBoard[y+1][x+1] == liveMarker){count++;}
		if (realBoard[y][x+1] == liveMarker){count++;}
		if (realBoard[y-1][x+1] == liveMarker){count++;}
	}
	return count;
}

void CBoard::printBoard(void){
	printf("%s",std::string(25,'\n').c_str());
	for (int i = 0; i < 24; i++){
		for (int j = 0; j < 75; j++){
			printf("%c",realBoard[i][j]);
		}
		printf("\n");
	}
}

void CBoard::wipeBoard(void){
	for (int i = 0; i < 24; i++){
		for (int j = 0; j < 75; j++){
			transitionBoard[i][j] = deadMarker;
		}
	}
}