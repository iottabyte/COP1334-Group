/*
	Brian Durin, Jayde Shaw, Kim Claros

	evergladesRPG.cpp

	A text-based RPG in which a player traverses a 5x5 two-dimensional array
	to rescue a group of lost tourists before time runs out.

	I:	initial menu choice, cell values, danger-related decisions

	P:	1 -	display initial menu and prompt user for choice
		2 - drive menu options
			1. Display game rules
			2. Start game
					display map and gong countdown
					prompt player (R) for next move
						if danger is generated in next cell:
							prompt user for choice: wait or fight
					continue until time runs out or player reaches
					the tourists (T)
			3 - Quit

	O:	1 - game rules
		2 - everglades 5 x 5 map, timer, and player consequences
*/

		/*
			TO DO LIST	(erase when complete)

			- fix genDanger() function
				- its only making 7 dangers
			- fix validateMove()
				- incorrectly rejecting SOME adjacent cells
			- dispMap()
				- figure out how to blank previously occupied cell
						everglades[x][y] = '*'; ?? 
				- replace 4 rows of cout with a for loop
			- complete game writing (like the shit in [braces])
			- make the game rules prettier (LOW PRIORITY)
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
void inDanger(char[][MAP], int, int, int&, char&); 

int main()
{
	// Constants and Variables
	int playerChoice, row, col, error;
	int x = 0;				// previous row, initialized to starting placement
	int y = 0;				// previous column
	int gong = 12;			// gong counter
	string move = "\nWhich adjacent cell would you like to move to?\n(row & column): ";
	char everglades[MAP][MAP] = { {' ', ' ', ' ', ' ', ' '},
								{' ', ' ', ' ', ' ', ' '},
								{' ', ' ', ' ', ' ', ' '},
								{' ', ' ', ' ', ' ', ' '}, 
								{' ', ' ', ' ', ' ', ' '} };
	char ranger = 'R', tourist = 'T';
	// int equivalent array holding location of dangers
	int key[MAP][MAP] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};		
				
	// Intro
	cout << "\n\t\tLost in the Everglades" << endl
		<< "\t\t\tTHE GAME" << endl;

	// Driving the menu and prompting user for choice
	do
	{
		// display menu
		cout << "\n[just pick one]" << endl
			<< "\n\t1 - See Rules" << endl
			<< "\t2 - Play Game" << endl
			<< "\t3 - Quit" << endl
			<< "\n[so what is it]: ";
		cin >> playerChoice;

		switch (playerChoice)
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
					inDanger(everglades, row, col, gong, ranger);
				else								
				{
					// if no danger, move ranger to cell and gong--
					everglades[row][col] = ranger;
					gong--;
					// update previous position
					// everglades[x][y] = '*';
					x = row;
					y = col;
					cout << "\nCell (" << row << "," << col << ") is free...you advance!\n" << endl;
					
					// now...SHOULD loop back to displaying map and prompting for move
			
				}
			
				// win condition
				if (ranger == tourist)
				{
					cout << "\nCongratulations, Ranger!\nYou found the lost tourists and led them to safety!" << endl;
					break;
				}
			}

			// losing message
			if (gong == 0)
				cout << "\nSorry...you ran out of time." << endl;		// maybe make this message better lol

			break;
		case 3:		// quit
			cout << "\nThank you for playing Lost in the Everglades..." << endl;
			break;
		default:	// error
			cout << "\nERROR: Invalid selection. Please try again." << endl;
		}
	} while (playerChoice != 3);

	return 0;
}

/*
	void genDangers()

	generates ten dangers at random and places them at
	random elements of map array

	{{'R', '*', '*', '*', '*'},
	{'*', '*', '*', '*', '*'},
	{'*', '*', '*', '*', '*'},
	{'*', '*', '*', '*', '*'},
	{'*', '*', '*', '*', 'T'}};
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
	for (int r = 0; r < MAP; r++)
	{
		for (int c = 0; c < MAP; c++)
		{
			cout << " " << key[r][c];
		}
		cout << endl;
	}

	return;
}

/*
	void gameRules()

	displays game rules

	no return values
*/
void gameRules()
{
	cout << "\nLost in the Everglades" << endl <<
			"\n\tGame Rules" << endl
		<< "----------------------------------" << endl;

	// Game objective and rules
	cout << "\nYou are a ranger stationed at Everglades National Park," << endl
		<< "and your objective is to rescue a group of stranded tourists " << endl
		<< "before time runs out!" << endl;
	cout << "\nA map of the area is represented by a 5x5 matrix, and you, the "
		<< "Ranger, will begin your task in the upperleft corner of the park."
		<< " The lost tourists are located at the bottom left." << endl;
	cout << "\tTime Limit\nYou have 12 gongs of time to find and rescue the tourists"
		<< "or they will perish."
		<< "\nDuring your journey you may encounter dangers like Hungry Alligators,"
		<< " Swarm of Giant Mosquitoes, Venomous Spider, or Python."
		<< " When you do encounter danger, you have the option of fighting,"
		<< " or hiding until they leave:"
		<< "\n\tIf you wait you will move to your desired cell but lose 5 gongs of time."
		<< "\n\tIf you fight & win you will move to your desired cell & lose 2 gongs of time."
		<< "\n\tIf you fight & lose you will go back to your intital cell, lose 3 gongs of time,"
		<< " and the danger will remain in the cell you lost the fight." << endl;

	/*
		- explain map
		The tourists in distress are located on the opposite side of the park.
		Examine your map and decide which direction to move by entering a cell
		postion when prompted.
		Ex: entering "3 5" would move the ranger to the ib located in Row 3, Column 5
		The ranger can only move to ibs adjacent or diagonal to the one they are in.
		Ex: moving from Row 2 to 4 is not possible without first moving to a ib in Row 3

		- explain time
	*/
	cout << "\nThe game ends when either:" << endl
		<< "\n\tThe ranger rescues the group of tourists." << endl
		<< "\n\tThe time expires and the fate of the tourists is forever unknown." << endl;
}

/*
	void displayMap()

	display an updated 5x5 map whenever called

	return val: none
*/
void dispMap(char ev[][MAP])
{
	string ib = " | ";		// for in between cells
	int rn = 0;		// for displaying key next to rows

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
void inDanger(char ev[][MAP], int row, int col, int& gong, char& pc)
{
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
			cout << "\n...\n...\nThe " << dName[danger] << " is gone...you advance!" << endl;
			gong = gong - 3;
			break;
		case 2: // fight
			outcome = rand() % 2;			// 0 - 2 to give player a greater chance at winning

			if (outcome == 0)				// loss
			{
				cout << "\n...\nYou fight the " << dName[danger] << " and lose..." << endl
					 << "You'll have to retreat and find a way around." << endl;
				gong = gong - 5;
				// update map with danger character
				ev[row][col] = icon[danger];
			}
			else
			{
				cout << "\n...\nYou fight the " << dName[danger] << " and win! You advance." << endl;
				gong = gong - 2;
				// update player position
				ev[row][col] = pc;
			}
			break;
	}
	return;
}