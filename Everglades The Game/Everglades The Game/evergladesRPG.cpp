/*
	Brian (last name? lmao sorry!), Jayde Shaw, Kim Claros

	evergladesRPG.cpp

	[ desc ]

	I:	initial menu choice, game decisions

	P:

	O:	5 x 5 cell map (maybe expand on this?)
*/

// header files
#include <iostream>
#include <string>
using namespace std;

// function prototypes



int main()
{
	// constants and variables
	int playerChoice;

	// intro
	cout << "\n\t\tLost in the Everglades" << endl;

	// pretty sure driving menu with a switch-case, but idk yet
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
			;
			break;
		case 2:		// let's play a game
			;
			break;
		case 3:		// quit
			cout << "\n[some kind of quit message]" << endl;

		default:	// error
			cout << "ERROR: Invalid selection. Please try again." << endl;

		}
	} while (playerChoice != 3);

	return 0;
}

/*
	function 1
*/


/*
	function 2
*/
