#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
using namespace std;

char square[10] = {'0' , '1', '2', '3', '4', '5', '6', '7', '8', '9'};

void playerMove();
int checkWin();
void botMove();
void board();

int main() {

  cout << "Lets find out who is going to going to pick first.\n";

  //implement the heads or tails game from the other shit.
  //This will lead to a 50 50 chance of picking first or second
  //For now will just have it be hard coded with a varible
  //1 will be he personwill play first
  //2 will be the ai first
  int order=0;

  //so if order equals 0 we need to get the ai to pick a random place. But do I actually want it be a completely random place or not. Becuase when I play with friends there are common places where we place. And it is not random at all.
  //eh going to be the random

  if (order ==0)
  {
    srand(time(NULL));
    int randNum = (rand() % 9) + 1;
    square[randNum] = 'O';
  }
  
  int i;
  do 
  {
    board();
    
    playerMove();

    i = checkWin();

    if (i != -1) {
      if (i == 1) {
        cout << "Congrats you beat the bot";
        board();
        cin.ignore();
        cin.get();
        return 0;
      }
      else if (i == 0) {
        board();
        cout << "You failed to beat the bot";
        cin.ignore();
        cin.get();
        return 0;
      }
    }

    botMove();
    i = checkWin();

    if (i != -1) {
      board();
      if (i == 1) {
        cout << "The bot won how could you";
        
        cin.ignore();
        cin.get();
        return 0;
      }
      else if (i == 0) {
        
        cout << "Hey at least you tied the bot";
        cin.ignore();
        cin.get();
        return 0;
      }
    }
  }while (i == -1);
}


void playerMove() {
  int choice, error= 0;
  do {
    
    cout << "Please enter a number: ";
    cin >> choice;

    
    if (choice ==1 && square[1] == '1')
      square[1] = 'X';
    else if (choice == 2 && square[2] == '2')
      square[2] = 'X';
    else if (choice == 3 && square[3] == '3')
      square[3] = 'X';
    else if (choice == 4 && square[4] == '4')
      square [4] = 'X';
    else if (choice == 5 && square[5] == '5')
      square [5] = 'X';
    else if (choice == 6 && square[6] == '6')
      square [6] = 'X';
    else if (choice == 7 && square[7] == '7')
      square [7] = 'X';
    else if (choice == 8 && square[8] == '8')
      square [8] = 'X';
    else if (choice == 9 && square[9] == '9')
      square [9] = 'X';
    else 
    {
      error =1;

      cout << endl << endl;
      cout << "Invalid move\n";
      cout << "Please choose a different spot\n";
      cout << "Please press ENTER to confirm you are aware";

      cin.ignore();
      cin.get();
    }
  } while (error ==1);
}



int checkWin()
{
  if (square [1] == square [2] && square [2] == square [3])
    return 1; //will check square 1 later
  else if (square[4] == square [5] && square[5] == square[6])
    return 1; //will check square 5 later
  else if (square[7] == square [8] && square[8] == square[9])
    return 1; //will check square 9 later
  else if (square[1] == square [4] && square[4] == square[7])
    return 1; //will check sqaure 1 later
  else if (square[2] == square [5] && square[5] == square[8])
    return 1; //will check square 5 later
  else if (square[3] == square [6] && square[6] == square[9])
    return 1; //will check square 9 later
  else if (square[1] == square [5] && square[5] == square[9])
    return 1; //will check square 5 later
  else if (square[3] == square [5] && square[5] == square[7])
    return 1; //will check square 5 later
  else if (square[1] != '1' && square[2] != '2' && square[3] != '3' && square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7] != '7' && square[8] != '8' && square[9] != '9')
    return 0;
  else
    return -1;
}

void botMove() {
  //First going X X _
  if (square [1] == square [2] && square [3] != '3')
    square [3] = 'O';
  else if (square[4] == square [5] && square[6] == '6')
    square [6] = 'O';
  else if (square[7] == square [8] && square[9] == '9')
    square [9] = 'O';
  //Secong going _ X X 
  else if (square[2] == square [3] && square[1] == '1')
    square [1] = 'O';
  else if (square[6] == square [5] && square[4] == '4')
    square [4] = 'O';
  else if (square[9] == square [8] && square[7] == '7')
    square [7] = 'O';
  //Third going X _ X
  else if (square[1] == square [3] && square[2] == '2')
    square [2] = 'O';
  else if (square[4] == square [6] && square[5] == '5')
    square [5] = 'O';
  else if (square[9] == square [8] && square[7] == '7')
    square [7] = 'O';
  // X
  // X   Fourth
  // _ 
  else if (square[1] == square [4] && square[7] == '7')
    square [2] = 'O';
  else if (square[2] == square [5] && square[8] == '8')
    square [5] = 'O';
  else if (square[3] == square [6] && square[9] == '9')
    square [7] = 'O';
  // X
  // _   Fifth
  // X   
  else if (square[1] == square [7] && square[4] == '4')
    square [2] = 'O';
  else if (square[2] == square [8] && square[5] == '5')
    square [5] = 'O';
  else if (square[3] == square [9] && square[6] == '6')
    square [7] = 'O';
  // _
  // x   Sixed
  // X   
  else if (square[4] == square [7] && square[1] == '1')
    square [2] = 'O';
  else if (square[5] == square [8] && square[2] == '2')
    square [5] = 'O';
  else if (square[6] == square [9] && square[3] == '3')
    square [7] = 'O';
  //Seventh going across from top left to bottom right
  else if (square[1] == square [5] && square[9] == '9')
    square [9] = 'O';
  else if (square[1] == square [9] && square[5] == '5')
    square [5] = 'O';
  else if (square[5] == square [9] && square[1] == '1')
    square [1] = 'O';
  //Eighth going across from bottom left to top right
  else if (square[7] == square [5] && square[3] == '3')
    square [3] = 'O';
  else if (square[7] == square [3] && square[5] == '5')
    square [5] = 'O';
  else if (square[5] == square [3] && square[7] == '7')
    square [7] = 'O';
  //Now that we have all the basic down we can think about complex moves that help prevent getting stuck in those situations were there are 2 options of which the other person is going to win. These I think will still be reactive
  // _ _ X
  // _ O _
  // X _ _

  //this is just random if none of the other requirements are met
  else {
    for( ; ; ) {
      int randNum;

      if (square[randNum] == randNum) {
        square[randNum] = 'O';
        break; 
      }
    } 
  }
}



void board()
{
  cout << "\n\nTic Tac Toe \n\n";

  cout << "Player 1 (X)  -  Player Bot  (O)\n\n";

  cout << "   |   |   " << endl;

  cout << " " << square[1] << " | " << square[2] << " | " << square[3] << endl;

  cout << "___|___|___" << endl;
  cout << "   |   |   " << endl;

  cout << " " << square[4] << " | " << square[5] << " | " << square[6] << endl;

  cout << "___|___|___" << endl;
  cout << "   |   |   " << endl;

  cout << " " << square[7] << " | " << square[8] << " | " << square[9] << endl;

  cout << "   |   |   " << endl << endl;
}
