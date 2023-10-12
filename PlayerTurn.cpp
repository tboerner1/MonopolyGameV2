#include "PlayerTurn.h"
#include "Functions.h"
#include <Windows.h>

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

//array<String^>^ args
//would normally go in main, don't know why, but it should be in there.
//If I have future bugs, come back to this point.
void main() {
	Application::SetCompatibleTextRenderingDefault;
	Application::EnableVisualStyles();
	MonopolyGameWithGUI::PlayerTurn frm;




	buildBoard(tile, NUM_SPACES);


	for (int j = 0; j < NUM_PLAYERS; j++) {
		player[j].setPlayerNum(j + 1);
		player[j].setMoney(MONEY);
		player[j].initializeSpacesOwned();
	}
	giveTile(tile, player, DARK_BLUE2, 1);
	giveTile(tile, player, DARK_BLUE1, 1);
	giveTile(tile, player, ORANGE1, 2);
	giveTile(tile, player, ORANGE2, 2);
	giveTile(tile, player, ORANGE3, 2);


	int i = 0;
	do {

		if (!player[playerIndex].getIsBankrupt()) {
			if (player[playerIndex].getPosition() == JAIL) {
				jailTurn(tile, player, playerIndex + 1);
				checkSpace(tile, player, player[playerIndex].getPosition() - 1, playerIndex + 1);
				playerIndex++;

			}
			do {
				cout << "Player " << playerIndex + 1 << ": " << endl;
				cout << "You have $" << player[playerIndex].getMoney() << endl;
				MonopolyGameWithGUI::PlayerTurn::Form^ frm = gcnew MonopolyGameWithGUI::PlayerTurn;
				Application::Run(frm);
				if (player[playerIndex].getDie1() == player[playerIndex].getDie2() &&
					player[playerIndex].getNumDoubles() < 3) {
					cout << "You rolled Doubles, take another turn" << endl;
					player[playerIndex].addNumDoubles();
				}
			} while (player[playerIndex].getDie1() == player[playerIndex].getDie2() &&
				player[playerIndex].getNumDoubles() < 3);
			player[playerIndex].setNumDoublesZero();
			
			
		}
		if (playerIndex < NUM_PLAYERS - 1) {
			playerIndex++;
		}
		else {
			playerIndex = 0;
		}
	} while (num_bankrupt < NUM_PLAYERS - 1);

}