#include <iostream>
#include <cmath>
#include <CoinFlip.h>
#include "HangMan.h"
#include "TicTacToe.h"
using namespace std;


int main() {
  cout << endl;
  cout << "-----------------------------------------------------";
  cout << endl << "\t\t\t\t\tMENU" << endl;
  cout << "-----------------------------------------------------";
  cout << endl << "\t1. CoinFlip";
  cout << endl << "\t2. HangMan";
  cout << endl << "\t3. TicTacToe";
  cout << endl << "\t4. TicTacToe Against a Bot (NEED TO MAKE)";

  cout << endl << endl << "What would you like to do? ";

  int option;
  cin >> option;


  buffer();

  if(option == 1) {
    coinFlip coinFlipObject;
    coinFlipObject.coinFlipProgram();
  }
  else if (option ==2) {
    hangMan hangManObject;
    hangManObject.hangManProgram();
  }
  else if (option ==3) {
    ticTacToeProgram();
  }
  else if (option ==3) {
    cout << "Yeah I am still programming this ;)";
  }
  else {
    cout << "Please enter a correct option: ";
    cin >> option;
  }
}
