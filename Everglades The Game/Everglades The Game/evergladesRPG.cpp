/*
	Brian Durin, Jayde Shaw, Kim Claros

	evergladesRPG.cpp

	A text-based RPG in which a player traverses a 5x5 two-dimensional array
	to rescue a group of lost tourists before time runs out.

	Input:	initial menu choice, cell values, danger-related decisions

	Processing:	1 -	display initial menu and prompt user for choice
		2 - drive menu options
			1. Display game rules
			2. Start game
					Display map and gong countdown
					Prompt player (R) for next move
						If danger is generated in next cell:
							Prompt user for choice: wait or fight
					Continue until time runs out or player reaches
					the tourists (T)
			3 - Quit

	Output:	1 - Game Rules
			2 - Everglades 5 x 5 map, countdown, and player consequences
*/

		/*
			TO DO LIST	(erase when complete)

			- dispMap()
				- replace 4 rows of cout with a for loop
					already tried this and i don't think it's compatible with
					updating ranger (R) placement
		*/

// Header files
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// Global constants
const int MAP = 5;						// size of map matrix

// Function prototypes
void gameRules();
void genDangers(int[][MAP]);			// generate dangers wit rand() function 
void dispMap(char[][MAP]);
int validateMove(int, int, int, int);
void inDanger(char[][MAP], int, int, int&, int&, int&, char&);

int main()
{
	// Constants and Variables
	int menuChoice, row, col, error;
	int x = 0;				// previous row, initialized to starting placement
	int y = 0;				// previous column
	string move = "\nWhich adjacent cell would you like to move to?\n(row & column): ";
	char everglades[MAP][MAP] = { {' ', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', ' '} };
	char ranger = 'R', tourist = 'T';
	// int equivalent array holding location of dangers
	int key[MAP][MAP] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};		
				
	// Intro
	cout << "\n\tLost in the Everglades" << endl
		<< "\t\tTHE GAME" << endl;

	// Driving the menu and prompting user for choice
	do
	{
		int gong = 12;		// gong counter
		
		// display menu
		cout << "\nChoose one of the following options:" << endl
			<< "\n\t1 - See Rules" << endl
			<< "\t2 - Play Game" << endl
			<< "\t3 - Quit" << endl
			<< "\nYour choice: ";
		cin >> menuChoice;

		switch (menuChoice)
		{

		case 1:		// rules

			gameRules();

			break;
		case 2:		// let's play a game
			
			cout << "\nGood luck ranger...\n   GAME START\n" << endl;

			// initialize placement (not even sure if this is a good idea)
			everglades[0][0] = ranger;
			everglades[4][4] = tourist;

			genDangers(key);						// generate dangers and place in key array

			while (gong > 0)
			{
				// display map
				dispMap(everglades);		
				cout << "\nGongs Left: " << gong << endl;

				// send input to validation function
				do						
				{
					cout << move;					// prompt player for move
					cin >> row >> col;

					error = validateMove(row, col, x, y);

					if (error == 1)
						cout << "\nEntered cell is out of bounds. Please try again." << endl;
					else if (error == 2)
						cout << "\nEntered cell is not adjacent! Try again." << endl;

				} while (error != 0);

				// check for danger
				if (key[row][col] == 1)
					inDanger(everglades, row, col, gong, x, y, ranger);
				else								
				{
					// if no danger, move ranger to cell and gong--
					everglades[row][col] = ranger;
					gong--;
					// update previous position
					everglades[x][y] = ' ';
					x = row;
					y = col;
					cout << "\nCell (" << row << "," << col << ") is free...you advance!\n" << endl;
				}
			
				// win condition
				if (ranger == everglades[4][4])
				{
					for (int i = 0; i < 55; i++)
						cout << '*';
					cout << "\n*" << setw(15) << " " << "Congratulations, Ranger!" << setw(15) << '*'
						<< "\n* You found the lost tourists and led them to safety! *" << endl;
					for (int i = 0; i < 55; i++)
						cout << '*';
					break;
				}
			}

			// losing message
			if (gong <= 0)
				cout << "\nSorry...you ran out of time." << endl;		// maybe make this message better lol

			break;
		case 3:		// quit
			cout << "\nThank you for playing Lost in the Everglades..." << endl;
			break;
		default:	// error
			cout << "\nERROR: Invalid selection. Please try again." << endl;
		}
	} while (menuChoice != 3);

	return 0;
}

/*
	void genDangers()

	generates random cells and places a danger in them based on a binary system
	0 = safe, 1 = danger

	{{' ', '*', '*', '*', '*'},
	{'*', '*', '*', '*', '*'},
	{'*', '*', '*', '*', '*'},
	{'*', '*', '*', '*', '*'},
	{'*', '*', '*', '*', ' '}};
*/
void genDangers(int key[][MAP])
{
	int danger = 1;			// random danger
	int row, col;			// to be randomly generated
	srand(time(NULL));		// seeding random function

	// run generator 10 times
	for (int i = 0; i < 10; i++)
	{
		row = rand() % 4;	// generate random x-coordinate 1-3
		col = rand() % 4;	// generate random y-coordinate 1-3
		
		key[row][col] = danger;
	}

	// erase the /* */ to turn on cheats >:P
	/*
		for (int r = 0; r < MAP; r++)
		{
			for (int c = 0; c < MAP; c++)
			{
				cout << " " << key[r][c];
			}
			cout << endl;
		}
	*/

	return;
}

/*
	void gameRules()

	displays game rules

	no return values
*/
void gameRules()
{
	// Putting title in the middle of screen
	cout << setw(55);
	cout << "Lost in the Everglades" << endl;
	cout << setw(50);
	cout << "Game Rules" << endl;

	for (int i = 1; i <= 90; i++)
		cout << '-';
	cout << endl;

	// Game Rules
	cout << "Hello Ranger! You are stationed at Everglades National Park,"
		<< "\nwhere a group of lost tourists need to be rescued"
		<< " before time runs out!" << endl;
	cout << "\nUse your map to locate and may your way to the tourists," << endl
		<< "but beware of dangers along the way!" << endl;
	cout << "\nMany wild and territorial creatures lurk in the park," << endl
		<< "such as alligators, giant mosquitos, venemous spiders, and enormous pythons!" << endl;
	cout << "If you do encounter one of these dangers, you will have two choices:"
		<< "\n\tFight or Wait."
		<< "\n\n\t*Waiting - you will move to your desired cell but lose 5 gongs of time*"
		<< "\n\t*Fight & win -  you will move to your desired cell & lose 2 gongs of time*"
		<< "\n\t*Fight & lose - you will not move, lose 3 gongs of time,"
		<< "\n\t and the danger will remain in the cell*" << endl;

	cout << "\nThe game ends when either:" << endl
		<< "\tThe ranger rescues the group of tourists." << endl
		<< "\tThe time expires and the fate of the tourists is forever unknown." << endl;

	for (int i = 1; i <= 90; i++)
		cout << '-';
	cout << endl;
}

/*
	void displayMap()

	display an updated 5x5 map whenever called

	return val: none
*/
void dispMap(char ev[][MAP])
{
	string ib = " | ";		// for in between cells

	cout << "     0   1   2   3   4" << endl;
	// damn, make a for-loop to eliminate these long ass lines of code:
	cout << "0 " << ib << ev[0][0] << ib << ev[0][1] << ib << ev[0][2] << ib << ev[0][3] << ib << ev[0][4] << ib << endl;
	cout << "1 " << ib << ev[1][0] << ib << ev[1][1] << ib << ev[1][2] << ib << ev[1][3] << ib << ev[1][4] << ib << endl;
	cout << "2 " << ib << ev[2][0] << ib << ev[2][1] << ib << ev[2][2] << ib << ev[2][3] << ib << ev[2][4] << ib << endl;
	cout << "3 " << ib << ev[3][0] << ib << ev[3][1] << ib << ev[3][2] << ib << ev[3][3] << ib << ev[3][4] << ib << endl;
	cout << "4 " << ib << ev[4][0] << ib << ev[4][1] << ib << ev[4][2] << ib << ev[4][3] << ib << ev[4][4] << ib << endl;

	return;
}

/*
	int validateMove()

	checks that move is within parameters (0 < x > 5), that it is adjacent to current cell (HOW DO I DO THIS??),
	and that it does not contain a Danger? (can prob do this in main)

	return val: 0 (if all is clear), 1 for out of bounds, 2 for non-adjacent
*/
int validateMove(int row, int col, int x, int y)
{
	int error;
	
	if (row < 0 || row > 4)					// if row is out of boundaries
		error = 1;
	else if (col < 0 || col > 4)			// if column is out of boundaries
		error = 1;
	else if (x < --row || x > ++row)		// if row input is not adjacent
		error = 2;
	else if (y < --col || y > ++col)		// if column input is not adjacent
		error = 2;	
	else
		error = 0;

	return error;
}

/*
	void inDanger(char ev[][MAP], int& gong)

	generates a danger and then prompts player to choose wait or fight (updates gong counter -5 for wait),
	randomly determines outcome of fight (gong -3 for loss and -2 for win), and updates cell if danger is beaten
*/
void inDanger(char ev[][MAP], int row, int col, int& gong, int& x, int& y, char& pc)
{
	srand(time(NULL));						// seeding random function (do i need to do this again?)
	int danger = rand() % 3;				// 0 - 3 for 4 types of dangers
	string dName[] = { "Hungry Alligator", "Swarm of Giant Mosquitos", "Venemous Spider", "Python" };
	char icon[] = { 'A', 'M', 'S', 'P' };	
	int move, outcome;

	// danger sequence
	cout << "\nWatch out! There is a " << dName[danger] << " ahead!" << endl
		<< "\nWhat will you do?\n\t1 - Wait until it leaves.\n\t2 - Fight it." << endl;
	
	// validate
	do
	{
		cout << "Your move: ";
		cin >> move;

		if (move < 1 || move > 2)
		{
			cout << "\nInvalid choice. Please choose 1 or 2." << endl;
		}
	} while (move < 1 || move > 2);

	switch (move)
	{
		case 1:	// wait
			cout << "\n... ... ...\n... ... ..." << endl
				<< "The " << dName[danger] << " is gone...you advance!" << endl;
			gong = gong - 3;
			break;
		case 2: // fight
			outcome = rand() % 2;			// 0 - 2 to give player a greater chance at winning

			if (outcome == 0)				// loss
			{
				cout << "\n... ... ...\nYou fight the " << dName[danger] << " and lose..." << endl
					 << "You'll have to retreat and find a way around." << endl;
				gong = gong - 5;
				// update map with danger character
				ev[row][col] = icon[danger];
			}
			else
			{
				cout << "\n... ... ...\nYou fight the " << dName[danger] << " and win! You advance." << endl;
				gong = gong - 2;
				// update player position and previous position
				ev[row][col] = pc;
				ev[x][y] = ' ';
				x = row;
				y = col;
			}
			break;
	}
	return;
}