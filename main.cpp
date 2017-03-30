#include "Board.h"

void printMenu(void);
int getChoice(void);

int main (void){

	CBoard board;
	int choice = 0;
	bool runMenu = true;
	while (runMenu){
		printMenu();
		choice = getChoice();

		switch(choice){
		case 1:
			board.playGameOfLife(1);
			system("PAUSE");
			break;
		case 2:
			board.playGameOfLife(2);
			system("PAUSE");
			break;
		case 3:
			runMenu = false;
			break;
		}
		
	}

	return 0;
}

void printMenu(void){
	printf("%s",std::string(25,'\n').c_str());
	printf("Conway's Game of Life\n");
	printf("**********************\n");
	printf(" 1 - Random Mode\n");
	printf(" 2 - Flyer Demo\n");
	printf(" 3 - Quit\n");
	printf("**********************\n");
	printf("Command: ");
}

int getChoice(void){
	int temp = 0;

	while(true){
		std::cin >> temp;
		if ((temp < 1)||(temp > 3)){
			std::cin.clear();
			std::cin.ignore(INT_MAX,'\n');
		} else {
			return temp;
		}
	}
}