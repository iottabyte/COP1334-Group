/*
	Brian Durin, Jayde Shaw, Kim Claros

	evergladesRPG.cpp

	[ desc ]

	I:	initial menu choice, game decisions

	P:

	O:	5 x 5 cell map (maybe expand on this?)
*/

// header files
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// global constants


// function prototypes
void gameRules();

int main()
{
	// constants and variables
	int playerChoice;

	// intro
	cout << "\n\t\tLost in the Everglades" << endl
		<< "\t\t\tTHE GAME" << endl;

	// pretty sure driving menu with a switch function
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
			;
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
	// imma be real wit u chief
	// i do NOT want to type this up
	// but i will if no one else does
	// D;

	cout << "\nLost in the Everglades - Game Rules" << endl
		<< "-------------------------------------" << endl;

	// how to play
	cout << "\nYou are a ranger stationed at Everglades National Park," << endl
		<< "and your objective is to rescue a group of stranded tourists" << endl
		<< "before time runs out!" << endl;

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
	function 2
*/


/*
	function 3
*/


/*
	function 4
*/