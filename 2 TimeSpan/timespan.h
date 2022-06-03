//
// Created by Yusuf Pisan on 4/2/18.
// Modified by Egor Kolyshkin on 10/17/21.
//

#ifndef ASS2_TimeSpan_H
#define ASS2_TimeSpan_H

#include <iostream>

using namespace std;

class TimeSpan
{
   // prints out TimeSpan in digital format
   friend ostream& operator<<(ostream& out, const TimeSpan& ts);

public:

   // CONSTRUCTORS 

   // constructor
   explicit TimeSpan(double hour = 0, double minute = 0, double second = 0);


   // GETTERS

   // return hour component of TimeSpan
   int getHour() const;

   // return minute component of TimeSpan
   int getMinute() const;

   // return second component of TimeSpan
   int getSecond() const;

   // return true if TimeSpan is 0 or larger
   bool isPositive() const;

   // add TimeSpan to this TimeSpan
   TimeSpan operator+(const TimeSpan& ts) const;

   // subtract TimeSpan from this TimeSpan
   TimeSpan operator-(const TimeSpan& ts) const;

   // multiply this TimeSpan with positive integer
   TimeSpan operator*(unsigned int number) const;

   // return true if TimeSpan is equal to this TimeSpan
   bool operator==(const TimeSpan& ts) const;

   // return true if TimeSpan is NOT equal to this TimeSpan
   bool operator!=(const TimeSpan& ts) const;
   
   // return true if TimeSpan is less than this TimeSpan
   bool operator>(const TimeSpan& ts) const;

   // return true if TimeSpan is less than or equal to this TimeSpan
   bool operator>=(const TimeSpan& ts) const;
  
   // return true if TimeSpan is more than this TimeSpan 
   bool operator<(const TimeSpan& ts) const;
  
   // return true if TimeSpan more than or equal to this TimeSpan 
   bool operator<=(const TimeSpan& ts) const;


   // SETTERS

   // add TimeSpan to this TimeSpan and modify this TimeSpan
   TimeSpan& operator+=(const TimeSpan& ts);

   // subtract TimeSpan from this TimeSpan and modify this TimeSpan
   TimeSpan& operator-=(const TimeSpan& ts);

private:

   // FIELDS

   int hour;   // hours in TimeSpan
   int minute; // minutes in TimeSpan
   int second; // seconds in TimeSpan


   // HELPERS 

   // returns TimeSpan values in total seconds
   int toSeconds(const double& hour, const double& minute, const double& second) const;

   // returns string of absolute value of parameter with extra 0
   // if the absolute value is less than 10
   string padValue(int value) const;
};

#endif // ASS2_TimeSpan_H
