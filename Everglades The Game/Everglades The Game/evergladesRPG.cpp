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
using namespace std;

// Global constants
const int MAP = 5;		// size of map matrix

// Function prototypes
void gameRules();
void dispMap(const char[][MAP]);

int main()
{
	// Constants and Variables
	int playerChoice;
	char everglades[MAP][MAP] = { {'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'},
								{'*', '*', '*', '*', '*'}, 
								{'*', '*', '*', '*', 'T'} };

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
			
			dispMap(everglades);

			break;
		case 3:		// quit
			cout << "\n[some kind of quit message]" << endl;
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
void dispMap(const char arr[][MAP])
{

	return;
}

/*
	function 3
*/


/*
	function 4
*/