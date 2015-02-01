/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 13, 2015, 6:04 PM
    Purpose: test writing to a screen and animate it
 */

//System Libraries
#include <iostream>
#include <cmath>

#include <iomanip>
#include <string>

//for sleeping. referece: http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
//chrono needs C++11. In NetBeans, right click on Project. Set Configuration -> Customize. Build -> C++ Compiler. C++ Standard == C++11.
#include <chrono>
#include <thread>

using namespace std;

//User Libraries

//Global Constants
const float g = 9.8; // m/s^2

//should these be global, or passed to function??
const int ANIMATION_RATE = 50; //miliseconds
const int WINDOW_COLUMNS = 80;
const int WINDOW_ROWS = 25;

//Function Prototypes
bool writeScreen(int x, int y); //write a screen with a '*' at (x, y)
void testWriteScreen();

void cls(); //clear the screen by writing 100 new lines

//Execution Begins Here
int main(int argc, char** argv)
{
  //testWriteScreen();
  
  //using values for stage 1 of Saturn V rocket
  float Isp = 263; // 263 seconds = specific impulse
  float m_v_empty = 870000; //total mass for rocket - stage 1 fuel
  //float m_v_empty = 867200; // sum of full stage 2-3, plus payload max
  
  float m_fuel = 2100000; //from stage 1 info
  float t_b = 165; //the saturn 5 rocket stage 1 burns for 165 s
  
  //t_b = 60;
  
  float m_v0 = m_v_empty + m_fuel;
  float m_vfinal = m_v_empty;

  float t = 0.0f;
  float curr_mass_vehicle = 0.0f;
  float curr_velocity = 0.0f;
  float curr_height = 0.0f;
  
  float height_at_end_of_burnout = 0.0f; //will be in m
  float velocity_at_end_of_burnout = 0.0f; //will be in m/s
  
  
  while (t <= t_b)
  {
    cout << "t=" << t << " sec." << endl;
    curr_mass_vehicle = m_v0 - (m_v0 - m_vfinal) * (t / t_b);
    cout << "curr_mass_vehicle: " << curr_mass_vehicle << " kg" << endl;
  
    // curr_velocity = g * (Isp * log(m_v0 / curr_mass_vehicle) - t);
    // curr_velocity = g * (Isp * log(m_v0 / m_v_empty) - t);
    curr_velocity = g * (Isp * log(curr_mass_vehicle / m_v_empty) - t);
    cout << "curr_velocity: " << curr_velocity << " m/s" << endl; 

    curr_height = g * ( -t * Isp * ((log(m_v0 / curr_mass_vehicle)) / ((m_v0 / curr_mass_vehicle) - 1)) + t * Isp - 1/2 * t * t);
    cout << "curr_height: " << (curr_height / 100) << " km" << endl;
    t += t_b / 4;
    
    cout << endl;
  }
  
  
  t = t_b;
  curr_mass_vehicle = m_v0 - (m_v0 - m_vfinal) * (t / t_b);
  cout << "curr_mass_vehicle: " << curr_mass_vehicle << " kg" << endl;
  velocity_at_end_of_burnout = g * (Isp * log(m_v0 / curr_mass_vehicle) - t);
  cout << "velocity_at_end_of_burnout: " << velocity_at_end_of_burnout << " m/s" << endl;
  
  float delta_u = Isp * g * log(m_v0/m_vfinal) - g*t_b;
  cout << "delta_u: " << delta_u << " m/s" << endl;
  
  height_at_end_of_burnout = g * ( -t_b * Isp * ((log(m_v0 / m_vfinal)) / ((m_v0 / m_vfinal) - 1)) + t_b * Isp - 1/2 * t_b * t_b);
  cout << "height_at_end_of_burnout: " << (height_at_end_of_burnout / 100) << " km" << endl << endl;
  
  return 0;
}
void testWriteScreen()
{
  int x = WINDOW_COLUMNS / 2;
  for (int y = 0; y < WINDOW_ROWS; ++y)
  {
    cls();
    writeScreen(x, y);
    this_thread::sleep_for(chrono::milliseconds(ANIMATION_RATE)); //reference: http://stackoverflow.com/questions/4184468/sleep-for-milliseconds
  }
}

bool writeScreen(int x, int y)
{
  if (x < 1 || x > WINDOW_COLUMNS)
  {
    cout << "Error in writeScreen: horizontal (" << x << ") is out of bounds.";
    return 1;
  }
  else if (y < 1 || y > WINDOW_ROWS)
  {
    cout << "Error in writeScreen: vertical (" << y << ") is out of bounds.";
    return 1;
  }
  else 
  {
    cout << WINDOW_ROWS << string(WINDOW_COLUMNS - 3, '-') << endl;; //line WINDOW_ROWS
    
    int row, col;
    for (row = (WINDOW_ROWS - 1); row > 0; --row)
    {
      cout << setw(2) << row;
      if (row == y)
      {
        //for (col = 0; col < x; ++col)
        //  cout << ' ';
        //cout << '*';
        cout << string(x, ' ') << '*';
      }
      cout << endl;
    }
    
    cout << " 0" << string(WINDOW_COLUMNS - 3, '-') << endl; //line 0
  }
}

void cls()
{
  for (int i = 0; i < 100; ++i)
    cout << endl;
  return;
}
