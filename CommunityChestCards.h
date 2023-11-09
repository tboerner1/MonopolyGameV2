#pragma once
#ifndef H_Comm_Chest
#define H_Comm_Chest

#include "Board.h"
#include "Players.h"
#include <Windows.h>
#include "Functions.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

void drawCommCard(Board tile[], Players player[], int index, int playerNum) {
	int random = (rand() % 16) + 1;

	switch (random) {
	case 1:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Advance to GO (Collect $200)", 
			"Community Chest Card", MessageBoxButtons::OK);
		player[playerNum - 1].setPosition(GO + 1);
		player[playerNum - 1].addMoney(200);
		break;
	case 2:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Bank error in your favor\n (Collect $200)",
			"Community Chest Card", MessageBoxButtons::OK);
		player[playerNum - 1].addMoney(200);
		break;
	case 3:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Doctor's Fee (Pay $50)",
			"Community Chest Card", MessageBoxButtons::OK);
		if (player[playerNum - 1].getMoney() < 50) {
			checkMortgage(tile, player, index, playerNum, 50, "to pay $50");
		}
		if (player[playerNum - 1].getMoney() >= 50) {
			player[playerNum - 1].subtractMoney(50);
		}
		break;
	case 4:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "From sale of stock,\n you get $50",
			"Community Chest Card", MessageBoxButtons::OK);
		player[playerNum - 1].addMoney(50);
		break;
	case 5:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Get out of Jail Free",
			"Community Chest Card", MessageBoxButtons::OK);
		player[playerNum - 1].addNumGetOutOfJailCards();
		break;
	case 6:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Go to Jail. Go directly to jail,\n" +
			"do not pass GO, do not collect $200", "Community Chest Card", MessageBoxButtons::OK);
		player[playerNum - 1].setPosition(JAIL + 1);
		break;
	case 7:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Holiday Fund Matures.\n Receive $100",
			"Community Chest Card", MessageBoxButtons::OK);
		player[playerNum - 1].addMoney(100);
		break;
	case 8:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Income Tax refund.\n Collect $20",
			"Community Chest Card", MessageBoxButtons::OK);
		player[playerNum - 1].addMoney(20);
		break;
	case 9:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "It is your birthday.\n Collect $10 from each player",
			"Community Chest Card", MessageBoxButtons::OK);
		for (int i = 0; i < NUM_PLAYERS; i++) {
			if (!player[i].getIsBankrupt() && i != playerNum-1) {
				if (player[i].getMoney() < 10) {
					checkMortgage(tile, player, index, i + 1, 10, "to pay $10");
				}
				if (player[i].getMoney() >= 10) {
					player[i].subtractMoney(10);
					player[playerNum - 1].addMoney(10);
				}
			}
		}
		break;
	case 10:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Life Insurance Matures.\n Collect $100",
			"Community Chest Card", MessageBoxButtons::OK);
		player[playerNum - 1].addMoney(100);
		break;
	case 11:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Pay hospital fees of $100",
			"Community Chest Card", MessageBoxButtons::OK);
		if (player[playerNum - 1].getMoney() < 100) {
			checkMortgage(tile, player, index, playerNum, 100, "to pay $100");
		}
		if (player[playerNum - 1].getMoney() >= 100) {
			player[playerNum - 1].subtractMoney(100);
		}
		break;
	case 12:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Pay school fees of $50",
			"Community Chest Card", MessageBoxButtons::OK);
		if (player[playerNum - 1].getMoney() < 50) {
			checkMortgage(tile, player, index, playerNum, 50, "to pay $50");
		}
		if (player[playerNum - 1].getMoney() >= 50) {
			player[playerNum - 1].subtractMoney(50);
		}
		break;
	case 13:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Recieve $25 consulting fee",
			"Community Chest Card", MessageBoxButtons::OK);
		player[playerNum - 1].addMoney(25);
		break;
	case 14:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "You are assessed for street repair\n" +
			"$40 per house, $115 per hotel", "Community Chest Card", MessageBoxButtons::OK);
		cout << "Come back to this:";
		//Create function to do this
		break;
	case 15:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "You won 2nd in a beauty contest.\n Collect $10",
			"Community Chest Card", MessageBoxButtons::OK);
		player[playerNum - 1].addMoney(10);
		break;
	case 16:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "You inherit $100",
			"Community Chest Card", MessageBoxButtons::OK);
		player[playerNum - 1].addMoney(100);
		break;

	}
}

#endif