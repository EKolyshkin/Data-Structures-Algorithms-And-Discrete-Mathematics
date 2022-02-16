#include <cassert>
#include <iostream>
#include <sstream>

#include "timespan.h"
#include <cmath>

using namespace std;

// testing constructor
void test1()
{
  //   int hour = 1; int minute = 20; int second = 30;
  //   cout << remainder(hour, 1) * 3600 + remainder(minute, 1) * 60 + second << endl;
  
  TimeSpan ts(1, 20, 30);
  stringstream ss;
  ss << ts;
  // cout << ts << endl;
  assert(ss.str() == "1:20:30"); // 4830 seconds

  TimeSpan ts2(4, -20, -90);
  ss.str("");
  ss << ts2;
  // cout << "'" << ss.str() << "'" << endl;
  assert(ss.str() == "3:38:30");

  TimeSpan ts3(1.5, 30.5, -90);
  ss.str("");
  ss << ts3;
  // cout << ss.str() << endl;
  assert(ss.str() == "1:59:00");

  TimeSpan ts4(0, 0.07, 0);
  ss.str("");
  ss << ts4;
  assert(ss.str() == "0:00:04");

  TimeSpan two(0, 0);
  TimeSpan one(0);
  // TimeSpan def();

  cout << "test1 complete" << endl;
}

// testing equality, addition, subtraction, multiplication
void test2()
{
  TimeSpan ts(1, 20, 30);
  TimeSpan ts2(1, 20, 30);
  TimeSpan ts3(0, 0, 0);

  assert(ts == ts2);
  assert(!(ts != ts2));
  assert(ts != ts3);
  // cout << (ts2 * 3) << endl;
  assert((ts + ts + ts) == (ts2 * 3));
  assert((ts * 5) == (ts2 * 4) + ts2);
  assert((ts * 5) == (ts2 * 6) - ts2);
  assert((ts + ts - ts) == ((ts2 * 2) - ts));
  assert((ts - ts2) == ts3);
  assert((ts3 * 5) == ts3);
  cout << "test2 complete" << endl;
}

void test3()
{
  TimeSpan ts0(0, 0, 0);
  TimeSpan ts1(0, 0, 10);
  TimeSpan ts2 = ts0 - ts1;
  assert(ts1.isPositive() && !ts2.isPositive());
  stringstream ss;
  ss << ts2;
  assert(ss.str() == "-0:00:10");
  cout << "test3 complete" << endl;
}

void test4()
{
  TimeSpan ts0(0, 0, 0);
  TimeSpan ts1(0, 0, 10);
  TimeSpan ts2(-1, 20, 30);
  TimeSpan ts3(-4, 20, -90);
  TimeSpan ts4(0, 0, -10);
  TimeSpan ts5(0, 0);

  assert(ts1 > ts0);
  assert(ts2 <= ts1);
  assert(ts0 >= ts0);
  assert(ts1 < ts1 == false);
//   cout << ts0 - (ts1 * 2) << endl;
  assert((ts0 -= (ts1 * 1)) == ts4);
//   cout << ts0 << endl;
//   ts1 += ts4;
//   cout << ts1 << endl;
  assert((ts1 += ts4) == ts5);
//   cout << ts2 << endl;
//   ts2 -= ts3;
//   cout << ts2 << endl;
  cout << "test4 complete" << endl;
}

int main()
{
  test1();
  test2();
  test3();
  test4();

  cout << "Done." << std::endl;
  return 0;
}