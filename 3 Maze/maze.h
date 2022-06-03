// Maze header
// Modified by Egor Kolyshkin on 10/31/21

#ifndef ASS3_MAZE_H
#define ASS3_MAZE_H

#include <ostream>

using namespace std;

enum CELL { CLEAR, WALL, PATH, VISITED }; // four conditions of cell in maze

class Maze
{
   // prints maze in current condition
   friend ostream &operator<<(ostream &Out, const Maze &Maze);

private:
   // FIELDS
   const static int MAX_SIZE = 100; // maximum width and height value
   char Field[MAX_SIZE][MAX_SIZE];  // maze field made of characters
   int Width, Height;               // width and height of maze
   int ExitRow, ExitColumn;         // exit row and column location

public:
   // MUTATORS
   explicit Maze(const string &FileName); // constructs maze fields of chars from file FileName
   void markAsPath(int Row, int Col);     // marks location as path to exit with "*"
   void markAsVisited(int Row, int Col);  // marks location as visited with "+"

   // ACCESSORS
   int getExitRow() const;                // gets exit row coordinate of maze
   int getExitColumn() const;             // gets exit column coordinate of maze
   bool isClear(int Row, int Col) const;  // returns true if location is clear
   bool isInside(int Row, int Col) const; // returns true if location is inside maze
   bool isVisited(int Row, int Col) const;// returns true if location is visited
};

#endif //ASS3_MAZE_H
