/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 14, 2015, 9:33 PM
    Purpose: calculate percentage grade for an unknown number of scores
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
  //set up working variables
  int maxScores = 0, currScore = 0, currScoreMax = 0, totalScore = 0, totalScoreMax = 0;
  float percentGrade = 0.0f;
  
  //get the number of times to loop
  cout << "How many exercises to input? ";
  cin >> maxScores;
  cout << endl;
  if (maxScores < 1)
  {
    cout << "The number of exercises must be one or more." << endl;
    return 1;
  }
  
  //loop maxScores times, getting input for each one
  int count = 1;
  while (count <= maxScores)
  {
    //get scores for current exercise
    cout << "Score received for exercise " << count << ": ";
    cin >> currScore;
    cout << "Total points possible for exercise " << count << ": ";
    cin >> currScoreMax;
    
    //add scores for current exercise into total
    totalScore += currScore;
    totalScoreMax += currScoreMax;
    
    cout << endl;
    ++count;
  }
  
  //calculate scores and percentage, and output to user
  cout << "Your total is " << totalScore << " out of " << totalScoreMax << ", or " << static_cast<float>(totalScore)/totalScoreMax * 100 << "%." << endl;
  
  return 0;
}
