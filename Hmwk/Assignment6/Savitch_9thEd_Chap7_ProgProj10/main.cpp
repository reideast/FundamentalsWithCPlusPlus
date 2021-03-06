/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on February 8, 2015, 2:07 PM
    Purpose: two player tic-tac-toe
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
int playGame(char players[], int first); //players must be a 2-item array of the tokens to place on the board; first must be 0 or 1
void displayBoard(int board[], char players[]);
void getSquare(int &input, int board[]);
int checkWinner(int board[]); // returns -1 for no win, 0 for first player wins, 1 for second
int sum(int nums[], int first, int last);

//Execution Begins Here
int main(int argc, char** argv)
{
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isUserFinished = false; //controls main loop
  char quit = 0;
  char players[2] = {'X','O'};
  int score[2] = {0,0};
  int winner = 0;
  int first = 0;
  while (!isUserFinished)
  {
    cout << "Let's play Tic-Tac-Toe!" << endl;
    
    winner = playGame(players, first);
    if (winner >= 0) //did not play to a draw
      score[winner]++;
    
    cout << "The current score is: Player " << players[0] << " - " << score[0] << " vs. Player " << players[1] << " - " << score[1] << endl;
    
    first = !first;
    
    //determine if the user would like to repeat the calculation (copied from my Savitch_9thEd_Chap3_ProgProj1)
    cout << endl;
    cout << "Would you like to play again? (N to quit) ";
    cin >> quit;
    if (quit == 'N' || quit == 'n')
      isUserFinished = true;
    else
      cout << endl; //a blank line for readability
  }
  return 0;
}

int playGame(char players[], int current)
{
  int board[9] = {-10,-10,-10,-10,-10,-10,-10,-10,-10};
  int input = 0;
  int winner = -1;
  while ((winner = checkWinner(board)) == -1)
  {
    displayBoard(board, players);
    cout << "Player " << players[current] << endl << "Please choose a square (1-9): ";
    getSquare(input, board);
    board[(input - 1)] = current;
    current = !current;
  }
  
  if (winner == 2)
  {
    displayBoard(board, players);
    cout << endl << "The game ended in a draw." << endl;
    return -1;
  }
  else
  {
    displayBoard(board, players);
    cout << endl << "Player " << players[winner] << " has won!" << endl;
    return winner;
  }
}

void getSquare(int &input, int board[])
{
  bool isInputValid = false; //controls input loop (ie, loop until input is right)
  while (!isInputValid)
  {
    cout << "> ";
    cin >> input;
    if (input < 1)
      cout << "The square cannot be less than 1. Please choose again." << endl;
    else if (input > 9)
      cout << "The square cannot be greater than 9. Please choose again." << endl;
    else if (board[input - 1] >= 0)
      cout << "That square has already been chosen." << endl;
    else
      isInputValid = true;
  }
}

void displayBoard(int board[], char players[])
{
  cout << "     |     |     " << endl;
  for (int i = 0; i < 9; ++i)
  {
    cout << "  " << static_cast<char>(((board[i] >= 0) ? players[board[i]] : (i + 1 + '0'))) << "  ";
    if ((i + 1) % 3 == 0)
      if (i == 8)
        cout << endl << "     |     |     " << endl;
      else
        cout << endl << "-----|-----|-----" << endl;
    else
      cout << "|";
  }
}
int checkWinner(int board[]) // returns -1 for no win, 0 for first player wins, 1 for second, 2 for draw
{
  //note: all these use the fact that the board is initialized to -10, and players are 0 and 1
  int total = 0;
  
  //rows:
  total = sum(board, 0, 2);
  if (total == 0) return 0;
  else if (total == 3) return 1;
  total = sum(board, 3, 5);
  if (total == 0) return 0;
  else if (total == 3) return 1;
  total = sum(board, 6, 8);
  if (total == 0) return 0;
  else if (total == 3) return 1;
  
  //cols:
  total = board[0] + board[3] + board[6];
  if (total == 0) return 0;
  else if (total == 3) return 1;
  total = board[1] + board[4] + board[7];
  if (total == 0) return 0;
  else if (total == 3) return 1;
  total = board[2] + board[5] + board[8];
  if (total == 0) return 0;
  else if (total == 3) return 1;
  
  //diagonals:
  total = board[0] + board[4] + board[8];
  if (total == 0) return 0;
  else if (total == 3) return 1;
  total = board[6] + board[4] + board[2];
  if (total == 0) return 0;
  else if (total == 3) return 1;
  
  if (sum(board, 0, 8) > 0) //all spaces have been played, yet none of the other win conditions were true
    return 2;
  
  return -1;
}

//I realized after I made this that function isn't all that useful compared to just adding 3 numbers.
//But I left it in because I like the example
int sum(int nums[], int first, int last)
{
  int sum = 0;
  for ( ; first <= last; ++first)
    sum += nums[first];
  return sum;
}