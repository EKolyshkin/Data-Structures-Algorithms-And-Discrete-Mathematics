// Maze methods
// Modified by Egor Kolyshkin on 10/31/21

#include <fstream>
#include <iostream>
#include <string>

#include "maze.h"

using namespace std;


// CONSTRUCTORS

// constructs maze fields of chars from file FileName
// For Clion, need the following line in CMakeLists.txt so maze.txt is found
// at the same location as the cpp files
// # need to load data files from current directory as cpp files
// set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
Maze::Maze(const string &FileName)
{
   ifstream InFile;
   InFile.open(FileName);

   if (!InFile)
   {
      cout << "Unable to open file";
      exit(1); // terminate with error
   }

   InFile >> Width >> Height;
   InFile >> ExitRow >> ExitColumn;
   string Str;
   getline(InFile, Str);

   for (int Row = 0; Row < Height; ++Row)
   {
      for (int Col = 0; Col < Width; ++Col)
      {
         InFile.get(Field[Row][Col]);
         // cout << Row << ", " << col << ": " << field[Row][col] << endl;
      }

      getline(InFile, Str);
   }
}


// MUTATORS

// prints maze in current condition
ostream &operator<<(ostream &Out, const Maze &Maze)
{
   for (int Row = 0; Row < Maze.Height; ++Row)
   {
      for (int Col = 0; Col < Maze.Width; ++Col)
      {
         Out << Maze.Field[Row][Col];
      }

      Out << endl;
   }

   Out << endl;
   return Out;
}

// marks location as path to exit with "*"
void Maze::markAsPath(int Row, int Col)
{
   Field[Row][Col] = '*';
   // std::cout << "Marking " << Row << ", " << Col << " as path." << std::endl;
}

// marks location as visited with "+"
void Maze::markAsVisited(int Row, int Col)
{
   Field[Row][Col] = '+';
   // std::cout << "Marking " << Row << ", " << Col << " as visited." << std::endl;
}


// ACCESSORS

// gets exit row coordinate of maze
int Maze::getExitRow() const
{
   return ExitRow;
}

// gets exit column coordinate of maze
int Maze::getExitColumn() const
{
   return ExitColumn;
}

// returns true if location is clear
bool Maze::isClear(int Row, int Col) const
{
   return Field[Row][Col] == ' ';
}

// returns true if location is inside maze
bool Maze::isInside(int Row, int Col) const
{
   return (Row <= this->Height && Col <= this->Width);
}

// returns true if location is visited
bool Maze::isVisited(int Row, int Col) const
{
   return Field[Row][Col] == '+';
}