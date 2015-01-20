/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 15, 2015, 9:26 PM
    Purpose: Convert Arabic numerals to Roman numerals
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries
//Global Constants
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv)
{
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isUserFinished = false; //controls main loop
  char quit = 0;
  bool isInputValid = false; //controls individual input loops (ie, loop until input is right)
  while (!isUserFinished)
  {
    int arabic = 0;
    //input loop; until input is verified as valid (copied from my Savitch_9thEd_Chap3_ProgProj1)
    isInputValid = false;
    while (!isInputValid)
    {
      cout << "Input the year in Arabic numerals: ";
      cin >> arabic;
      if (arabic < 0) //don't accept negative numbers
      {
        cout << "The number cannot be negative. Please input again." << endl;
        isInputValid = false;
      }
      else
      {
        isInputValid = true;
      }
    }
    
    int currValue, currPlace, prevPlace;
    char currDigit, halfDigit, prevDigit;
    
    currPlace = 10000; //set up starting place before; everything is based off of that
    do
    {
      prevPlace = currPlace;
      currPlace /= 10;
      if (currPlace == 1000)
      {
        currDigit = 'M';
        halfDigit = '*';
        prevDigit = '*';
      } 
      else if (currPlace == 100)
      {
        prevDigit = currDigit;
        currDigit = 'C';
        halfDigit = 'D';
      }
      else if (currPlace == 10)
      {
        prevDigit = currDigit;
        currDigit = 'X';
        halfDigit = 'L';
      }
      else if (currPlace == 1)
      {
        prevDigit = currDigit;
        currDigit = 'I';
        halfDigit = 'V';
      }
      
      currValue = arabic / currPlace; //uses integer division to quickly determine # of digits
      cout << "DEBUG number of " << currPlace << "'s: " << currValue << endl;
      if (currValue == 9)
      {
        cout << currDigit << prevDigit;
      }
      else if (currValue == 4)
      {
        cout << currDigit << halfDigit;
      }
      else // 1 - 3, 5 - 8
      {
        if (currValue >= 5) //5 - 8
        {
          cout << halfDigit;
          currValue = currValue - 5;
        }
        for ( ; currValue > 0; --currValue)
          cout << currDigit;
      }
      arabic %= currPlace;
      cout << endl << "DEBUG: leftovers: " << arabic << endl;
      
    }
    while (currDigit != 'I');
    
    
    //determine if the user would like to repeat the calculation (copied from my Savitch_9thEd_Chap3_ProgProj1)
    cout << endl;
    cout << "Would you like to do more calculations? (N to quit) ";
    cin >> quit;
    if (quit == 'N' || quit == 'n')
      isUserFinished = true;
  }
  return 0;
}