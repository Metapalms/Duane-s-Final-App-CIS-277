#pragma once
// BlackJack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

//list of all cards done in an two dimentional array because for me it seemed easier to keep everythign in order
string drawPile[4][13] = {
  {"A Spade   ", "2 Spade   ", "3 Spade   ", "4 Spade   ", "5 Spade   ", "6 Spade   ", "7 Spade   ", "8 Spade   ", "9 Spade   ", "10 Spade  ", "J Spade   ", "Q Spade   ", "K Spade   "},
  {"A Heart   ", "2 Heart   ", "3 Heart   ", "4 Heart   ", "5 Heart   ", "6 Heart   ", "7 Heart   ", "8 Heart   ", "9 Heart   ", "10 Heart  ", "J Heart   ", "Q Heart   ", "K Heart   "},
  {"A Diamond ", "2 Diamond ", "3 Diamond ", "4 Diamond ", "5 Diamond ", "6 Diamond ", "7 Diamond ", "8 Diamond ", "9 Diamond ", "10 Diamond", "J Diamond ", "Q Diamond ", "K Diamond "},
  {"A Club    ", "2 Club    ", "3 Club    ", "4 Club    ", "5 Club    ", "6 Club    ", "7 Club    ", "8 Club    ", "9 Club    ", "10 Club   ", "J Club    ", "Q Club    ", "K Club    "}
};
//cards in people's hands (playerCards[whatPlayer][whatTurn])
//blank because they are set to display from the beginning and they fill in as they get drawn
string playerCards[5][7] = {
	{ "          ", "          ", "          ", "          ", "          ", "          ", "          " },
	{ "          ", "          ", "          ", "          ", "          ", "          ", "          " },
	{ "          ", "          ", "          ", "          ", "          ", "          ", "          " },
	{ "          ", "          ", "          ", "          ", "          ", "          ", "          " },
	{ "          ", "          ", "          ", "          ", "          ", "          ", "          " }
};
//An array for player values (playerValues[whatDoes][whatPlayer])
//0) playerTotals - adds as total 
//1) ammoutHave -
//2) ammountBet -
//3) ifSplitOrDouble - 1 for split, 2 for double
//4) ifWon - -1 for nothing, 0 if bust, 1 if lost, 2 if blackjack, 3 if won, 4 match dealer, 5 if surrender
double playerValues[5][5] = {
	{0, 0, 0,  0, 0},
	{0, 0, 0,  0, 0},
	{0, 0, 0,  0, 0},
	{0, 0, 0,  0, 0},
	{-1, -1, -1,  -1, -1}
};
//Then just an array of 2 for min and max bet.
//betValues[0] = min bet 
//betValues[1] = max bet
int betValues[2] = { 0,0 };


//Prototypes
void displayBoard(int numberOfPlayers, int turnsTaken, int dealerTurnsTaken);
void drawCard(int whatPlayer, int turnsTaken);
void redoDeck();
int dealerBelatedTotal(int dealerTurnsTaken);  //the total I want to be shown hides one of the cards
void aceOutput(int whatplayer, bool ifBelated, int belatedTotal);
void ifBust(int whatPlayer);
bool finishDealer();
void checkWinMatch();
void betUpDate();



void blackJackProgram() {
	//I like to set all varables which I plan to use at the beginning
	int numberOfPlayers;
	int turnsTaken = 0;
	int dealerTurnsTaken = 0;
	int startDollarAmount;
	char anotherRound;
	int anotherRound_bool = 0;
	

	cout << endl << "Welcome to 21 BackJack." << endl;
	cout << "How many people would be playing? (Between 1 & 4): "; //gets number of poeple
	cin >> numberOfPlayers;

	//display board fort a starter
	displayBoard(numberOfPlayers, turnsTaken, dealerTurnsTaken);

	cout << "\nHow much money should everyone start with? (0 if don't want to do bets): ";
	cin >> startDollarAmount;

	if (startDollarAmount != 0) {
		//Gives all players the startDollarAmount
		for (int x = 1; x <= numberOfPlayers; x++) {
			playerValues[1][x] = startDollarAmount;
		}

		cout << "What would you like to be the min then max bet? (Separated by a space): ";
		cin >> betValues[0] >> betValues[1];
	}

	
	do {
		if (startDollarAmount != 0) {
			//outputs the max and min bets and then gets player bets
			cout << "\nMin: " << betValues[0] << "     Max: " << betValues[1] << endl;
			for (int x = 1; x <= numberOfPlayers; x++) {
				cout << "Player " << x << ": How much would you like to bet? ";
				cin >> playerValues[2][x];
				while (playerValues[2][x] < betValues[0] || playerValues[2][x] > betValues[1]) {
					cout << "Please Eneter a valid input: ";
					cin >> playerValues[2][x];
				}
				playerValues[1][x] -= playerValues[2][x];
			}
		}

		//First 2 turns have no actual interaction in terms of choices
		for (int y = 1; y <= 2; y++) {
			//to automatically have the turns drawn
			for (int x = 1; x <= numberOfPlayers; x++) {
				drawCard(x, turnsTaken);
				displayBoard(numberOfPlayers, turnsTaken, dealerTurnsTaken);
			}
			//displayBoard(numberOfPlayers); //take out only for testing
			//after players have their cards the dealer gets a card, though for the second card it doesn't show till after the players have had their third turn. Would be easier to just have him draw and show a card later but I want it to actually have the deck as it should be in real life. 
			drawCard(0, turnsTaken);
			turnsTaken++;
			dealerTurnsTaken++;
			displayBoard(numberOfPlayers, turnsTaken, dealerTurnsTaken); //take out only for testing
		}
		displayBoard(numberOfPlayers, turnsTaken, dealerTurnsTaken);


		for (int x = 1; x <= numberOfPlayers; x++) {
			turnsTaken = 2;
			char playerChoice;
			bool repeatChoice;


			do {
				do {
					cout << "\nPlayer " << x << ": Would you like to hit or surrender? (Y or N or S): ";
					cin >> playerChoice;

					if (playerChoice == 'Y' || playerChoice == 'y') {
						drawCard(x, turnsTaken);
						repeatChoice = false;
					}
					else if (playerChoice == 'N' || playerChoice == 'n') {
						repeatChoice = false;
					}
					else if (playerChoice == 'S' || playerChoice == 's') {
						playerValues[4][x] = 5;
						repeatChoice = false;
					}
					else {
						cout << "Player " << x << ": Please enter a valid input ";
						repeatChoice = true;
					}
				} while (repeatChoice);

				ifBust(x);
				displayBoard(numberOfPlayers, turnsTaken, dealerTurnsTaken);
				turnsTaken++;
			} while (playerValues[4][x] == -1 && playerChoice == 'y');
		}

		//after all players have taken there the dealer gets a card and should show the previous card
		turnsTaken = 2;
		do {
			drawCard(0, turnsTaken);
			turnsTaken++;
			dealerTurnsTaken++;
			displayBoard(numberOfPlayers, turnsTaken, dealerTurnsTaken);
		} while (finishDealer());

		checkWinMatch();
		betUpDate();
		displayBoard(numberOfPlayers, turnsTaken, dealerTurnsTaken);

		do {
			cout << "\nWould you like to do another round? (Y or N): ";
			cin >> anotherRound;
			if (anotherRound == 'Y' || anotherRound == 'y') {
				anotherRound_bool = 1;
				anotherRound = 'y';
			}
			else if (anotherRound == 'N' || anotherRound == 'n') {
				anotherRound_bool = 0;
				anotherRound = 'y';
			}
		} while (anotherRound != 'y');
	} while (anotherRound_bool == 1);
}



//*********************************************************************
//                      displayBoard
//   Sets up and displays the output for the whole board
//**********************************************************************

void displayBoard(int numberOfPlayers, int turnsTaken, int dealerTurnsTaken) {
	cout << fixed << right << setprecision(0) << endl << endl << endl;
	cout << setw(3) << "Dealer";

	//showing all the players name
	for (int x = 1; x <= numberOfPlayers; x++) {
		cout << setw(15) << "Player " << x;
	}

	//showing how much each person has
	cout << endl << " " << setw(15); //just to get the first value in place
	for (int x = 1; x < 5; x++) {
		cout << "$" << playerValues[1][x];
		//now just stuff to make it look better. 
		//This will be the setting up for the next player
		//we don't want the last person on the line above to have a setw
		if (x != 4) {
			if (playerValues[1][x] < 10)
				cout << setw(15);
			else if (playerValues[1][x] < 100)
				cout << setw(14);
			else if (playerValues[1][x] < 1000)
				cout << setw(13);
			else if (playerValues[1][x] < 10000)
				cout << setw(12);
			else if (playerValues[1][x] < 100000)
				cout << setw(11);
			else if (playerValues[1][x] < 1000000)
				cout << setw(10);
		}
	}

	//showing people's bet
	cout << endl << " " << setw(20);
	for (int x = 1; x < 5; x++) {
		cout << "Bet: $" << playerValues[2][x];
		//now just stuff to make it look better. 
		//This will be the setting up for the next player
		if (x != 4) {
			if (playerValues[2][x] < 10)
				cout << setw(15);
			else if (playerValues[2][x] < 100)
				cout << setw(14);
			else if (playerValues[2][x] < 1000)
				cout << setw(13);
			else if (playerValues[1][x] < 10000)
				cout << setw(12);
			else if (playerValues[1][x] < 100000)
				cout << setw(11);
			else if (playerValues[1][x] < 1000000)
				cout << setw(10);
		}
	}

	// now showing the cards that the players have
	for (int x = 0; x < 5; x++) {
		//for the hidden values of the dealer
		cout << endl;
		if (x == 0 && turnsTaken == 1)
			cout << "[???]     " << "       ";
		else if (x == 1 && dealerTurnsTaken == 2)
			cout << "[???]     " << "       ";
		else
			cout << playerCards[0][x] << "       ";

		//displaying the cards 
		for (int y = 1; y < 5; y++) {
			cout << playerCards[y][x] << "      ";
		}
	}

	//This is just to help make the output look better by setting the dashes underneath neither to long or too short.
	//Have initialized with 65 beacuse if not I get "warning C6001:using unitialized memory"
	int numberOfDashes = 65;
	if (numberOfPlayers == 1)
		numberOfDashes = 24;
	else if (numberOfPlayers == 2)
		numberOfDashes = 40;
	else if (numberOfPlayers == 3)
		numberOfDashes = 54;
	else if (numberOfPlayers == 4)
		numberOfDashes = 65;

	cout << endl;
	for (int x = 1; x <= numberOfDashes; x++)
		cout << "-";


	//Once agian this is long and drawn out for purposes of makit the totals look good.
	//I could just do this all in the same line but the location would be different whether it is a 2 digit or 1 digit number
	cout << endl;
	if (playerValues[0][0] == 0)
		cout << playerValues[0][0] << "                ";
	else if (dealerTurnsTaken < 3) {
		if (dealerBelatedTotal(dealerTurnsTaken) >= 1000)
			aceOutput(0, true, dealerBelatedTotal(dealerTurnsTaken));
		else {
			if (dealerBelatedTotal(dealerTurnsTaken) < 10)
				cout << dealerBelatedTotal(dealerTurnsTaken) << "                ";
			else
				cout << dealerBelatedTotal(dealerTurnsTaken) << "               ";
		}
	}
	else if (playerValues[0][0] >= 1000) {
		aceOutput(0, false, 0);
	}
	else {
		cout << playerValues[0][0];
		if (playerValues[0][0] < 10)
			cout << "                ";
		else
			cout << "               ";
	}


	//now for player totals
	for (int x = 1; x < 5; x++) {
		//if ace send to aceOutput
		if (playerValues[0][x] >= 1000) {
			aceOutput(1, false, 0);
		}
		else {
			cout << playerValues[0][x];
			if (playerValues[0][x] < 10)
				cout << "               ";
			else
				cout << "              ";
		}
	}


	/*
	if (playerValues[0][1] >= 1000) {
		aceOutput(1, false, 0);
	}
	else {
		cout << playerValues[0][1];
		if (playerValues[0][1] < 10)
			cout << setw(13);
		else
			cout << setw(14);
	}

	if (playerValues[0][2] >= 1000) {
		aceOutput(2, false, 0);
	}
	else {
		cout << playerValues[0][2];
		if (playerValues[0][2] < 10)
			cout << setw(13);
		else
			cout << setw(14);
	}

	if (playerValues[0][3] >= 1000) {
		aceOutput(3, false, 0);
	}
	else {
		cout << playerValues[0][3];
		if (playerValues[0][3] < 10)
			cout << setw(13);
		else
			cout << setw(14);
	}

	if (playerValues[0][4] >= 1000) {
		aceOutput(4, false, 0);
	}
	else {
		cout << playerValues[0][4];
		if (playerValues[0][4] < 10)
			cout << setw(13);
		else
			cout << setw(14);
	}
	*/


	cout << endl;
	cout << "               "; //dealer buffer
	for (int x = 1; x < 5; x++) {
		if (playerValues[4][x] == -1)
			cout << "         " << "  ";
		else if (playerValues[4][x] == 0)
			cout << "Bust     " << "  ";
		else if (playerValues[4][x] == 1)
			cout << "Lost     " << "  ";
		else if (playerValues[4][x] == 2)
			cout << "BlackJack" << "  ";
		else if (playerValues[4][x] == 3)
			cout << "Won      " << "  ";
		else if (playerValues[4][x] == 4)
			cout << "Push     " << "  ";
		else if (playerValues[4][x] == 5)
			cout << "Surrender" << "  ";

		cout << setw(14);
	}

}



//*********************************************************************
//                      drawCard
//   Using a random number generator it will draw a random card. From there 
//   it will asign the value of that card to whatPlayer it is
//**********************************************************************

void drawCard(int whatPlayer, int turnsTaken) {
	int randomNumber, randomNumber2;
	int emptyDeck =0;

	//First just checking to see if all cards have been drawn
	//If all 52 cards are drawn then we redo the deck
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 13; y++) {
			if (drawPile[x][y] == "x")
				emptyDeck++;
		}
	}
	if (emptyDeck == 52)
		redoDeck();


	//okay now on to the actual drawing of the cards
	do {
		randomNumber = rand() % 4;
		randomNumber2 = rand() % 13;
	} while (drawPile[randomNumber][randomNumber2] == "x");


	int firstSpotValue;
	if (drawPile[randomNumber][randomNumber2][0] == 'A') {
		firstSpotValue = 1000;
	}
	else if (drawPile[randomNumber][randomNumber2][0] == '2') {
		firstSpotValue = 2;
	}
	else if (drawPile[randomNumber][randomNumber2][0] == '3') {
		firstSpotValue = 3;
	}
	else if (drawPile[randomNumber][randomNumber2][0] == '4') {
		firstSpotValue = 4;
	}
	else if (drawPile[randomNumber][randomNumber2][0] == '5') {
		firstSpotValue = 5;
	}
	else if (drawPile[randomNumber][randomNumber2][0] == '6') {
		firstSpotValue = 6;
	}
	else if (drawPile[randomNumber][randomNumber2][0] == '7') {
		firstSpotValue = 7;
	}
	else if (drawPile[randomNumber][randomNumber2][0] == '8') {
		firstSpotValue = 8;
	}
	else if (drawPile[randomNumber][randomNumber2][0] == '9') {
		firstSpotValue = 9;
	}
	else if (drawPile[randomNumber][randomNumber2][0] == '1') {
		firstSpotValue = 10;
	}
	else if (drawPile[randomNumber][randomNumber2][0] == 'J') {
		firstSpotValue = 10;
	}
	else if (drawPile[randomNumber][randomNumber2][0] == 'Q') {
		firstSpotValue = 10;
	}
	else if (drawPile[randomNumber][randomNumber2][0] == 'K') {
		firstSpotValue = 10;
	}
	else {
		cout << endl;
		cout << randomNumber << " | " << randomNumber2 << " | " << drawPile[randomNumber][randomNumber2] << " | " << endl;
		cout << "This is showing at the point where we are moving the card value to a value in which we can work with";
		exit(0);
	}

	playerCards[whatPlayer][turnsTaken] = drawPile[randomNumber][randomNumber2];
	playerValues[0][whatPlayer] += firstSpotValue;


	drawPile[randomNumber][randomNumber2] = "x";
}



//*********************************************************************
//                      dealerBelatedTotal
//   For the first two turns the dealer has a hidden card. ALong with that
//   It hides the value of the card is hidden. I need the total not take in
//   that hidden card
//**********************************************************************

int dealerBelatedTotal(int dealerTurnsTaken) {
	int dealerBelatedTotal_var = 0;
	int firstSpotValue;


	for (int x = 0; x < dealerTurnsTaken - 1; x++) {
		if (playerCards[0][x][0] == 'A') {
			firstSpotValue = 1000;
		}
		else if (playerCards[0][x][0] == '2') {
			firstSpotValue = 2;
		}
		else if (playerCards[0][x][0] == '3') {
			firstSpotValue = 3;
		}
		else if (playerCards[0][x][0] == '4') {
			firstSpotValue = 4;
		}
		else if (playerCards[0][x][0] == '5') {
			firstSpotValue = 5;
		}
		else if (playerCards[0][x][0] == '6') {
			firstSpotValue = 6;
		}
		else if (playerCards[0][x][0] == '7') {
			firstSpotValue = 7;
		}
		else if (playerCards[0][x][0] == '8') {
			firstSpotValue = 8;
		}
		else if (playerCards[0][x][0] == '9') {
			firstSpotValue = 9;
		}
		else if (playerCards[0][x][0] == '1') {
			firstSpotValue = 10;
		}
		else if (playerCards[0][x][0] == 'J') {
			firstSpotValue = 10;
		}
		else if (playerCards[0][x][0] == 'Q') {
			firstSpotValue = 10;
		}
		else if (playerCards[0][x][0] == 'K') {
			firstSpotValue = 10;
		}
		else {
			cout << endl;
			cout << "This is showing at firstSpotValue for the dealerBelated";
			exit(0);
		}
		dealerBelatedTotal_var += firstSpotValue;
	}

	return dealerBelatedTotal_var;
}


//*********************************************************************
//                      AceOutput
//   If there is an ace played in blackjack there is a hard and soft ace.  
//   This allows the soft and hard ace to be shown in an understandbale way
//**********************************************************************

void aceOutput(int whatPlayer, bool ifBelated, int belatedTotal) {
	int playerTotal;
	int softAce;
	int hardAce;
	int totalSpaces = 1; //having 1 there because of the slash there

	if (ifBelated) {
		playerTotal = belatedTotal;
	}
	else
		playerTotal = playerValues[0][whatPlayer];


	if (playerTotal <= 2000) {
		softAce = playerTotal - 999;
		hardAce = playerTotal - 989;
	}
	else if (playerTotal <= 3000) {
		softAce = playerTotal - 1998;
		hardAce = playerTotal - 1989;
	}
	else if (playerTotal <= 4000) {
		softAce = playerTotal - 2998;
		hardAce = playerTotal - 2989;
	}
	else if (playerTotal <= 5000) {
		softAce = playerTotal - 3998;
		hardAce = playerTotal - 3989;
	}
	else {
		cout << "This should not show and is at the aceOutput point";
		exit(0);
	}

	if (softAce < 10)
		totalSpaces += 1;
	else
		totalSpaces += 2;

	if (hardAce < 10)
		totalSpaces += 1;
	else
		totalSpaces += 2;


	if (whatPlayer == 0) {
		if (totalSpaces == 4)
			cout << softAce << '/' << hardAce << "             ";
		else if (totalSpaces == 5)
			cout << softAce << '/' << hardAce << "            ";
	}
	else {
		if (totalSpaces == 4)
			cout << softAce << '/' << hardAce << "            ";
		else if (totalSpaces == 5)
			cout << softAce << '/' << hardAce << "           ";
	}
}


//*********************************************************************
//                      ifBust
//   Sees if a player drew over 21 value with the different aces
//**********************************************************************

void ifBust(int whatPlayer) {
	if (playerValues[0][whatPlayer] > 4017) {
		playerValues[4][whatPlayer] = 0;
	}
	else if (playerValues[0][whatPlayer] > 3018 && playerValues[0][whatPlayer] < 4000) {
		playerValues[4][whatPlayer] = 0;
	}
	else if (playerValues[0][whatPlayer] > 2019 && playerValues[0][whatPlayer] < 3000) {
		playerValues[4][whatPlayer] = 0;
	}
	else if (playerValues[0][whatPlayer] > 1020 && playerValues[0][whatPlayer] < 2000) {
		playerValues[4][whatPlayer] = 0;
	}
	else if (playerValues[0][whatPlayer] > 21 && playerValues[0][whatPlayer] < 1000) {
		playerValues[4][whatPlayer] = 0;
	}
}


//*********************************************************************
//                      finishDealer
//   Sees if dealer drew over 17 in value even with aces
//**********************************************************************

bool finishDealer() {
	if (playerValues[0][0] >= 4013) {
		return false;
	}
	else if (playerValues[0][0] >= 3014 && playerValues[0][0] <= 4000) {
		return false;
	}
	else if (playerValues[0][0] >= 2015 && playerValues[0][0] <= 3000) {
		return false;
	}
	else if (playerValues[0][0] >= 1016 && playerValues[0][0] <= 2000) {
		return false;
	}
	else if (playerValues[0][0] >= 17 && playerValues[0][0] <= 1000) {
		return false;
	}
	else
		return true;
}


//*********************************************************************
//                      checkWinMatch
//   The ending seeing if a palyer won lost split blackjacked or anything else 
//   also took aces in to consideration
//**********************************************************************

void checkWinMatch() {
	int playerSubtract1, playerSubtract2;
	int dealerSubtract1, dealerSubtract2;

	if (playerValues[0][0] > 4000) {
		dealerSubtract1 = 3996;
		dealerSubtract2 = 3986;
	}
	else if (playerValues[0][0] > 3000) {
		dealerSubtract1 = 2997;
		dealerSubtract2 = 2987;
	}
	else if (playerValues[0][0] > 2000) {
		dealerSubtract1 = 1998;
		dealerSubtract2 = 1988;
	}
	else if (playerValues[0][0] > 1000) {
		dealerSubtract1 = 999;
		dealerSubtract2 = 989;
	}
	else {
		dealerSubtract1 = 0;
		dealerSubtract2 = 0;
	}


	for (int x = 1; x < 5; x++) {
		if (playerValues[0][x] > 4000) {
			playerSubtract1 = 3996;
			playerSubtract2 = 3986;
		}
		else if (playerValues[0][x] > 3000) {
			playerSubtract1 = 1997;
			playerSubtract2 = 1987;
		}
		else if (playerValues[0][x] > 2000) {
			playerSubtract1 = 1998;
			playerSubtract2 = 1988;
		}
		else if (playerValues[0][x] > 1000) {
			playerSubtract1 = 999;
			playerSubtract2 = 989;
		}
		else {
			playerSubtract1 = 0;
			playerSubtract2 = 0;
		}

		if ((playerValues[0][x] - playerSubtract1) == 21 || (playerValues[0][x] - playerSubtract2) == 21) //blackjack
			playerValues[4][x] = 2;
		else if ((playerValues[0][x] - playerSubtract1) > 21 || (playerValues[0][x] - playerSubtract2) > 21) //player over 21
			playerValues[4][x] = 0;
		else if ((playerValues[0][0] - dealerSubtract1) > 21 || (playerValues[0][0] - dealerSubtract2) > 21) //dealer over 21
			playerValues[4][x] = 3;
		else if ((playerValues[0][0] - dealerSubtract1) < (playerValues[0][x] - playerSubtract1) || (playerValues[0][0] - dealerSubtract2) < (playerValues[0][x] - playerSubtract2)) //player over dealer || same taken
			playerValues[4][x] = 3;
		else if ((playerValues[0][0] - dealerSubtract1) < (playerValues[0][x] - playerSubtract2) || (playerValues[0][0] - dealerSubtract2) < (playerValues[0][x] - playerSubtract1)) //player over dealer || opposite taken
			playerValues[4][x] = 3;
		else if ((playerValues[0][0] - dealerSubtract1) > (playerValues[0][x] - playerSubtract1) || (playerValues[0][0] - dealerSubtract2) > (playerValues[0][x] - playerSubtract2)) //dealer over player || same taken
			playerValues[4][x] = 1;
		else if ((playerValues[0][0] - dealerSubtract1) > (playerValues[0][x] - playerSubtract2) || (playerValues[0][0] - dealerSubtract2) > (playerValues[0][x] - playerSubtract1)) //dealer over player || opposite taken
			playerValues[4][x] = 1;
		else if ((playerValues[0][0] - dealerSubtract1) == (playerValues[0][x] - playerSubtract1) || (playerValues[0][0] - dealerSubtract2) == (playerValues[0][x] - playerSubtract2)) //dealer same player || same taken
			playerValues[4][x] = 4;
		else if ((playerValues[0][0] - dealerSubtract1) == (playerValues[0][x] - playerSubtract2) || (playerValues[0][0] - dealerSubtract2) == (playerValues[0][x] - playerSubtract1)) //dealer same player || opposite taken
			playerValues[4][x] = 4;
	}


	/*
	for (int x = 1; x < 5; x++) { //There are 4 aces total
		if (playerValues[0][x] > 4000 || playerValues[0][0] > 4000) {  //If either has 4 aces
			//---------------------------------------------------------------------------------------------------------
			//---------------------------------------------------------------------------------------------------------
			if (playerValues[0][x] > 4000 && playerValues[0][0] < 1000) { //player 4 aces and dealer 0 aces
				//---------------------------------------------------------------------------------------------------------
				if ( (playerValues[0][x] - 3996) == 21 || (playerValues[0][x] - 3986) == 21) //blackjack
					playerValues[4][x] = 2;
				else if ( (playerValues[0][x] - 3996) > 21 || (playerValues[0][x] - 3986) > 21) //player over 21
					playerValues[4][x] = 0;
				else if (playerValues[0][0] > 21) //dealer over 21
					playerValues[4][x] = 3;
				else if ( (playerValues[0][x] - 3996) > playerValues[0][0] || (playerValues[0][x] - 3896) > playerValues[0][0]) //player over dealer
					playerValues[4][x] = 3;
				else if ( (playerValues[0][x] - 3996) < playerValues[0][0] || (playerValues[0][x] - 3896) < playerValues[0][0]) //dealer over player
					playerValues[4][x] = 1;
				else if ( (playerValues[0][x] - 3996) == playerValues[0][0] || (playerValues[0][x] - 3896) == playerValues[0][0]) //dealer same player
					playerValues[4][x] = 4;
			}
			else if (playerValues[0][0] > 4000 && playerValues[0][x] < 1000) { //dealer 4 aces and player 0 aces
				//---------------------------------------------------------------------------------------------------------
				if (playerValues[0][x] == 21) //blackjack
					playerValues[4][x] = 2;
				else if (playerValues[0][x] > 21) //player over 21
					playerValues[4][x] = 0;
				else if ( (playerValues[0][0] - 3996) > 21 || (playerValues[0][0] - 3986) > 21) //dealer over 21
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 3996) < playerValues[0][x] || (playerValues[0][0] - 3896) < playerValues[0][x]) //player over dealer
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 3996) > playerValues[0][x] || (playerValues[0][0] - 3896) > playerValues[0][x]) //dealer over player
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 3996) == playerValues[0][x] || (playerValues[0][0] - 3896) == playerValues[0][x]) //dealer same player
					playerValues[4][x] = 4;
			}
		}
		//---------------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------
		else if (playerValues[0][x] > 3000 || playerValues[0][0] > 3000) { //If either has 3 aces
			//---------------------------------------------------------------------------------------------------------
			//---------------------------------------------------------------------------------------------------------
			if (playerValues[0][x] > 3000 && playerValues[0][0] > 1000) { // player 3 aces and dealer 1 ace
				//---------------------------------------------------------------------------------------------------------
				if ((playerValues[0][x] - 2996) == 21 || (playerValues[0][x] - 2986) == 21) //blackjack
					playerValues[4][x] = 2;
				else if ((playerValues[0][x] - 2996) > 21 || (playerValues[0][x] - 2986) > 21) //player over 21
					playerValues[4][x] = 0;
				else if ((playerValues[0][0] - 996) > 21 || (playerValues[0][0] - 986) > 21) //dealer over 21
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 996) < (playerValues[0][x] - 2996) || (playerValues[0][0] - 986) < (playerValues[0][x] - 2986)) //player over dealer || same taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 996) < (playerValues[0][x] - 2986) || (playerValues[0][0] - 986) < (playerValues[0][x] - 2996)) //player over dealer || opposite taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 996) > (playerValues[0][x] - 2996) || (playerValues[0][0] - 986) > (playerValues[0][x] - 2986)) //dealer over player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 996) > (playerValues[0][x] - 2986) || (playerValues[0][0] - 986) > (playerValues[0][x] - 2996)) //dealer over player || opposite taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 996) == (playerValues[0][x] - 2996) || (playerValues[0][0] - 986) == (playerValues[0][x] - 2986)) //dealer same player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 996) == (playerValues[0][x] - 2986) || (playerValues[0][0] - 986) == (playerValues[0][x] - 2996)) //dealer same player || opposite taken
					playerValues[4][x] = 1;
			}
			else if (playerValues[0][x] > 3000 && playerValues[0][0] < 1000) { // player 3 aces and dealer no aces
				//---------------------------------------------------------------------------------------------------------
				if ((playerValues[0][x] - 2996) == 21 || (playerValues[0][x] - 2986) == 21) //blackjack
					playerValues[4][x] = 2;
				else if ((playerValues[0][x] - 2996) > 21 || (playerValues[0][x] - 2986) > 21) //player over 21
					playerValues[4][x] = 0;
				else if ((playerValues[0][0]) > 21 || (playerValues[0][0]) > 21) //dealer over 21
					playerValues[4][x] = 3;
				else if ((playerValues[0][0]) < (playerValues[0][x] - 2996) || (playerValues[0][0]) < (playerValues[0][x] - 2986)) //player over dealer || same taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0]) < (playerValues[0][x] - 2986) || (playerValues[0][0]) < (playerValues[0][x] - 2996)) //player over dealer || opposite taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0]) > (playerValues[0][x] - 2996) || (playerValues[0][0]) > (playerValues[0][x] - 2986)) //dealer over player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0]) > (playerValues[0][x] - 2986) || (playerValues[0][0]) > (playerValues[0][x] - 2996)) //dealer over player || opposite taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0]) == (playerValues[0][x] - 2996) || (playerValues[0][0]) == (playerValues[0][x] - 2986)) //dealer same player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0]) == (playerValues[0][x] - 2986) || (playerValues[0][0]) == (playerValues[0][x] - 2996)) //dealer same player || opposite taken
					playerValues[4][x] = 1;
			}
			else if (playerValues[0][0] > 3000 && playerValues[0][x] > 1000) { // dealer 3 aces and player 1 ace
				//---------------------------------------------------------------------------------------------------------
				if ((playerValues[0][x] - 996) == 21 || (playerValues[0][x] - 986) == 21) //blackjack
					playerValues[4][x] = 2;
				else if ((playerValues[0][x] - 996) > 21 || (playerValues[0][x] - 986) > 21) //player over 21
					playerValues[4][x] = 0;
				else if ((playerValues[0][0] - 2996) > 21 || (playerValues[0][0] - 2986) > 21) //dealer over 21
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 2996) < (playerValues[0][x] - 996) || (playerValues[0][0] - 2986) < (playerValues[0][x] - 986)) //player over dealer || same taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 2996) < (playerValues[0][x] - 986) || (playerValues[0][0] - 2986) < (playerValues[0][x] - 996)) //player over dealer || opposite taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 2996) > (playerValues[0][x] - 996) || (playerValues[0][0] - 2986) > (playerValues[0][x] - 986)) //dealer over player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 2996) > (playerValues[0][x] - 986) || (playerValues[0][0] - 2986) > (playerValues[0][x] - 996)) //dealer over player || opposite taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 2996) == (playerValues[0][x] - 996) || (playerValues[0][0] - 2986) == (playerValues[0][x] - 986)) //dealer same player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 2996) == (playerValues[0][x] - 986) || (playerValues[0][0] - 2986) == (playerValues[0][x] - 996)) //dealer same player || opposite taken
					playerValues[4][x] = 1;
			}
			else if (playerValues[0][0] > 3000 && playerValues[0][x] < 1000) { //dealer 3 aces and player 0 aces
				//---------------------------------------------------------------------------------------------------------
				if ((playerValues[0][x]) == 21 || (playerValues[0][x]) == 21) //blackjack
					playerValues[4][x] = 2;
				else if ((playerValues[0][x]) > 21 || (playerValues[0][x]) > 21) //player over 21
					playerValues[4][x] = 0;
				else if ((playerValues[0][0] - 2996) > 21 || (playerValues[0][0] - 2986) > 21) //dealer over 21
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 2996) < (playerValues[0][x]) || (playerValues[0][0] - 2986) < (playerValues[0][x])) //player over dealer || same taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 2996) < (playerValues[0][x]) || (playerValues[0][0] - 2986) < (playerValues[0][x])) //player over dealer || opposite taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 2996) > (playerValues[0][x]) || (playerValues[0][0] - 2986) > (playerValues[0][x])) //dealer over player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 2996) > (playerValues[0][x]) || (playerValues[0][0] - 2986) > (playerValues[0][x])) //dealer over player || opposite taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 2996) == (playerValues[0][x]) || (playerValues[0][0] - 2986) == (playerValues[0][x])) //dealer same player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 2996) == (playerValues[0][x]) || (playerValues[0][0] - 2986) == (playerValues[0][x])) //dealer same player || opposite taken
					playerValues[4][x] = 1;
			}
		}
		//---------------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------
		else if (playerValues[0][x] > 2000 || playerValues[0][0] > 2000) { //If either has 2 aces
		//---------------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------
			if (playerValues[0][x] > 2000 && playerValues[0][0] > 2000) { // player 2 aces and dealer 2 aces
				//---------------------------------------------------------------------------------------------------------
				if ((playerValues[0][x] - 1996) == 21 || (playerValues[0][x] - 1986) == 21) //blackjack
					playerValues[4][x] = 2;
				else if ((playerValues[0][x] - 1996) > 21 || (playerValues[0][x] - 1986) > 21) //player over 21
					playerValues[4][x] = 0;
				else if ((playerValues[0][0] - 1996) > 21 || (playerValues[0][0] - 1986) > 21) //dealer over 21
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 1996) < (playerValues[0][x] - 1996) || (playerValues[0][0] - 1986) < (playerValues[0][x] - 1986)) //player over dealer || same taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 1996) < (playerValues[0][x] - 1986) || (playerValues[0][0] - 1986) < (playerValues[0][x] - 1996)) //player over dealer || opposite taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 1996) > (playerValues[0][x] - 1996) || (playerValues[0][0] - 1986) > (playerValues[0][x] - 1986)) //dealer over player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 1996) > (playerValues[0][x] - 1986) || (playerValues[0][0] - 1986) > (playerValues[0][x] - 1996)) //dealer over player || opposite taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 1996) == (playerValues[0][x] - 1996) || (playerValues[0][0] - 1986) == (playerValues[0][x] - 1986)) //dealer same player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 1996) == (playerValues[0][x] - 1986) || (playerValues[0][0] - 1986) == (playerValues[0][x] - 1996)) //dealer same player || opposite taken
					playerValues[4][x] = 1;
			}
			else if (playerValues[0][x] > 2000 && playerValues[0][0] > 1000) { // player 2 aces and dealer 1 aces
				//---------------------------------------------------------------------------------------------------------
				if ((playerValues[0][x] - 1996) == 21 || (playerValues[0][x] - 1986) == 21) //blackjack
					playerValues[4][x] = 2;
				else if ((playerValues[0][x] - 1996) > 21 || (playerValues[0][x] - 1986) > 21) //player over 21
					playerValues[4][x] = 0;
				else if ((playerValues[0][0] - 996) > 21 || (playerValues[0][0] - 986) > 21) //dealer over 21
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 996) < (playerValues[0][x] - 1996) || (playerValues[0][0] - 986) < (playerValues[0][x] - 1986)) //player over dealer || same taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 996) < (playerValues[0][x] - 1986) || (playerValues[0][0] - 986) < (playerValues[0][x] - 1996)) //player over dealer || opposite taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 996) > (playerValues[0][x] - 1996) || (playerValues[0][0] - 986) > (playerValues[0][x] - 1986)) //dealer over player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 996) > (playerValues[0][x] - 1986) || (playerValues[0][0] - 986) > (playerValues[0][x] - 1996)) //dealer over player || opposite taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 996) == (playerValues[0][x] - 1996) || (playerValues[0][0] - 986) == (playerValues[0][x] - 1986)) //dealer same player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 996) == (playerValues[0][x] - 1986) || (playerValues[0][0] - 986) == (playerValues[0][x] - 1996)) //dealer same player || opposite taken
					playerValues[4][x] = 1;
			}
			else if (playerValues[0][x] > 2000 && playerValues[0][0] < 1000) { // player 2 aces and dealer 0 aces
				//---------------------------------------------------------------------------------------------------------
				if ((playerValues[0][x] - 1996) == 21 || (playerValues[0][x] - 1986) == 21) //blackjack
					playerValues[4][x] = 2;
				else if ((playerValues[0][x] - 1996) > 21 || (playerValues[0][x] - 1986) > 21) //player over 21
					playerValues[4][x] = 0;
				else if ((playerValues[0][0] - 1996) > 21 || (playerValues[0][0] - 1986) > 21) //dealer over 21
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 1996) < (playerValues[0][x] - 1996) || (playerValues[0][0] - 1986) < (playerValues[0][x] - 1986)) //player over dealer || same taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 1996) < (playerValues[0][x] - 1986) || (playerValues[0][0] - 1986) < (playerValues[0][x] - 1996)) //player over dealer || opposite taken
					playerValues[4][x] = 3;
				else if ((playerValues[0][0] - 1996) > (playerValues[0][x] - 1996) || (playerValues[0][0] - 1986) > (playerValues[0][x] - 1986)) //dealer over player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 1996) > (playerValues[0][x] - 1986) || (playerValues[0][0] - 1986) > (playerValues[0][x] - 1996)) //dealer over player || opposite taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 1996) == (playerValues[0][x] - 1996) || (playerValues[0][0] - 1986) == (playerValues[0][x] - 1986)) //dealer same player || same taken
					playerValues[4][x] = 1;
				else if ((playerValues[0][0] - 1996) == (playerValues[0][x] - 1986) || (playerValues[0][0] - 1986) == (playerValues[0][x] - 1996)) //dealer same player || opposite taken
					playerValues[4][x] = 1;
			}
			else if (playerValues[0][0] > 2000 && playerValues[0][x] > 1000) { // dealer 2 aces and player 1 aces

			}
			else if (playerValues[0][0] > 2000 && playerValues[0][x] < 1000) { // dealer 2 aces and player 0 aces

			}
		}
		else if (playerValues[0][x] > 1000 || playerValues[0][0] > 1000) { //If either has 1 aces
			if (playerValues[0][x] > 1000 && playerValues[0][0] > 1000) { // player 1 aces and dealer 1 aces

			}
			else if (playerValues[0][x] > 1000 && playerValues[0][0] < 1000) { // player 1 aces and dealer 0 aces

			}
			else if (playerValues[0][0] > 1000 && playerValues[0][x] < 1000) { // dealer 1 aces and player 0 aces

			}
		}
		else if (playerValues[0][x] < 1000 && playerValues[0][0] < 1000) { //if either has 0 aces
			if (playerValues[0][x] == 21) //blackjack
				playerValues[4][x] = 2;
			else if (playerValues[0][x] > 21) //player over 21
				playerValues[4][x] = 0;
			else if (playerValues[0][0] > 21) //dealer over 21
				playerValues[4][x] = 3;
			else if (playerValues[0][x] > playerValues[0][0]) //player over dealer
				playerValues[4][x] = 3;
			else if (playerValues[0][x] < playerValues[0][0]) //dealer over player
				playerValues[4][x] = 1;
			else if (playerValues[0][x] == playerValues[0][0]) //dealer same player
				playerValues[4][x] = 4;
		}
		*/
}


//*********************************************************************
//                      betUpDate
//   Updates people's balances once the round is done
//**********************************************************************

void betUpDate() {
	for (int x = 1; x < 5; x++) {
		if (playerValues[4][x] == 0) { //bust
			playerValues[1][x] = playerValues[1][x];
			playerValues[2][x] = 0;
		}
		else if (playerValues[4][x] == 1) { //lost
			playerValues[1][x] = playerValues[1][x];
			playerValues[2][x] = 0;
		}
		else if (playerValues[4][x] == 2) { //blackjack
			playerValues[1][x] = playerValues[1][x] + (2.5 * playerValues[2][x] ); //2.5 multiplier
			playerValues[2][x] = 0;
		}
		else if (playerValues[4][x] == 3) { //won
			playerValues[1][x] = playerValues[1][x] + (2.5 * playerValues[2][x]); //2 multiplier
			playerValues[2][x] = 0;
		}
		else if (playerValues[4][x] == 4) { //split
			playerValues[1][x] = playerValues[1][x] + playerValues[2][x]; //stays the same as from the beginning
			playerValues[2][x] = 0;
		}
		else if (playerValues[4][x] == 5) { //surrender
			playerValues[1][x] = playerValues[1][x] + (.5 * playerValues[2][x]); //,5 multiplier
			playerValues[2][x] = 0;
		}
	}
}



//*********************************************************************
//                      redoDeck
//   If all cards have been drawn in drawCard(); it will call upon thi.
//   It will redo all of the values for the cards
//**********************************************************************

void redoDeck() {
  drawPile[0][0]= "A Spade   ";
  drawPile[0][1]= "2 Spade   ";
  drawPile[0][2]= "3 Spade   ";
  drawPile[0][3]= "4 Spade   ";
  drawPile[0][4]= "5 Spade   ";
  drawPile[0][5]= "6 Spade   ";
  drawPile[0][6]= "7 Spade   ";
  drawPile[0][7]= "8 Spade   ";
  drawPile[0][8]= "9 Spade   ";
  drawPile[0][9]= "10 Spade  ";
  drawPile[0][10]= "J Spade   ";
  drawPile[0][11]= "Q Spade   ";
  drawPile[0][12]= "K Spade   ";

  drawPile[1][0]= "A Heart   ";
  drawPile[1][1]= "2 Heart   ";
  drawPile[1][2]= "3 Heart   ";
  drawPile[1][3]= "4 Heart   ";
  drawPile[1][4]= "5 Heart   ";
  drawPile[1][5]= "6 Heart   ";
  drawPile[1][6]= "7 Heart   ";
  drawPile[1][7]= "8 Heart   ";
  drawPile[1][8]= "9 Heart   ";
  drawPile[1][9]= "10 Heart  ";
  drawPile[1][10]= "J Heart   ";
  drawPile[1][11]= "Q Heart   ";
  drawPile[1][12]= "K Heart   ";

  drawPile[2][0]= "A Diamond ";
  drawPile[2][1]= "2 Diamond ";
  drawPile[2][2]= "3 Diamond ";
  drawPile[2][3]= "4 Diamond ";
  drawPile[2][4]= "5 Diamond ";
  drawPile[2][5]= "6 Diamond ";
  drawPile[2][6]= "7 Diamond ";
  drawPile[2][7]= "8 Diamond ";
  drawPile[2][8]= "9 Diamond ";
  drawPile[2][9]= "10 Diamond";
  drawPile[2][10]= "J Diamond ";
  drawPile[2][11]= "Q Diamond ";
  drawPile[2][12]= "K Diamond ";

  drawPile[3][0]= "A Club    ";
  drawPile[3][1]= "2 Club    ";
  drawPile[3][2]= "3 Club    ";
  drawPile[3][3]= "4 Club    ";
  drawPile[3][4]= "5 Club    ";
  drawPile[3][5]= "6 Club    ";
  drawPile[3][6]= "7 Club    ";
  drawPile[3][7]= "8 Club    ";
  drawPile[3][8]= "9 Club    ";
  drawPile[3][9]= "10 Club   ";
  drawPile[3][10]= "J Club    ";
  drawPile[3][11]= "Q Club    ";
  drawPile[3][12]= "K Club    ";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
