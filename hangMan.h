#pragma once
#include <iostream>
using namespace std;
#include <cmath>

int checkGuess(int letterSpace, char guess, char blackSpace[]);
/* OLD STUFF
int checkGuess0(char , char blankSpaces[]);
int checkGuess1(char , char blankSpaces[]);
int checkGuess2(char , char blankSpaces[]);
int checkGuess3(char , char blankSpaces[]);
int checkGuess4(char , char blankSpaces[]);
int checkGuess5(char , char blankSpaces[]);
int checkGuess6(char , char blankSpaces[]);
int checkGuess7(char , char blankSpaces[]);
int checkGuess8(char , char blankSpaces[]);
*/
void showMan0();
void showMan1();
void showMan2();
void showMan3();
void showMan4();
void showMan5();
void showMan6();
void gameOver();
void buffer();

//the array for the testing of the if they have the right guess for the letter
int test[9] = {0,0,0,0,0,0,0,0,0};




void hangManProgram() 
{
  //just initilizign stuff I know form the start will need
  int numberLetters;
  char guess;

  //getting input of number of letters for the word because I did not figure out a way to use str.length();
  cout << "How many letters are there in your word? (2-9) ";
  cin >> numberLetters;
  while(numberLetters <2 || numberLetters >9)
  {
    cin.ignore();
    cout << "Please enter a valid number";
    cin >> numberLetters;
  }

  //now they will enter the word
  char blankSpace[numberLetters];
  cin.ignore();
  cout << endl <<"Please enter the letters in the word in order:";

  //this gets the word and places it in the right order
  cout << endl;
  for (int x=0; x < numberLetters; x++)
    cin >> blankSpace[x];
  

  //these next two are just for confirmation for the user
  cout << endl;
  for (int x=0; x < numberLetters; x++) //cout the word
    cout << blankSpace[x];
  cout << endl;
  for (int x=1; x <= numberLetters; x++) //cout the number under the word
    cout <<x;
  buffer(); //comment out if testing so you can see the full thing



  for (int x = numberLetters; x < 9; x++) { //setes all not used numbers to 2
    test[x] = 2;
  }

  //int test0=0, test1=0, test2=0, test3=0, test4=0, test5=0, test6=0, test7=0, test8=0; Previous stuff
  int amountWrong;
  while (test[0] == 0 || test[1] == 0 || test[2] == 0 || test[3] == 0 || test[4] == 0 || test[5] == 0 || test[6] == 0 || test[7] == 0 || test[8] == 0)
  {
    cout << endl << endl;
    cout << "\nWhat is your guess? ";
    cin >> guess;
    

    for (int x=0; x < numberLetters; x++) {
      if (test[x] == 0)
        test[x] = checkGuess(x, guess, blankSpace);
      cout << test[x];
    }

    /* OLD STUFF THAT I JUST LIKE TO KEEP IN THERE
    if (test0 ==0)
      test0 = checkGuess0(guess, blankSpace);
      cout << test0;
    if (test1 ==0)
      test1 = checkGuess1(guess, blankSpace);
      cout << test1;
    if (test2 ==0)
      test2 = checkGuess2(guess, blankSpace);
      cout << test2;
    if (test3 ==0)
      test3 = checkGuess3(guess, blankSpace);
      cout << test3;
    if (test4 ==0)
      test4 = checkGuess4(guess, blankSpace);
      cout << test4;
    if (test5 ==0)
      test5 = checkGuess5(guess, blankSpace);
      cout << test5;
    if (test6 ==0)
      test6 = checkGuess6(guess, blankSpace);
      cout << test6;
    if (test7 ==0)
      test7 = checkGuess7(guess, blankSpace);
      cout << test7;
    if (test8 ==0)
      test8 = checkGuess8(guess, blankSpace);
      cout << test8;
    */

    cout << endl;

    for (int x=0; x < numberLetters; x++) {
      if (test[x] == 1)
        cout << blankSpace[x];
      else if (test[x] == 0)
        cout << ".";
    }

    /* OLD STUFF THAT I JUST LIKE TO KEEP IN THERE
    if (test0 ==1)
      cout << blankSpace[0];
    else 
      cout << ".";
    if (test1 ==1)
      cout << blankSpace[1];
    else 
      cout << ".";
    if (test2 ==1)
      cout << blankSpace[2];
    else 
      cout << ".";
    if (test3 ==1)
      cout << blankSpace[3];
    else 
      cout << ".";
    if (test4 ==1)
      cout << blankSpace[4];
    else 
      cout << ".";
    if (test5 ==1)
      cout << blankSpace[5];
    else 
      cout << ".";
    if (test6 ==1)
      cout << blankSpace[6];
    else 
      cout << ".";
    if (test7 ==1)
      cout << blankSpace[7];
    else 
      cout << ".";
    if (test8 ==1)
      cout << blankSpace[8];
    else 
      cout << ".";
    */

    cout << endl;
    for (int x=1; x <= numberLetters; x++)
      cout <<x;
    cout << endl;

    //int amountWrong;  it is inside the loop so every time it ran it would reset it to 0;
    if (guess != blankSpace[0] && guess != blankSpace[1] && guess != blankSpace[2] && guess != blankSpace[3] && guess != blankSpace[4] && guess != blankSpace[5] && guess != blankSpace[6] && guess != blankSpace[7] && guess != blankSpace[8])
      {
        amountWrong = amountWrong + 1;
      }
      cout << "Wrong Guesses: " << amountWrong;
    
    if (amountWrong == 0)
      showMan0();
    else if (amountWrong ==1)
      showMan1();
    else if (amountWrong ==2)
      showMan2();
    else if (amountWrong ==3)
      showMan3();
    else if (amountWrong ==4)
      showMan4();
    else if (amountWrong ==5)
      showMan5();
    else if (amountWrong ==6)
      showMan6();
    else 
      gameOver();

  }

  cout << "CONGRADULATIONS YOU WON!!!!!";
}

int checkGuess(int letterSpace, char guess, char blackSpace[]) {
  if (guess == blackSpace[letterSpace]) 
    return 1;
  else 
    return 0;
  
}

/*
int checkGuess0(char guess, char blankSpace[])
{
  if (guess == blankSpace[0])
  {
    return 1;
  }
  else
    return 0;
}

int checkGuess1(char guess, char blankSpace[])
{
  if (guess == blankSpace[1])
  {
    return 1;
  }
  else
    return 0;
}

int checkGuess2(char guess, char blankSpace[])
{
  if (guess == blankSpace[2])
  {
    return 1;
  }
  else
    return 0;
}

int checkGuess3(char guess, char blankSpace[])
{
  if (guess == blankSpace[3])
  {
    return 1;
  }
  else
    return 0;
}

int checkGuess4(char guess, char blankSpace[])
{
  if (guess == blankSpace[4])
  {
    return 1;
  }
  else
    return 0;
}

int checkGuess5(char guess, char blankSpace[])
{
  if (guess == blankSpace[5])
  {
    return 1;
  }
  else
    return 0;
}

int checkGuess6(char guess, char blankSpace[])
{
  if (guess == blankSpace[6])
  {
    return 1;
  }
  else
    return 0;
}

int checkGuess7(char guess, char blankSpace[])
{
  if (guess == blankSpace[7])
  {
    return 1;
  }
  else
    return 0;
}

int checkGuess8(char guess, char blankSpace[])
{
  if (guess == blankSpace[8])
  {
    return 1;
  }
  else
    return 0;
}
*/

void showMan6()
{
  cout << endl;
  cout << "       ____ " << endl;
  cout << "       |   |" << endl;
  cout << "       O   |" << endl;
  cout << "      /|\\  |" << endl;
  cout << "      / \\  |" << endl;
  cout << "           |" << endl;
  cout << "   -------------" << endl;
}

void showMan5()
{
  cout << endl;
  cout << "       ____ " << endl;
  cout << "       |   |" << endl;
  cout << "       O   |" << endl;
  cout << "      /|\\  |" << endl;
  cout << "      /    |" << endl;
  cout << "           |" << endl;
  cout << "   -------------" << endl;
}

void showMan4()
{
  cout << endl;
  cout << "       ____ " << endl;
  cout << "       |   |" << endl;
  cout << "       O   |" << endl;
  cout << "      /|\\  |" << endl;
  cout << "           |" << endl;
  cout << "           |" << endl;
  cout << "   -------------" << endl;
}

void showMan3()
{
  cout << endl;
  cout << "       ____ " << endl;
  cout << "       |   |" << endl;
  cout << "       O   |" << endl;
  cout << "      /|   |" << endl;
  cout << "           |" << endl;
  cout << "           |" << endl;
  cout << "   -------------" << endl;
}

void showMan2()
{
  cout << endl;
  cout << "       ____ " << endl;
  cout << "       |   |" << endl;
  cout << "       O   |" << endl;
  cout << "       |   |" << endl;
  cout << "           |" << endl;
  cout << "           |" << endl;
  cout << "   -------------" << endl;
}

void showMan1()
{
  cout << endl;
  cout << "       ____ " << endl;
  cout << "       |   |" << endl;
  cout << "       O   |" << endl;
  cout << "           |" << endl;
  cout << "           |" << endl;
  cout << "           |" << endl;
  cout << "   -------------" << endl;
}

void showMan0()
{
  cout << endl;
  cout << "       ____ " << endl;
  cout << "       |   |" << endl;
  cout << "           |" << endl;
  cout << "           |" << endl;
  cout << "           |" << endl;
  cout << "           |" << endl;
  cout << "   -------------" << endl;
}

void gameOver()
{
  cout << endl;
  cout << endl;
  cout << endl;
  cout << "Game Over" << endl;
  cout << "............................................________ ";
  cout << endl;
  cout << "....................................,.-‘”...................``~., ";
  cout << endl;
  cout << ".............................,.-”...................................“-.,";
  cout << endl;
  cout << ".........................,/...............................................”:, ";
  cout << endl;
  cout << ".....................,?......................................................\\, ";
  cout << endl;
  cout << ".................../...........................................................,} ";
  cout << endl;
  cout << "................./......................................................,:`^`..} ";
  cout << endl;
  cout << ".............../...................................................,:”........./ ";
  cout << endl;
  cout << "..............?.....__.........................................:`.........../ ";
  cout << endl;
  cout << "............./__.(.....“~-,_..............................,:`........../ ";
  cout << endl;
  cout << ".........../(_....”~,_........“~,_....................,:`........_/ ";
  cout << endl;
  cout << "..........{.._$;_......”=,_.......“-,_.......,.-~-,},.~”;/....} ";
  cout << endl;
  cout << "...........((.....*~_.......”=-._......“;,,./`..../”............../ ";
  cout << endl;
  cout << "...,,,___.\\`~,......“~.,....................`.....}............../ ";
  cout << endl;
  cout << "............(....`=-,,.......`........................(......;_,,-” ";
  cout << endl;
  cout << "............/.`~,......`-...............................\\....../\\ ";
  cout << endl;
  cout << ".............\\`~.*-,.....................................|,./.....\\,__ ";
  cout << endl;
  cout << ",,_..........}.>-._\\...................................|..............`=~-, ";
  cout << endl;
  cout << ".....`=~-,_\\_......`\\,.................................\\ ";
  cout << endl;
  cout << "...................`=~-,,.\\,...............................\\ ";
  cout << endl;
  cout << "................................`:,,...........................`\\..............__ ";
  cout << endl;
  cout << ".....................................`=-,...................,%`>--==`` ";
  cout << endl;
  cout << "........................................_\\..........._,-%.......`\\ ";
  cout << endl;
  cout << "..................................., ";
}

void buffer()
{
  for (int x =0; x <= 55; x++)
    cout << endl;
}
