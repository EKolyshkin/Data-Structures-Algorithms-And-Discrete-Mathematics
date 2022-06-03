//
// Created by Yusuf Pisan on 4/2/18.
// Modified by Egor Kolyshkin on 10/17/21.
//

#include "timespan.h"
#include <cmath>

// prints out TimeSpan in digital format
ostream& operator<<(ostream& out, const TimeSpan& ts)
{   
   if (ts.hour == 0 && (ts.minute < 0 || ts.second < 0))
   {  // add negative sign if hour is 0 and other values are negative
      out << "-";
   }

   out << ts.hour << ":" << ts.padValue(ts.minute) << ":" << ts.padValue(ts.second);
   return out;
}


// CONSTRUCTORS

// parameterized constructor
// pre: hour, minute, second are desired values
// post: new TimeSpan object is created with desired values
TimeSpan::TimeSpan(double hour, double minute, double second)
{
   int seconds = toSeconds(hour, minute, second);

   this->hour = seconds / 3600;
   this->minute = seconds % 3600 / 60;
   this->second = seconds % 3600 % 60;
}


// GETTERS

// return hour component of timespan
int TimeSpan::getHour() const
{
   return hour;
}

// return minute component of timespan
int TimeSpan::getMinute() const
{
   return minute;
}

// return second component of timespan
int TimeSpan::getSecond() const
{
   return second;
}

// return true if timespan is 0 or larger
bool TimeSpan::isPositive() const
{
   return hour > 0 || minute > 0 || second > 0;
}

// add TimeSpan to this TimeSpan
TimeSpan TimeSpan::operator+(const TimeSpan& ts) const
{
   int hour = this->hour + ts.hour;
   int minute = this->minute + ts.minute;
   int second = this->second + ts.second;

   return TimeSpan(hour, minute, second);
}

// subtract TimeSpan from this TimeSpan
TimeSpan TimeSpan::operator-(const TimeSpan& ts) const
{
   int hour = this->hour - ts.hour;
   int minute = this->minute - ts.minute;
   int second = this->second - ts.second;

   return TimeSpan(hour, minute, second);
}

// multiply this TimeSpan with positive integer
TimeSpan TimeSpan::operator*(unsigned int number) const
{
   int hour = this->hour * number;
   int minute = this->minute * number;
   int second = this->second * number;

   return TimeSpan(hour, minute, second);
}

// return true if TimeSpan is equal to this TimeSpan
bool TimeSpan::operator==(const TimeSpan& ts) const
{
   return (this->hour == ts.hour && this->minute == ts.minute && this->second == ts.second);
}

// return true if TimeSpan is NOT equal to this TimeSpan
bool TimeSpan::operator!=(const TimeSpan& ts) const
{
   return (this->hour != ts.hour || this->minute != ts.minute || this->second != ts.second);
}

// return true if TimeSpan is less than this TimeSpan
bool TimeSpan::operator>(const TimeSpan& ts) const
{
   return toSeconds(this->hour, this->minute, this->second) > toSeconds(ts.hour, ts.minute, ts.second);
}

// return true if TimeSpan is less than or equal to this TimeSpan
bool TimeSpan::operator>=(const TimeSpan& ts) const
{
   return toSeconds(this->hour, this->minute, this->second) >= toSeconds(ts.hour, ts.minute, ts.second);
}

// return true if TimeSpan is more than this TimeSpan
bool TimeSpan::operator<(const TimeSpan& ts) const
{
   return toSeconds(this->hour, this->minute, this->second) < toSeconds(ts.hour, ts.minute, ts.second);
}

// return true if TimeSpan more than or equal to this TimeSpan  
bool TimeSpan::operator<=(const TimeSpan& ts) const
{
   return toSeconds(this->hour, this->minute, this->second) <= toSeconds(ts.hour, ts.minute, ts.second);
}

// convert TimeSpan constructor values to seconds
int TimeSpan::toSeconds(const double& hour, const double& minute, const double& second) const
{
   return round(hour * 3600 + minute * 60 + second);
}

// returns string of absolute value of parameter with extra 0
// if the absolute value is less than 10
string TimeSpan::padValue(int value) const
{
   value = abs(value);

   if (value < 10)
   {
      return "0" + to_string(value);
   }
   else
   {
      return "" + to_string(value);
   }
}


// SETTERS

// add TimeSpan to this TimeSpan and modify this TimeSpan
TimeSpan& TimeSpan::operator+=(const TimeSpan& ts)
{
   int hour = this->hour + ts.hour;
   int minute = this->minute + ts.minute;
   int second = this->second + ts.second;

   TimeSpan temp(hour, minute, second);

   this->hour = temp.hour;
   this->minute = temp.minute;
   this->second = temp.second;

   return *this;
}

// subtract TimeSpan from this TimeSpan and modify this TimeSpan
TimeSpan& TimeSpan::operator-=(const TimeSpan& ts)
{
   int hour = this->hour - ts.hour;
   int minute = this->minute - ts.minute;
   int second = this->second - ts.second;

   TimeSpan temp(hour, minute, second);

   this->hour = temp.hour;
   this->minute = temp.minute;
   this->second = temp.second;

   return *this;
}