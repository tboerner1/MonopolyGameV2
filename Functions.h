#pragma once

#ifndef H_Functions
#define H_Functions


#include "Board.h"
#include "Players.h"
#include <fstream>
#include <iomanip>
#include "PlayerTurn.h"
#include "Constants.h"
#include <Windows.h>
#include <vector>
#include "CommunityChestCards.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


void buildBoard(Board tile[], int num_spaces);
void checkSpace(Board tile[], Players player[], int index, int playerNum);
int declareBankruptcy(Board tile[], Players player[], int index, int playerNum);
void buy(Board tile[], Players player[], int index, int playerNum);
void addTile(Board tile[], Players player[], int index, int playerNum);
void rent(Board tile[], Players player[], int index, int playerNum);
int propertyRent(Board tile[], Players player[], int index, int playerNum);
int utilityRent(Board tile[], Players player[], int index, int playerNum);
int railroadRent(Board tile[], Players player[], int index, int playerNum);
void tax(Board tile[], Players player[], int index, int playerNum);
void checkMortgage(Board tile[], Players player[], int index, int playerNum, int owed, string toPay);
void checkMortgage(Board tile[], Players player[], int index, int playerNum);
void forceBankruptcy(Board tile[], Players player[], int index, int playerNum, int owed, string toPay);
void mortgage(Board tile[], Players player[], int index, int playerNum);
void buildMortgage(Board tile[], Players player[], int index, int playerNum);
void build(Board tile[], Players player[], int index, int playerNum);
void removeHouses(Board tile[], Players player[], int index, int playerNum);
void giveTile(Board tile[], Players player[], int index, int playerNum);
void removeTile(Board tile[], Players player[], int index, int playerNum);
void subtractTile(Board tile[], Players player[], int index, int playerNum);
void monopolize(Board tile[], Players player[], int index, int PlayerNum);
void deMonopolize(Board tile[], Players player[], int index, int PlayerNum);
bool checkIsMortgaged(Board tile[], Players player[], int index, int playerNum);
void jailTurn(Board tile[], Players player[], int playerNum);
void giveOnePlayerProperties(Board tile[], Players player[], int index, int playerNum);
void giveUpProperties(Board tile[], Players player[], int index, int playerNum);
void initializeTrade(Board tile[], Players player[], int playerNum);
void trade(Board tile[], Players player[], int playerNum, int otherPlayerNum);


int num_bankrupt = 0;
Board tile[NUM_SPACES];
Players player[NUM_PLAYERS];



//This function creates the board by pulling data from a .txt file
void buildBoard(Board tile[], int num_spaces) {
	ifstream iFile;
	int tempI;
	string tempS;
	string id;
	iFile.open("BoardData.txt");

	for (int i = 0; i < num_spaces; i++) {
		iFile >> tempI;
		tile[i].setPosition(tempI);
		iFile >> id;
		tile[i].setId(id);
		if (id == "bProperty") {
			iFile >> tempS;
			tile[i].setColor(tempS);
		}
		if (id == "bProperty" || id == "utility" || id == "railroad") {
			iFile >> tempI;
			tile[i].setPrice(tempI);
			tile[i].setMortgagePrice(tempI / 2);
		}
		if (id == "go") {
			iFile >> tempI;
			tile[i].setPrice(tempI);
		}
		if (id == "bProperty" || id == "railroad" || id == "tax") {
			iFile >> tempI;
			tile[i].setRentPrice(tempI);
		}
		if (id == "bProperty") {
			iFile >> tempI;
			tile[i].setRent1(tempI);
			iFile >> tempI;
			tile[i].setRent2(tempI);
			iFile >> tempI;
			tile[i].setRent3(tempI);
			iFile >> tempI;
			tile[i].setRent4(tempI);
			iFile >> tempI;
			tile[i].setRentHotel(tempI);
			iFile >> tempI;
			tile[i].setPriceOfHouse(tempI);
		}
		iFile.ignore();
		getline(iFile, tempS);
		tile[i].setName(tempS);
	}
}

//this function gives the information about the space that the current player
//lands on.
void checkSpace(Board tile[], Players player[], int index, int playerNum) {
	cout << "You landed on: " << endl;
	cout << tile[index].getName() << " ";
	if (tile[index].getColor() != " ") {
		cout << "(" << tile[index].getColor() << ")";
	}
	cout << endl << endl;
	if (tile[index].getId() == "bProperty" || tile[index].getId() == "utility" || tile[index].getId() == "railroad") {
		if (!tile[index].getIsOwned()) {
			buy(tile, player, index, playerNum);

		}
		else {
			rent(tile, player, index, playerNum);
		}
	}
	else if (tile[index].getId() == "tax") {
		tax(tile, player, index, playerNum);
	}
	else if (tile[index].getId() == "gtJail") {
		player[playerNum - 1].setPosition(41);
	}
	else if (tile[index].getId() == "fParking") {
		player[playerNum - 1].addMoney(tile[index].getPrice());
		tile[index].setPrice(0);
	}
	else if (tile[index].getId() == "cChest") {
		drawCommCard(tile, player, index, playerNum);
	}


	//cout << left << setw(16) << "Position:" << right << setw(22) << tile[index].getPosition()<< endl;
	//cout << left << setw(16) << "Color:" << right << setw(22) << tile[index].getColor()<< endl;
	//cout << left << setw(16) << "Price:" << right << setw(22) << tile[index].getPrice() << endl;
	//cout << left << setw(16) << "Mortgage Price:" << right << setw(22) << tile[index].getMortgagePrice() << endl;
	//cout << left << setw(16) << "Rent Price:" << right << setw(22) << tile[index].getRentPrice() << endl;
	//cout << left << setw(16) << "Rent 1 House:" << right << setw(22) << tile[index].getRent1() << endl;
	//cout << left << setw(16) << "Rent 2 Houses:" << right << setw(22) << tile[index].getRent2() << endl;
	//cout << left << setw(16) << "Rent 3 Houses:" << right << setw(22) << tile[index].getRent3() << endl;
	//cout << left << setw(16) << "Rent 4 Houses:" << right << setw(22) << tile[index].getRent4() << endl;
	//cout << left << setw(16) << "Rent Hotel:" << right << setw(22) << tile[index].getRentHotel() << endl;
	//cout << left << setw(16) << "Price Of House:" << right << setw(22) << tile[index].getPriceOfHouse() << endl;
	//cout << left << setw(16) << "Name:" << right << setw(22) << tile[index].getName() << endl << endl;
}

void buy(Board tile[], Players player[], int index, int playerNum) {
	checkMortgage(tile, player, index, playerNum, tile[index].getPrice(), "to purchase this property");
	string choice = "y";
	if (player[playerNum - 1].getMoney() >= tile[index].getPrice()) {
		cout << "Player " << playerNum << ": Would you like to buy " << tile[index].getName()
			<< " for $" << tile[index].getPrice() << "? (y or n)";
		cin >> choice;
		if (choice == "Y" || choice == "y") {
			giveTile(tile, player, index, playerNum);
			player[playerNum - 1].subtractMoney(tile[index].getPrice());
			cout << "Player " << playerNum << " bought " << tile[index].getName() << endl;
			cout << "You have $" << player[playerNum - 1].getMoney() << " left" << endl << endl;
		}
	}
	else {
		cout << "You don't have enough money to purchase this property." << endl << endl;
	}
}

//Allows giving a tile to a player without making them have to purchase it
void giveTile(Board tile[], Players player[], int index, int playerNum) {
	tile[index].setIsOwned();
	tile[index].setOwner(playerNum);
	player[playerNum - 1].addProperty(index);
	addTile(tile, player, index, playerNum);
}

void removeTile(Board tile[], Players player[], int index, int playerNum) {
	player[playerNum - 1].subtractProperty(index);
	subtractTile(tile, player, index, playerNum);
}

//this function adds the tile in one of the player's numColor variables, it also
//monopolizes a tile if need be.
void addTile(Board tile[], Players player[], int index, int playerNum) {
	if (tile[index].getId() == "utility") {
		player[playerNum - 1].addUtility();
	}
	else if (tile[index].getId() == "railroad") {
		player[playerNum - 1].addRailroad();
	}
	else {
		if (tile[index].getColor() == "Brown") {
			player[playerNum - 1].addBrown();
		}
		else if (tile[index].getColor() == "Light_Blue") {
			player[playerNum - 1].addLightBlue();
		}
		else if (tile[index].getColor() == "Pink") {
			player[playerNum - 1].addPink();
		}
		else if (tile[index].getColor() == "Orange") {
			player[playerNum - 1].addOrange();
		}
		else if (tile[index].getColor() == "Red") {
			player[playerNum - 1].addRed();
		}
		else if (tile[index].getColor() == "Yellow") {
			player[playerNum - 1].addYellow();
		}
		else if (tile[index].getColor() == "Green") {
			player[playerNum - 1].addGreen();
		}
		else if (tile[index].getColor() == "Dark_Blue") {
			player[playerNum - 1].addDarkBlue();
		}
	}
	monopolize(tile, player, index, playerNum);
}

//this function subtracts the tile in one of the player's numColor variables, it also
//unmonopolizes a tile if need be.
void subtractTile(Board tile[], Players player[], int index, int playerNum) {
	if (tile[index].getId() == "utility") {
		player[playerNum - 1].subtractUtility();
	}
	else if (tile[index].getId() == "railroad") {
		player[playerNum - 1].subtractRailroad();
	}
	else {
		if (tile[index].getColor() == "Brown") {
			player[playerNum - 1].subtractBrown();
		}
		else if (tile[index].getColor() == "Light_Blue") {
			player[playerNum - 1].subtractLightBlue();
		}
		else if (tile[index].getColor() == "Pink") {
			player[playerNum - 1].subtractPink();
		}
		else if (tile[index].getColor() == "Orange") {
			player[playerNum - 1].subtractOrange();
		}
		else if (tile[index].getColor() == "Red") {
			player[playerNum - 1].subtractRed();
		}
		else if (tile[index].getColor() == "Yellow") {
			player[playerNum - 1].subtractYellow();
		}
		else if (tile[index].getColor() == "Green") {
			player[playerNum - 1].subtractGreen();
		}
		else if (tile[index].getColor() == "Dark_Blue") {
			player[playerNum - 1].subtractDarkBlue();
		}
	}
	deMonopolize(tile, player, index, playerNum);
}

//This function sets any property to a monopoly if the player has the correct amount of that property
void monopolize(Board tile[], Players player[], int index, int PlayerNum) {
	if (tile[index].getId() == "utility" && player[PlayerNum - 1].getNumUtilities() == 2) {
		tile[UTILITY1].setIsMonopolized();
		tile[UTILITY2].setIsMonopolized();
	}
	else if (tile[index].getId() == "railroad" && player[PlayerNum - 1].getNumUtilities() == 4) {
		tile[RAILROAD1].setIsMonopolized();
		tile[RAILROAD2].setIsMonopolized();
		tile[RAILROAD3].setIsMonopolized();
		tile[RAILROAD4].setIsMonopolized();
	}
	else if (tile[index].getId() == "bProperty") {
		if (tile[index].getColor() == "Brown" && player[PlayerNum - 1].getNumBrown() == 2) {
			tile[BROWN1].setIsMonopolized();
			tile[BROWN2].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Light_Blue" && player[PlayerNum - 1].getNumLightBlue() == 3) {
			tile[LIGHT_BLUE1].setIsMonopolized();
			tile[LIGHT_BLUE2].setIsMonopolized();
			tile[LIGHT_BLUE3].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Pink" && player[PlayerNum - 1].getNumPink() == 3) {
			tile[PINK1].setIsMonopolized();
			tile[PINK2].setIsMonopolized();
			tile[PINK3].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Orange" && player[PlayerNum - 1].getNumOrange() == 3) {
			tile[ORANGE1].setIsMonopolized();
			tile[ORANGE2].setIsMonopolized();
			tile[ORANGE3].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Red" && player[PlayerNum - 1].getNumRed() == 3) {
			tile[RED1].setIsMonopolized();
			tile[RED2].setIsMonopolized();
			tile[RED3].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Yellow" && player[PlayerNum - 1].getNumYellow() == 3) {
			tile[YELLOW1].setIsMonopolized();
			tile[YELLOW2].setIsMonopolized();
			tile[YELLOW3].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Green" && player[PlayerNum - 1].getNumGreen() == 3) {
			tile[GREEN1].setIsMonopolized();
			tile[GREEN2].setIsMonopolized();
			tile[GREEN3].setIsMonopolized();
		}
		else if (tile[index].getColor() == "Dark_Blue" && player[PlayerNum - 1].getNumDarkBlue() == 2) {
			tile[DARK_BLUE1].setIsMonopolized();
			tile[DARK_BLUE2].setIsMonopolized();
		}
	}

}

//This function gets rid of a monopoly if they no longer meet the requirements of a monopoly.
void deMonopolize(Board tile[], Players player[], int index, int PlayerNum) {
	if (tile[index].getIsMonopolized()) {
		removeHouses(tile, player, index, PlayerNum);
		if (tile[index].getId() == "utility" && player[PlayerNum - 1].getNumUtilities() < 2) {
			tile[UTILITY1].unMonopolize();
			tile[UTILITY2].unMonopolize();
		}
		else if (tile[index].getId() == "railroad" && player[PlayerNum - 1].getNumUtilities() < 4) {
			tile[RAILROAD1].unMonopolize();
			tile[RAILROAD2].unMonopolize();
			tile[RAILROAD3].unMonopolize();
			tile[RAILROAD4].unMonopolize();
		}
		else if (tile[index].getId() == "bProperty") {
			if (tile[index].getColor() == "Brown" && player[PlayerNum - 1].getNumBrown() < 2) {
				tile[BROWN1].unMonopolize();
				tile[BROWN2].unMonopolize();
			}
			else if (tile[index].getColor() == "Light_Blue" && player[PlayerNum - 1].getNumLightBlue() < 3) {
				tile[LIGHT_BLUE1].unMonopolize();
				tile[LIGHT_BLUE2].unMonopolize();
				tile[LIGHT_BLUE3].unMonopolize();
			}
			else if (tile[index].getColor() == "Pink" && player[PlayerNum - 1].getNumPink() < 3) {
				tile[PINK1].unMonopolize();
				tile[PINK2].unMonopolize();
				tile[PINK3].unMonopolize();
			}
			else if (tile[index].getColor() == "Orange" && player[PlayerNum - 1].getNumOrange() < 3) {
				tile[ORANGE1].unMonopolize();
				tile[ORANGE2].unMonopolize();
				tile[ORANGE3].unMonopolize();
			}
			else if (tile[index].getColor() == "Red" && player[PlayerNum - 1].getNumRed() < 3) {
				tile[RED1].unMonopolize();
				tile[RED2].unMonopolize();
				tile[RED3].unMonopolize();
			}
			else if (tile[index].getColor() == "Yellow" && player[PlayerNum - 1].getNumYellow() < 3) {
				tile[YELLOW1].unMonopolize();
				tile[YELLOW2].unMonopolize();
				tile[YELLOW3].unMonopolize();
			}
			else if (tile[index].getColor() == "Green" && player[PlayerNum - 1].getNumGreen() < 3) {
				tile[GREEN1].unMonopolize();
				tile[GREEN2].unMonopolize();
				tile[GREEN3].unMonopolize();
			}
			else if (tile[index].getColor() == "Dark_Blue" && player[PlayerNum - 1].getNumDarkBlue() < 2) {
				tile[DARK_BLUE1].unMonopolize();
				tile[DARK_BLUE2].unMonopolize();
			}
		}
	}

}

//Forces the player to pay rent to another play, then the player either
//mortgages properties or declares bankruptcy
void rent(Board tile[], Players player[], int index, int playerNum) {
	int tempRent = 0;
	//checks if the property is not owned by the current player and that it
	//is not mortgaged.
	if (tile[index].getOwner() != playerNum && !tile[index].getIsMortgaged()) {
		cout << "This property is owned by Player " << tile[index].getOwner() << endl;
		//Sets the rent of buildableProperties
		if (tile[index].getId() == "bProperty") {
			tempRent = propertyRent(tile, player, index, playerNum);
		}
		//Sets the rent of utilities
		else if (tile[index].getId() == "utility") {
			tempRent = utilityRent(tile, player, index, playerNum);
		}
		//sets the rent of railroads
		else if (tile[index].getId() == "railroad") {
			tempRent = railroadRent(tile, player, index, playerNum);
		}
		cout << "You owe $" << tempRent << endl;
		checkMortgage(tile, player, index, playerNum, tempRent, "to pay for rent");
		if (tempRent > player[playerNum - 1].getMoney()) {
			forceBankruptcy(tile, player, index, playerNum, tempRent, "to pay for rent");
		}
		if (tempRent <= player[playerNum - 1].getMoney()) {
			player[playerNum - 1].subtractMoney(tempRent);
			cout << "Player " << playerNum << " paid Player " << tile[index].getOwner()
				<< " $" << tempRent << endl;
			player[tile[index].getOwner() - 1].addMoney(tempRent);
		}
	}
	else if (tile[index].getOwner() == playerNum) {
		cout << "This property is owned by YOU" << endl;
	}
	else if (tile[index].getIsMortgaged()) {
		cout << "This property is MORTGAGED" << endl;
	}
	if (player[playerNum - 1].getMoney() != -1) {
		cout << "You have $" << player[playerNum - 1].getMoney() << " left" << endl << endl;
	}
}

//This calculates the property rent and returns it to rent.
int propertyRent(Board tile[], Players player[], int index, int playerNum) {
	if (tile[index].getNumHouses() == 0 && !tile[index].getIsMonopolized()) {
		return tile[index].getRentPrice();
	}
	else if (tile[index].getNumHouses() == 0 && tile[index].getIsMonopolized()) {
		return (tile[index].getRentPrice() * 2);
	}
	else if (tile[index].getNumHouses() == 1) {
		return tile[index].getRent1();
	}
	else if (tile[index].getNumHouses() == 2) {
		return tile[index].getRent2();
	}
	else if (tile[index].getNumHouses() == 3) {
		return tile[index].getRent3();
	}
	else if (tile[index].getNumHouses() == 4) {
		return tile[index].getRent4();
	}
	else {
		return tile[index].getRentHotel();
	}
}

//This calculates the rent based on utility rent rules, then the player either
//pays the rent, mortgages properties, or declares bankruptcy
int utilityRent(Board tile[], Players player[], int index, int playerNum) {
	if (!tile[index].getIsMonopolized()) {
		return (4 * (player[playerNum - 1].getDie1() + player[playerNum - 1].getDie2()));
	}
	else {
		return (10 * (player[playerNum - 1].getDie1() + player[playerNum - 1].getDie2()));
	}
}

//This calculates the rent based on railroad rent rules, then the player either
//pays the rent, mortgages properties, or declares bankruptcy
int railroadRent(Board tile[], Players player[], int index, int playerNum) {
	if (player[tile[index].getOwner() - 1].getNumRailroads() == 2) {
		return 50;
	}
	else if (player[tile[index].getOwner() - 1].getNumRailroads() == 3) {
		return 100;
	}
	else if (player[tile[index].getOwner() - 1].getNumRailroads() == 4) {
		return 200;
	}
	else {
		return 25;
	}
}

//This forces the player to pay their taxes, mortgage properties, or declare bankruptcy
void tax(Board tile[], Players player[], int index, int playerNum) {
	int tempTax = tile[index].getRentPrice();
	cout << "You owe $" << tempTax << " for taxes" << endl;
	checkMortgage(tile, player, index, playerNum, tempTax, "to pay your taxes");
	if (tempTax > player[playerNum - 1].getMoney()) {
		forceBankruptcy(tile, player, index, playerNum, tempTax, "to pay your taxes");
	}
	if (player[playerNum - 1].getMoney() != -1) {
		player[playerNum - 1].subtractMoney(tempTax);
		//this adds to the price of free parking which is at index 20
		tile[F_PARKING].addPrice(tempTax);
		cout << "You have $" << player[playerNum - 1].getMoney() << " left" << endl << endl;
	}
}

//This functions checks if the player wants to mortgage their properties because
//they don't have enough money to pay for something.
void checkMortgage(Board tile[], Players player[], int index, int playerNum, int owed, string toPay) {
	string choice = "n";
	while (player[playerNum - 1].getMoney() < owed) {
		cout << "You don't have enough money " << toPay << endl
			<< "Would you like to build/mortgage your properties? (y or n): ";
		cin >> choice;
		if (choice == "Y" || choice == "y") {
			cout << "You owe $" << owed << endl << endl;
			buildMortgage(tile, player, index, playerNum);
		}
		else {
			break;
		}
	}
}

//Overloaded function based on the number of parameters. This checkMortgage
//allows players to build and mortgage their properties without forcing them to
void checkMortgage(Board tile[], Players player[], int index, int playerNum) {
	string choice = "n";
	while (player[playerNum - 1].getMoney() >= 0) {
		cout << "Would you like to build/mortgage your properties? (y or n): ";
		cin >> choice;
		cout << endl;
		if (choice == "Y" || choice == "y") {
			buildMortgage(tile, player, index, playerNum);
		}
		else {
			break;
		}
	}
}

//This prints off the list of properties for the current player
//Then it lets the player choose if they want to build or mortgage
void buildMortgage(Board tile[], Players player[], int index, int playerNum) {
	int i = 0;
	//represents property choice
	int choice = -1;
	//represents build or mortgage choice
	string choice2 = " ";
	int counter = 1;
	cout << "You have $" << player[playerNum - 1].getMoney() << endl << endl;
	cout << "Here is your list of properties:" << endl;
	//i is the position in the array that stores the indexes of the properties owned
	while (player[playerNum - 1].getSpacesOwnedIndex(i) != -1 && i != 28 && choice != 0) {
		//tileIndex is the index of the tiles that the player owns
		int tileIndex = player[playerNum - 1].getSpacesOwnedIndex(i);
		cout << counter << "." << endl << tile[tileIndex].getName();
		//checks to see if the tile has a color and prints it if it does
		if (tile[tileIndex].getColor() != " ") {
			cout << "(" << tile[tileIndex].getColor() << ")" << endl;
		}
		else {
			cout << endl;
		}
		if (tile[tileIndex].getIsMonopolized() && tile[tileIndex].getId() == "bProperty") {
			cout << "House Price: $" << tile[tileIndex].getPriceOfHouse() << endl;
			if (tile[tileIndex].getNumHouses() != 5) {
				cout << "Number of Houses: " << tile[tileIndex].getNumHouses() << endl;
			}
			else {
				cout << "Hotel" << endl;
			}
		}
		cout << "Mortgage Value: $" << tile[tileIndex].getMortgagePrice() << endl;
		if (tile[tileIndex].getIsMortgaged()) {
			cout << "MORTGAGED" << endl << endl;
		}
		else {
			cout << "UNMORTGAGED" << endl << endl;
		}
		i++;
		counter++;
		if ((i == 28 && choice > 0) || player[playerNum - 1].getSpacesOwnedIndex(i) == -1) {
			cout << "Please enter the number of the property you would like to build/mortgage/unmortgage\n"
				<< "Only enter 1 number at a time. Please enter an integer value (0 to end): ";
			cin >> choice;
			cout << endl;
			if (choice > 0 && choice <= i) {
				int tileIndex = player[playerNum - 1].getSpacesOwnedIndex(choice - 1);
				//if property is a buildable property, monopolized, and not mortgaged, and doesn't 
				//have mortgaged properties in its set.
				if (tile[tileIndex].getId() == "bProperty" && tile[tileIndex].getIsMonopolized() && !tile[tileIndex].getIsMortgaged()
					&& !checkIsMortgaged(tile, player, tileIndex, playerNum)) {
					cout << "Would you like to build or mortgage property? (Enter 'B' for build, 'M' for mortgage): ";
					cin >> choice2;
				}
				cout << endl;
				if (choice2 == "B" || choice2 == "b") {
					build(tile, player, tileIndex, playerNum);

				}
				else {
					mortgage(tile, player, tileIndex, playerNum);
				}
			}
			choice2 = "m";
			i = 0;
			counter = 1;
		}
	}
}

//This function allows players to add or remove houses 1 at a time
void build(Board tile[], Players player[], int index, int playerNum) {
	int choice = -1;
	int tempMoney = 0;
	int tempIndex = -1;
	int i = 0;
	int j = 0;
	int tempNumHouses = 0;
	int tempNumHouses2 = 0;
	int tempNumHouses3 = 0;
	int otherPropertiesIndex[] = { -1, -1 };
	string tempColor = " ";

	cout << "NOTE: The number of houses for a property can only exceed the minimum number of \n"
		<< "houses, in that color set, by 1\n"
		<< "(The number of houses for the other properties in the set\n"
		<< "will be automatically adjusted to ensure this stays true)" << endl;
	cout << "Adding a 5th house is the same as adding a hotel" << endl << endl;
	cout << "How many houses would you like to add? (0 to end): ";
	cin >> choice;
	if (choice > 0 && choice <= 5 - tile[index].getNumHouses()) {
		tempMoney = choice * tile[index].getPriceOfHouse();
		tempColor = tile[index].getColor();
		tempNumHouses = choice;
		//If color is not Brown or Dark_Blue, find two other properties
		if (tempColor != "Brown" && tempColor != "Dark_Blue") {
			while (i < 28 && player[playerNum - 1].getSpacesOwnedIndex(i) != -1 && j < 2) {
				tempIndex = player[playerNum - 1].getSpacesOwnedIndex(i);
				if (tile[tempIndex].getColor() == tempColor && tempIndex != index) {
					otherPropertiesIndex[j] = tempIndex;
					j++;
				}
				i++;
			}
		}
		//if color is Brown or Dark_Blue, find one other property.
		else {
			while (i < 28 && player[playerNum - 1].getSpacesOwnedIndex(i) != -1 && j < 1) {
				tempIndex = player[playerNum - 1].getSpacesOwnedIndex(i);
				if (tile[tempIndex].getColor() == tempColor && tempIndex != index) {
					otherPropertiesIndex[j] = tempIndex;
					j++;
				}
				i++;
			}
		}
		//While the first other property's number of houses is more than 1 less 
		//than the property we are building on, add up the money it would take to
		//get the first other property to have the number of houses to be 1 less
		//than the property we are building on
		for (int k = tile[otherPropertiesIndex[0]].getNumHouses(); k < tile[index].getNumHouses() + choice - 1; k++) {
			tempMoney += tile[index].getPriceOfHouse();
			tempNumHouses2 += 1;
		}
		//If there is a second other property
		if (j == 2) {
			//While the second other property's number of houses is more than 1 less 
			//than the property we are building on, add up the money it would take to
			//get the second other property to have the number of houses to be 1 less
			//than the property we are building on
			for (int k = tile[otherPropertiesIndex[1]].getNumHouses(); k < tile[index].getNumHouses() + choice - 1; k++) {
				tempMoney += tile[index].getPriceOfHouse();
				tempNumHouses3 += 1;
			}
		}
		//If the player has enough money for all the houses
		if (player[playerNum - 1].getMoney() >= tempMoney) {
			//sets the number of houses for the property we are currently building
			//on and subtracts money from the player
			for (int k = 0; k < choice; k++) {
				tile[index].addHouse();
				player[playerNum - 1].subtractMoney(tile[index].getPriceOfHouse());
			}
			cout << "Player " << playerNum << " added " << tempNumHouses << " houses to "
				<< tile[index].getName() << " (" << tile[index].getColor() << ")" << endl;
			//While the first other property's number of houses is more than 1 less 
			//than the property we are building on, add the number of houses it would take to
			//get the first other property to have the number of houses to be 1 less
			//than the property we are building on
			//Then subtract the house price from the player
			for (int k = tile[otherPropertiesIndex[0]].getNumHouses(); k < tile[index].getNumHouses() - 1; k++) {
				tile[otherPropertiesIndex[0]].addHouse();
				player[playerNum - 1].subtractMoney(tile[index].getPriceOfHouse());
			}
			cout << "Player " << playerNum << " added " << tempNumHouses2 << " houses to "
				<< tile[otherPropertiesIndex[0]].getName() << " (" << tile[otherPropertiesIndex[0]].getColor()
				<< ")" << endl;
			//If there is a second other property
			if (j == 2) {
				//While the second other property's number of houses is more than 1 less 
				//than the property we are building on, add the number of houses it would take to
				//get the second other property to have the number of houses to be 1 less
				//than the property we are building on
				//Then subtract the house price from the player
				for (int k = tile[otherPropertiesIndex[1]].getNumHouses(); k < tile[index].getNumHouses() - 1; k++) {
					tile[otherPropertiesIndex[1]].addHouse();
					player[playerNum - 1].subtractMoney(tile[index].getPriceOfHouse());
				}
				cout << "Player " << playerNum << " added " << tempNumHouses3 << " houses to "
					<< tile[otherPropertiesIndex[1]].getName() << " (" << tile[otherPropertiesIndex[1]].getColor()
					<< ")" << endl;
			}
		}
		//If the player doesn't have enough money
		else {
			cout << "Player " << playerNum << ", you don't have enough money to build "
				<< tempNumHouses + tempNumHouses2 + tempNumHouses3 << " houses" << endl;
		}
	}
	//If the player entered a number outside of how many houses the person can build
	else if (choice != 0) {
		cout << "You can't build " << choice << " houses on " << tile[index].getName()
			<< " (" << tile[index].getColor() << ")" << endl;
	}
	cout << "You now have $" << player[playerNum - 1].getMoney();
	cout << endl;
}

//This function removes the houses from every property in that color if
//one has been mortgaged, and it adds the cost of those houses to the 
//player's money
void removeHouses(Board tile[], Players player[], int index, int playerNum) {
	int i = 0;
	int tempIndex = -1;
	int tempMoney = 0;
	string tempColor = tile[index].getColor();
	while (i < 28 && player[playerNum - 1].getSpacesOwnedIndex(i) != -1) {
		tempIndex = player[playerNum - 1].getSpacesOwnedIndex(i);
		//if a tile is the same color as the tile being mortgaged, remove all the houses
		//from it and pay the user for all those houses. Then setNumHouses = 0;
		if (tile[tempIndex].getColor() == tempColor) {
			tempMoney = tile[tempIndex].getNumHouses() * tile[tempIndex].getPriceOfHouse();
			player[playerNum - 1].addMoney(tempMoney);
			tile[tempIndex].setHouseZero();
		}
		i++;
	}
}


//Checks if there is a mortgaged property in a set
bool checkIsMortgaged(Board tile[], Players player[], int index, int playerNum) {
	int i = 0;
	int tempIndex = -1;
	string tempColor = tile[index].getColor();
	while (i < 28 && player[playerNum - 1].getSpacesOwnedIndex(i) != -1) {
		tempIndex = player[playerNum - 1].getSpacesOwnedIndex(i);
		if (tile[tempIndex].getColor() == tempColor && tile[tempIndex].getIsMortgaged()) {
			return true;
		}
		i++;
	}
	return false;
}

//This mortgages or unmortgages a property depending on what state it is in, then
//it adds or subtracts from the players money.
void mortgage(Board tile[], Players player[], int index, int playerNum) {
	//If the tile is unmortgaged and the number of houses is 0
	if (!tile[index].getIsMortgaged() && tile[index].getNumHouses() == 0) {
		player[playerNum - 1].addMoney(tile[index].getMortgagePrice());
		cout << "Player " << playerNum << " mortgaged " << tile[index].getName();
		if (tile[index].getColor() != " ") {
			cout << "(" << tile[index].getColor() << ")" << endl;
		}
		else {
			cout << endl;
		}
	}
	//if the tile is not mortgaged and the number of houses is not 0
	else if (!tile[index].getIsMortgaged() && tile[index].getIsMonopolized()) {
		removeHouses(tile, player, index, playerNum);
		//adds mortgage price on at the end since the property will still be mortgaged.
		player[playerNum - 1].addMoney(tile[index].getMortgagePrice());
	}
	//if the tile is mortgaged 
	else if (tile[index].getIsMortgaged()) {
		//If player has enough money
		if (player[playerNum - 1].getMoney() >= tile[index].getMortgagePrice()) {
			player[playerNum - 1].subtractMoney(tile[index].getMortgagePrice());
			cout << "Player " << playerNum << " unmortgaged " << tile[index].getName();
			if (tile[index].getColor() != " ") {
				cout << "(" << tile[index].getColor() << ")" << endl;
			}
			else {
				cout << endl;
			}
		}
		//If player doesn't have enough money
		else {
			//reverses the mortgage status because it will be reversed again at
			//the end of this function.
			tile[index].setIsMortgaged();
			cout << "You don't have enough to unmortgage that property" << endl;
		}
	}
	cout << "You now have $" << player[playerNum - 1].getMoney() << endl;
	tile[index].setIsMortgaged();
}



//Forces a player into a bankrupt state if they don't have enough money to pay for something
//that they have to pay for, such as rent or taxes.
void forceBankruptcy(Board tile[], Players player[], int index, int playerNum, int owed, string toPay) {
	if (owed > player[playerNum - 1].getMoney()) {
		cout << "You don't have enough money to pay rent\n"
			<< "You must declare bankruptcy\n";
		player[playerNum - 1].setMoney(-1);
	}
}
//This function allows the player to use a get out of jail
//free card, roll for doubles, or pay the $50 fine to get out
//of jail. You can only be in jail for three turns, then it 
//forces you out.
void jailTurn(Board tile[], Players player[], int playerNum) {
	player[playerNum - 1].addNumTurnsInJail();
	cout << "Turn in Jail: " << player[playerNum - 1].getNumTurnsInJail() << endl;
	//checks if the player has at least 1 get out of jail free card
	if (player[playerNum - 1].getNumGetOutOfJailCards() > 0) {
		//asks the player if they want to use said card
		if (MessageBox::Show("Player " + (playerNum) + "\n" + "Do you want to use a\n"
			+ "Get Out of Jail Free Card?", "Jail", MessageBoxButtons::YesNo,
			MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
			player[playerNum - 1].setNumTurnsInJailZero();
			player[playerNum - 1].subtractNumGetOutOfJailCards();
			player[playerNum - 1].setPosition(JUST_VISITING + 1);
			if (player[playerNum - 1].getNumTurnsInJail() != 3) {
				return;
			}
		}
	}
	//Asks the player if they want to roll for doubles.
	if (MessageBox::Show("Player " + (playerNum)+"\n" + "Do you want to roll\n"
		+ "For Doubles?", "Jail", MessageBoxButtons::YesNo,
		MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
		player[playerNum - 1].rollDice();
		if (player[playerNum - 1].getNumTurnsInJail() != 3) {
			return;
		}
	}
	else {
		if (MessageBox::Show("Player " + (playerNum)+"\n" + "Do you want to pay\n"
		+ "the $50 fine?", "Jail", MessageBoxButtons::YesNo,
		MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
			player[playerNum - 1].setNumTurnsInJailZero();
			player[playerNum - 1].subtractMoney(50);
			player[playerNum - 1].setPosition(JUST_VISITING + 1);
			player[playerNum - 1].rollDice();
			if (player[playerNum - 1].getNumTurnsInJail() != 3) {
				return;
			}
		}
	}
	if (player[playerNum - 1].getNumTurnsInJail() == 3) {
		if (MessageBox::Show("Player " + (playerNum)+"\n" + "You have to pay\n"
			+ "the 50 fine.", "Jail", MessageBoxButtons::OK,
			MessageBoxIcon::Exclamation) == System::Windows::Forms::DialogResult::OK) {
			player[playerNum - 1].setNumTurnsInJailZero();
			player[playerNum - 1].subtractMoney(50);
			player[playerNum - 1].setPosition(JUST_VISITING + 1);
			player[playerNum - 1].rollDice();
		}
	}
}

//This function gives all properties from one player to the player that made them go 
//bankrupt
void giveOnePlayerProperties(Board tile[], Players player[], int index, int playerNum) {
	int i = 0;
	
	while (i < 28 && player[playerNum - 1].getSpacesOwnedIndex(i) != -1) {
		giveTile(tile, player, player[playerNum - 1].getSpacesOwnedIndex(i), tile[index].getOwner());
		i++;
	}
}

//This function 
void giveUpProperties(Board tile[], Players player[], int index, int playerNum) {
	//keeping track of space indexes
	int i = 0;
	//keeping track of player nums with j acting as an index
	int j;
	if (playerNum < NUM_PLAYERS) {
		j = playerNum + 1; //playerNum is 1 higher than the actual player index.
		//so this starts at the player after the player who just declared bankruptcy.
	}
	else {
		j = 1;
	}
	
	while (i < 28 && player[playerNum - 1].getSpacesOwnedIndex(i) != -1) {
		//if the property being given up is monopolized
		if (tile[player[playerNum - 1].getSpacesOwnedIndex(i)].getIsMonopolized()) {
			tile[player[playerNum - 1].getSpacesOwnedIndex(i)].unMonopolize();
		}
		//if the number of houses on the property is more than zero, set it to zero
		if (tile[player[playerNum - 1].getSpacesOwnedIndex(i)].getNumHouses() != 0) {
			tile[player[playerNum - 1].getSpacesOwnedIndex(i)].setHouseZero();
		}
		if (!(player[j-1].getIsBankrupt())) {
			giveTile(tile, player, player[playerNum - 1].getSpacesOwnedIndex(i), j);
			//Only increment i when the property has been given away.
			i++;
		}
		//j can only be incremented up to NUM_PLAYERS.
		if (j < NUM_PLAYERS) {
			j++;
		}
		else {
			j = 1;
		}
	}
}

//This function allows a player to choose what player they want to trade with
//Then it moves into the actual trading portion.
void initializeTrade(Board tile[], Players player[], int playerNum) {
	int otherPlayerNum = 0;
	do {
		cout << "Which player would you like to trade with?" << endl;
		for (int i = 0; i < NUM_PLAYERS; i++) {
			if (!player[i].getIsBankrupt() && i != playerNum - 1) {
				cout << "Player " << i + 1 << endl << endl;
			}
		}
		cout << "Please enter the number of the player you would like to trade with: ";
		cin >> otherPlayerNum;
		//This checks that the number entered is in the expected range, the proposed player is not bankrupt
		//and the proposed player is not the current player.
		if (!cin || otherPlayerNum == playerNum || player[otherPlayerNum].getIsBankrupt() || otherPlayerNum < 1
			|| otherPlayerNum > NUM_PLAYERS) {
			cout << "Please enter a valid player, this player can't be you nor can they be bankrupt." << endl;
		}
	//This checks that the number entered is in the expected range, the proposed player is not bankrupt
	//and the proposed player is not the current player.
	} while (!cin || otherPlayerNum == playerNum || player[otherPlayerNum].getIsBankrupt() || otherPlayerNum < 1
		|| otherPlayerNum > NUM_PLAYERS);
	trade(tile, player, playerNum, otherPlayerNum);
}

//This function prints all the properties these two players can trade, and allows
//the current player to propose a trade.
void trade(Board tile[], Players player[], int playerNum, int otherPlayerNum) {
	const int ONE = 1;
	const int FIVE = 5;
	const int SEVEN = 7;
	const int EIGHT = 8;
	const int TEN = 10;
	const int FIFTEEN = 15;
	const int SEVENTEEN = 17;
	const int EIGHTEEN = 18;
	const int TWENTY_FOUR = 24;
	const int TWENTY_FIVE = 25;


	int counter1 = 1;
	int counter2 = 1;
	int temp;
	vector <int> trade1;
	vector <int> trade2;
	system("cls");
	//This prints off the beginning of each column for the players.
	cout << setw(SEVEN) << left << "Player " << setw(EIGHTEEN)<< playerNum 
		<< setw(SEVEN) << "Player" << setw(EIGHTEEN) << otherPlayerNum << endl;
	cout << setw(TEN) << "You have $" << setw(FIFTEEN) << player[playerNum - 1].getMoney() 
		<< setw(TEN) << "You have $" << setw(FIFTEEN) << player[otherPlayerNum -1].getMoney() << endl << endl;
	cout << setw(TWENTY_FIVE) << "You have: " << setw(TWENTY_FIVE) << "You have: " << endl;
	//i is the position in the array that stores the indexes of the properties owned
	int i = 0;
	//while either player still has properties left or they have not reached the end of their property list.
	while ((player[playerNum - 1].getSpacesOwnedIndex(i) != -1 || player[otherPlayerNum-1].getSpacesOwnedIndex(i) != -1)
		&& i != 28) {
		//tileIndex is the index of the tiles that the player owns
		//tileIndex2 is the index of the tiles that the other player owns.
		int tileIndex = player[playerNum - 1].getSpacesOwnedIndex(i);
		int tileIndex2 = player[otherPlayerNum - 1].getSpacesOwnedIndex(i);
		//if tileIndex exists
		if (tileIndex != -1) {
			cout << setw(ONE) << left << counter1 << setw(TWENTY_FOUR) << ".";
			counter1 += 1;
		}
		else {
			cout << setw(TWENTY_FIVE) << left << " ";
		}
		//if tileIndex2 exists
		if (tileIndex2 != -1) {
			cout << setw(ONE) << left << counter2 << setw(TWENTY_FOUR) << ".";
			counter2 += 1;
		}
		else {
			cout << setw(TWENTY_FIVE) << left << " ";
		}
		cout << endl;
		//Checks if the current player has a property at position i in their array
		//If they don't, we still need to format the column.
		if (tileIndex != -1) {
			cout << left <<setw(TWENTY_FIVE) << tile[tileIndex].getName();
		}
		else {
			cout << left << setw(TWENTY_FIVE) << " ";
		}
		
		//Checks if the other player has a property at position i in their array
		//If they don't, we still need to format the column.
		if (tileIndex2 != -1) {
			cout << left <<setw(TWENTY_FIVE) << tile[tileIndex2].getName();
		}
		else {
			cout << left << setw(TWENTY_FIVE) << " ";
		}
		cout << endl;

		//Checks if the current player has a property at position i in their array
		//If they don't, we still need to format the column.
		//checks to see if the tile has a color and prints it if it does
		if (tileIndex != -1 && tile[tileIndex].getColor() != " ") {
			cout << left << setw(ONE) << "(" << setw(TWENTY_FOUR) << (tile[tileIndex].getColor() + ")");

		}
		else {
			cout <<left <<  setw(TWENTY_FIVE) << " ";
		}

		//Checks if the other player has a property at position i in their array
		//If they don't, we still need to format the column.
		//checks to see if the tile has a color and prints it if it does
		if (tileIndex2 != -1 && tile[tileIndex2].getColor() != " ") {
			cout << left << setw(ONE) << "(" << setw(TWENTY_FOUR) << (tile[tileIndex2].getColor() + ")");
		}
		else {
			cout << setw(TWENTY_FIVE) << " ";
		}
		cout << endl;

		//Prints mortgage value if it exists for current player
		if (tileIndex != -1) {
			cout << left <<setw(SEVENTEEN) << "Mortgage Value: $" << setw(EIGHT) << tile[tileIndex].getMortgagePrice();
		}
		else {
			cout << left << setw(TWENTY_FIVE) << " ";
		}

		//prints mortgage value if it exists for other player
		if (tileIndex2 != -1) {
			cout << left << setw(SEVENTEEN) << left << "Mortgage Value: $" << setw(EIGHT) << tile[tileIndex2].getMortgagePrice();
		}
		else {
			cout << left << setw(TWENTY_FIVE) << " ";
		}
		cout << endl;
		
		//Checks if a tile exists and prints mortgaged or unmortgaged for current player
		if (tile[tileIndex].getIsMortgaged() && tileIndex != -1) {
			cout << left << setw(TWENTY_FIVE) << "MORTGAGED";
		}
		else if(tileIndex != -1){
			cout << left << setw(TWENTY_FIVE) << "UNMORTGAGED";
		}
		else {
			cout << left << setw(TWENTY_FIVE) << " ";
		}

		//Checks if a tile exists and prints mortgaged or unmortgaged for other player
		if (tile[tileIndex2].getIsMortgaged() && tileIndex2 != -1) {
			cout << left << setw(TWENTY_FIVE) << "MORTGAGED";
		}
		else if (tileIndex2 != -1) {
			cout << left << setw(TWENTY_FIVE) << "UNMORTGAGED";
		}
		else {
			cout << left << setw(TWENTY_FIVE) << " ";
		}
		cout << endl << endl;
		i++;
	}

	cout << "Which properties would you like to propose from player " << playerNum << "?" << endl;
	cout << "Please enter this as a list of numbers separated by spaces (end with a '.' or other character): ";
	while (true) {
		cin >> temp;
		temp = player[playerNum-1].getSpacesOwnedIndex(temp - 1);
		trade1.push_back(temp);
		if (cin.peek() == '\n') {
			temp = 0;
			break;
		}
	}
	cout << endl;
	cout << endl;
	cout << "Which properties would you like to propose from player " << otherPlayerNum << "?" << endl;
	cout << "Please enter this as a list of numbers separated by spaces: ";
	while (true) {
		cin >> temp;
		temp = player[otherPlayerNum - 1].getSpacesOwnedIndex(temp - 1);
		trade2.push_back(temp);
		if (cin.peek() == '\n') {
			temp = 0;
			break;
		}
	}
	//NEED TO PRINT PROPERTIES HERE AGAIN AND HAVE OTHER PLAYER ACCEPT THE TRADE

	cout << endl;
	cout << endl;
	//removes tile from current player and gives it to other player
	//Then pops the value out of the vector
	for (int i = trade1.size() - 1; i >= 0; i--) {
		removeTile(tile, player, trade1[i], playerNum);
		giveTile(tile, player, trade1[i], otherPlayerNum);
		trade1.pop_back();
	}
	//removes tile from other player and gives it to current player
	//then pops the value out of the vector.
	for (int i = trade2.size() - 1; i >= 0; i--) {
		removeTile(tile, player, trade2[i], otherPlayerNum);
		giveTile(tile, player, trade2[i], playerNum);
		trade2.pop_back();
	}
}

//This function allows the current player to declare bankruptcy
//at the end of their turn
int declareBankruptcy(Board tile[], Players player[], int index, int playerNum) {
	if (player[playerNum - 1].getMoney() == -1) {
		player[playerNum - 1].setBankrupt();
		cout << "You declared bankruptcy. Goodbye!" << endl << endl;
		num_bankrupt += 1;
		//If the player was forced into bankruptcy and is on a property
		if (tile[index].getId() == "bProperty" || tile[index].getId() == "utility" || tile[index].getId() == "railroad") {
			cout << "Giving one player properties" << endl;
			giveOnePlayerProperties(tile, player, index, playerNum);
			return 1;
		}
	}
	else {
		player[playerNum - 1].setBankrupt();
		cout << "You declared bankruptcy. Goodbye!" << endl << endl;
	}
	cout << "Giving ALL players Properties" << endl;
	giveUpProperties(tile, player, index, playerNum);
	return 1;
}

#endif // !H_Functions
