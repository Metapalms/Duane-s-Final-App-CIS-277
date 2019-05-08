#include <iostream>
#include <cmath>
#include "blackJack.h"
#include "hangMan.h"
#include "coinFlip.h"
#include "ticTacToeBot.h"
using namespace std;


bool playAgain();
bool playDiffGame();
void blackJackredo();
void hangManredo();
void doCoinFlipredo();
void ticTacToeBotredo();


int main() {
  int option;
  char anotherGame;

  do {
    //Just showing the menu
    cout << endl;
    cout << "-----------------------------------------------------";
    cout << endl << "\t\t\t\t\tMENU" << endl;
    cout << "-----------------------------------------------------";
    cout << endl << "\t1. 21 BlackJack";
    cout << endl << "\t2. HangMan";
    cout << endl << "\t3. CoinFlip";
    cout << endl << "\t4. TicTacToe against Bot";

    cout << endl << endl << "What would you like to do? ";
    
    
    do {
      cin >> option;


      if(option == 1) {
        do {
          blackJackProgram();

          //Redoing all global variabels
          blackJackredo();
        } while (playAgain());
      }
      else if (option ==2) {
        do {
          hangManProgram();
          

          //Redoing all global variabels
          hangManredo();
        } while (playAgain());
      }
      else if (option ==3) {
        do {
          doCoinFlipProgram();

          //Redoing all global variabels
          doCoinFlipredo();
        } while (playAgain());
      }
      else if (option ==4) {
        do {
          ticTacToeBotProgram();

          //Redoing all global variabels
          ticTacToeBotredo();
        } while (playAgain());
      }
      else {
        cin.ignore();
        cout << "Please enter a correct option: ";
        option = 69;
      }
    } while (option == 69);
  } while (playDiffGame());
}


//gets the input and returns as a bool whether someone would like to play the same app again
bool playAgain() {
  char userAnswer;
  bool askAgain;
  do {
    cout << "\nWould you like to play again? (Y or N): ";
    cin >> userAnswer;

    if (userAnswer == 'y' || userAnswer == 'Y')
      return true;
    else if (userAnswer == 'n' || userAnswer == 'N')
      return false;
    else
      askAgain = true;

  } while (askAgain);
  return false; //just to get rid of error
}


//gets the input and returns as a bool whether someone would like to play a different game
bool playDiffGame() {
  char userAnswer;
  bool askAgain;
  do {
    cout << "\nWould you like to play a different game? (Y or N): ";
    cin >> userAnswer;

    if (userAnswer == 'y' || userAnswer == 'Y')
      return true;
    else if (userAnswer == 'n' || userAnswer == 'N')
      return false;
    else
      askAgain = true;

  } while (askAgain);
  return false; //just to get rid of error
}


void blackJackredo(){
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


playerCards[0][0] = "          ";
playerCards[0][1] = "          ";
playerCards[0][2] = "          ";
playerCards[0][3] = "          ";
playerCards[0][4] = "          ";
playerCards[0][5] = "          ";
playerCards[0][6] = "          ";

playerCards[1][0] = "          ";
playerCards[1][1] = "          ";
playerCards[1][2] = "          ";
playerCards[1][3] = "          ";
playerCards[1][4] = "          ";
playerCards[1][5] = "          ";
playerCards[1][6] = "          ";

playerCards[2][0] = "          ";
playerCards[2][1] = "          ";
playerCards[2][2] = "          ";
playerCards[2][3] = "          ";
playerCards[2][4] = "          ";
playerCards[2][5] = "          ";
playerCards[2][6] = "          ";

playerCards[3][0] = "          ";
playerCards[3][1] = "          ";
playerCards[3][2] = "          ";
playerCards[3][3] = "          ";
playerCards[3][4] = "          ";
playerCards[3][5] = "          ";
playerCards[3][6] = "          ";

playerCards[4][0] = "          ";
playerCards[4][1] = "          ";
playerCards[4][2] = "          ";
playerCards[4][3] = "          ";
playerCards[4][4] = "          ";
playerCards[4][5] = "          ";
playerCards[4][6] = "          ";




playerValues[0][0]= 0;
playerValues[0][1]= 0;
playerValues[0][2]= 0;
playerValues[0][3]= 0;
playerValues[0][4]= 0;

playerValues[1][0]= 0;
playerValues[1][1]= 0;
playerValues[1][2]= 0;
playerValues[1][3]= 0;
playerValues[1][4]= 0;

playerValues[2][0]= 0;
playerValues[2][1]= 0;
playerValues[2][2]= 0;
playerValues[2][3]= 0;
playerValues[2][4]= 0;

playerValues[3][0]= 0;
playerValues[3][1]= 0;
playerValues[3][2]= 0;
playerValues[3][3]= 0;
playerValues[3][4]= 0;

playerValues[4][0]= -1;
playerValues[4][1]= -1;
playerValues[4][2]= -1;
playerValues[4][3]= -1;
playerValues[4][4]= -1;



betValues[0] =0;
betValues[0] = 0;

}
void hangManredo(){
  test[0]=0;
  test[1]=0;
  test[2]=0;
  test[3]=0;
  test[4]=0;
  test[5]=0;
  test[6]=0;
  test[7]=0;
  test[8]=0;
}
void doCoinFlipredo(){
  cout << endl;
  //there is nothign to reset
}
void ticTacToeBotredo(){
  square[1] = '1';
  square[2] = '2';
  square[3] = '3';
  square[4] = '4';
  square[5] = '5';
  square[6] = '6';
  square[7] = '7';
  square[8] = '8';
  square[9] = '9';
}
