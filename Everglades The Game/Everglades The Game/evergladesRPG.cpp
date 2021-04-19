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

// header files
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// Global constants
const int MAP = 5;		// size of map matrix

// Function prototypes
void gameRules();
void dispMap(const char[][MAP]);
// void/bool testInput? determine if danger is in next space or not, also maybe validate as well
// int danger?? in case of danger = true, return win (1) or loss (0) ??

int main()
{
	// Constants and Variables
	int playerChoice, row, column;
	int gong = 12;		// gong counter
	string move = "\nWhere would you like to move?\n(row & column): ";
	char everglades[MAP][MAP] = { {'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'}, 
								{'*', '*', '*', '*', ' '} };
	char ranger = 'R', tourist = 'T';

	srand(time(0));		// seeding random function
						
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
			
			cout << "\n[good luck ranger...]\nGAME START\n" << endl;

			// initialize placement (not even sure if this is a good idea)
			everglades[0][0] = ranger;
			everglades[4][4] = tourist;

			while (gong > 0 || ranger != tourist)
			{

				dispMap(everglades);		// display map
				cout << move;				// prompt player for move
				cin >> row >> column;
											// send input to validation function

			}

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
		<< "and your objective is to rescue a group of stranded tourists that are lost" << endl
		<< "in the everglades before time runs out!" << endl;
	cout << "\nThe everglades is represented by a 5x5 Matrix, and you"
		<< " Ranger will begin your task in the upperleft corner of the park."
		<< " The lost tourists are located at the bottom left." << endl;
	cout << "\tTime Limit\nYou have 12 gongs of time to find and rescue the tourist"
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
		Ex: entering "3 5" would move the ranger to the space located in Row 3, Column 5
		The ranger can only move to spaces adjacent or diagonal to the one they are in.
		Ex: moving from Row 2 to 4 is not possible without first moving to a space in Row 3

		- explain dangers and how to proceed
		The Everglades terrain is full of lurking dangers, ranging from mosquito swarms to
		hungry alligators! The ranger can avoid them if you're lucky, but most times, you will
		have to confront them or go around.
		When a danger exists in a cell you wish to move to, you will be asked whether you wish
		to fight or wait for the danger to pass.

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
void dispMap(const char ev[][MAP])
{
	string space = " | ";		// for in between cells

	cout << setw(6) << "0   1   2   3   4" << endl;
		// damn, make a for-loop to eliminate these long ass lines of code:
	cout << "0 " << space << ev[0][0] << space << ev[0][1] << space << ev[0][2] << space << ev[0][3] << space << ev[0][4] << space << endl;
	cout << "1 " << space << ev[1][0] << space << ev[1][1] << space << ev[1][2] << space << ev[1][3] << space << ev[1][4] << space << endl;
	cout << "2 " << space << ev[2][0] << space << ev[2][1] << space << ev[2][2] << space << ev[2][3] << space << ev[2][4] << space << endl;
	cout << "3 " << space << ev[3][0] << space << ev[3][1] << space << ev[3][2] << space << ev[3][3] << space << ev[3][4] << space << endl;
	cout << "4 " << space << ev[4][0] << space << ev[4][1] << space << ev[4][2] << space << ev[4][3] << space << ev[4][4] << space << endl;

	return;
}

/*
	function 3
	// void getDanger
	// or void checkDanger
	dangers located on the map
	{						    {'R', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', 'T'} };
								Has to be ten
								A - Hungry Alligators
							    M - Swarm of Giant Mosquitoes
								S - Venomous Spider
								P - Python
*/


/*
	function 4
*/