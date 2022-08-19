#include<iostream>
#include"hex.h"


using namespace std;

bool Hex::newGame{ false };
int Hex::gameNow{ 0 };
int Hex::compare1{ -1 };		// initialization of some required static variables
int Hex::compare2{ -1 };

int main() {

	vector<Hex> hexGames;
	Hex firstGame;							// first game as default is added
	firstGame.menu();

	hexGames.push_back(firstGame);


	while (hexGames.size() != 0)						// while there is still at least a game 
	{
		if (Hex::gameNow > hexGames.size())				// if user enters wrong game number
		{
			cerr << "There is no game with this number. ";
			Hex::gameNow = 0;
		}

		hexGames[Hex::gameNow].PlayGame();			
		hexGames[0].clearScreen();
		cout << "Games at now:\n";
		for (int i = 0; i < hexGames.size(); i++)
			cout << i << ")" << hexGames[i].user1 << "-" << hexGames[i].user2 << endl ;
		cout << "\nInstruction Examples:\n- SAVE FILENAME\n- LOAD FILENAME\n- NEW\n- COMPARE 1 2\n- GAME 1 (playing for game 1)\n- UNDO 3 (Goes to 3 step back) \n- f5" << endl << endl << endl;
		if (Hex::newGame == true)						// if user want to add new game
		{

			Hex newGame;
			newGame.menu();									// takes information about the game
			hexGames.push_back(newGame);
			Hex::newGame = false;
			Hex::gameNow = hexGames.size() - 1;
		}

		if (Hex::compare1 != -1)
			hexGames[Hex::compare1] == hexGames[Hex::compare2];		// comparing 2 games with overloading ==

		if(hexGames[Hex::gameNow].isFinished)						// when the current game is finished
		{
			hexGames[Hex::gameNow].showResults();
			hexGames[Hex::gameNow].deleteTheTempFiles();
			hexGames.erase(hexGames.begin()+ Hex::gameNow);
			Hex::gameNow = 0;
			if (hexGames.size() < 1)									// if there is no any game
				cout << endl << "There is no any game to play goodBye :) " << endl << endl;
			
		}
	}
	

		return 0;
}
