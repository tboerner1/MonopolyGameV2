#pragma once
#ifndef H_Chance
#define H_Chance

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

void drawChanceCard(Board tile[], Players player[], int index, int playerNum) {
	int random = (rand() % 16) + 1;
	//Distances to railroads or utilities
	int dist1 = 0, dist2 = 0, dist3 = 0, dist4 = 0;


	switch (random) {
	case 1:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Advance to Boardwalk",
			"Chance Card", MessageBoxButtons::OK);
		if (DARK_BLUE2 <= player[playerNum - 1].getPosition() - 1) {
			player[playerNum - 1].addMoney(200);
		}
		player[playerNum - 1].setPosition(DARK_BLUE2 + 1);
		checkSpace(tile, player, player[playerNum - 1].getPosition() - 1, playerNum);
		break;
	case 2:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Advance to GO (Collect $200)",
			"Chance Card", MessageBoxButtons::OK);
		player[playerNum - 1].setPosition(GO + 1);
		player[playerNum - 1].addMoney(200);
		break;
	case 3:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Advance to Illinois Avenue\n"
			+ "If you pass GO, collect $200", "Chance Card", MessageBoxButtons::OK);
		if (RED3 <= player[playerNum - 1].getPosition() - 1) {
			player[playerNum - 1].addMoney(200);
		}
		player[playerNum - 1].setPosition(RED3 + 1);
		checkSpace(tile, player, player[playerNum - 1].getPosition() - 1, playerNum);
		break;
	case 4:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Advance to St. Charles Place\n"
			+ "If you pass GO, collect $200", "Chance Card", MessageBoxButtons::OK);
		if (PINK1 <= player[playerNum - 1].getPosition() - 1) {
			player[playerNum - 1].addMoney(200);
		}
		player[playerNum - 1].setPosition(PINK1 + 1);
		checkSpace(tile, player, player[playerNum - 1].getPosition() - 1, playerNum);
		break;
	case 5:
		//FIX CASE 5, 6, and 7
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Advance to nearest Railroad\n"
			+ "If unowned, you may buy it.\n If owned, pay double the normal rent", 
			"Chance Card", MessageBoxButtons::OK);
		while (tile[player[playerNum - 1].getPosition() - 1].getId() != "railroad") {
			if (player[playerNum-1].getPosition() == 40) {
				player[playerNum-1].setPosition(1);
			}
			else {
				player[playerNum - 1].setPosition(player[playerNum - 1].getPosition() + 1);
			}
		}
		checkSpace(tile, player, player[playerNum - 1].getPosition() - 1, playerNum);
		break;
	case 6:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Advance to nearest Railroad\n"
			+ "If unowned, you may buy it.\n If owned, pay double the normal rent",
			"Chance Card", MessageBoxButtons::OK);
		while (tile[player[playerNum - 1].getPosition() - 1].getId() != "railroad") {
			if (player[playerNum - 1].getPosition() == 40) {
				player[playerNum - 1].setPosition(1);
			}
			else {
				player[playerNum - 1].setPosition(player[playerNum - 1].getPosition() + 1);
			}
		}
		checkSpace(tile, player, player[playerNum - 1].getPosition() - 1, playerNum);
		break;
	case 7:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Advance to nearest Utility\n"
			+ "If unowned, you may buy it.\n If owned, pay 10 times dice roll",
			"Chance Card", MessageBoxButtons::OK);
		while (tile[player[playerNum - 1].getPosition() - 1].getId() != "utility") {
			if (player[playerNum - 1].getPosition() == 40) {
				player[playerNum - 1].setPosition(1);
			}
			else {
				player[playerNum - 1].setPosition(player[playerNum - 1].getPosition() + 1);
			}
		}
		checkSpace(tile, player, player[playerNum - 1].getPosition() - 1, playerNum);
		break;
	case 8:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Bank pays you dividend of $50.",
			"Chance Card", MessageBoxButtons::OK);
		player[playerNum - 1].addMoney(50);
		break;
	case 9:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Get out of Jail Free",
			"Chance Card", MessageBoxButtons::OK);
		player[playerNum - 1].addNumGetOutOfJailCards();
		break;
	case 10:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Go back 3 spaces",
			"Chance Card", MessageBoxButtons::OK);
		int newPosition = player[playerNum - 1].getPosition() - 3;
		if (newPosition <= 0) {
			newPosition = JAIL + newPosition;
		}
		player[playerNum - 1].setPosition(newPosition);
		if (player[playerNum - 1].getPosition() == GO + 1) {
			player[playerNum].addMoney(200);
		}
		break;
	case 11:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Go to Jail. Go directly to jail,\n" +
			"do not pass GO, do not collect $200", "Chance Card", MessageBoxButtons::OK);
		player[playerNum - 1].setPosition(JAIL + 1);
		break;
	case 12:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Make General repairs on all your property\n" +
			"$25 per house, $100 per hotel", "Chance Card", MessageBoxButtons::OK);
		cout << "Come back to this:";
		//Create function to do this
		break;
	case 13:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Speeding Fine of $15",
			"Chance Card", MessageBoxButtons::OK);
		if (player[playerNum - 1].getMoney() < 15) {
			checkMortgage(tile, player, index, playerNum, 15, "to pay $15");
		}
		if (player[playerNum - 1].getMoney() >= 15) {
			player[playerNum - 1].subtractMoney(15);
		}
		break;
	case 14:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Advance to Reading Railroad\n"
			+ "If you pass GO, collect $200", "Chance Card", MessageBoxButtons::OK);
		if (RAILROAD1 <= player[playerNum - 1].getPosition() - 1) {
			player[playerNum - 1].addMoney(200);
		}
		player[playerNum - 1].setPosition(RAILROAD1 + 1);
		checkSpace(tile, player, player[playerNum - 1].getPosition() - 1, playerNum);
		break;
	case 15:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "You've been elected as Chairman of the Board.\n" +
			"Pay each player $50", "Chance Card", MessageBoxButtons::OK);
		for (int i = 0; i < NUM_PLAYERS; i++) {
			if (!player[i].getIsBankrupt() && i != playerNum - 1) {
				if (player[playerNum-1].getMoney() < 50) {
					checkMortgage(tile, player, index, i + 1, 50, "to pay $50");
				}
				if (player[playerNum-1].getMoney() >= 50) {
					player[playerNum-1].subtractMoney(50);
					player[i].addMoney(50);
				}
			}
		}
		break;
	case 16:
		MessageBox::Show("Player " + (playerNum + 1) + "\n" + "Your building loan matures.\n Collect $150",
			"Chance Card", MessageBoxButtons::OK);
		player[playerNum - 1].addMoney(150);
		break;
	}

}

#endif