#pragma once
#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
using namespace std;

int doCoinFlipProgram() {
  int choice, r;
  cout << "Please pick heads(1) or tails(2): ";
  cin >> choice;

  if (choice== 1)
    cout << "You picked heads";
  else if (choice ==2)
    cout << "You picked tails";
  else {
    do {
      cout << "Please enter either one or two: ";
      cin >> choice;
    } while (choice != 1 || choice != 2);
  }


  cout << endl << endl << "Flipping the coin...\n\n";



  srand(time(NULL));
  int randNum = (rand() % 2) + 1;

  if (randNum== 1)
    cout << "It landed Heads";
  else if (randNum ==2)
    cout << "It landed Tails";

  if (randNum ==1 & choice ==1 || randNum ==2 & choice ==2)
  {
    cout << "Congrats you guess right";
    return 1;
  }
  else {
    cout << "\nSorry you guess wronge";
    return 0;
  }
}
