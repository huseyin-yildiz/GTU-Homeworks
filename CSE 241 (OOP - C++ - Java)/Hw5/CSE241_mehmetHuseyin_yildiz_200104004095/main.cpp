#include <iostream>
#include "HexVector.h"
#include "HexArray1D.h"
#include "HexAdapter.h"

using namespace Hex;

int main()
{

	try {
		vector<AbstractHex*> games;

		HexArray1D* game1 = new HexArray1D(8, "Ali", "Hasan");
		HexVector* game2 = new HexVector(10, "Ahmet", "Mehmet");
		auto game3 = new HexAdapter<CellState, deque< deque<CellState> > >(9,"Zeki","Veli");
		auto game4 = new HexAdapter<CellState, vector<vector<CellState> > >(12,"Hasan","Yusuf");
		HexVector* game5 = new HexVector(16,"Berke", "Kadir");

		games.push_back(game1);
		games.push_back(game2);
		games.push_back(game3);
		games.push_back(game4);
		games.push_back(game5);

		int i = 0;
		for(AbstractHex* game : games)
		{
			cout << "\n\n ---------------- game " + to_string(++i) + " ----------------\n"  ;
			game->print();
			Location location1(2, 0);
			Location location2(7, 0);
			game->play(location1);
			game->play(location2);
			game->print();
			game->writeToFile("savedGame"+to_string(i));

			for (int i = 0; i < 7; i++)
			{
				location2.setByAdding(0, 1);
				location1.setByAdding(0, 1);
				game->play(location1);
				game->play(location2);
			}



			game->print();
			if (game->isEnd())
				cout << "The game end " + game->getPlayerNow() + " is winner. Congratulations...\n";

			game->readFromFile("savedGame"+to_string(i));
			game->print();
		
			cout << "\n--------------------------------------\n";
		}

		cout << "\n--------------------Exception Test------------------\n";

		HexVector gameExcepTest1(74, "Sabri", "Cihat");
		
		
	}
	
	catch (out_of_board_exception ex)
	{
		cerr << "You cant access out of board" << endl;
		cerr << ex.what() << endl;
	}

	catch(my_exception ex)
	{
		cerr << ex.what() << endl;
	}

	catch (exception ex)
	{
		cerr << ex.what() << endl;
	}

	
	return 0;
}

