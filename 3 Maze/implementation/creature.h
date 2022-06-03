// Creature header
// Modified by Egor Kolyshkin on 10/31/21

#ifndef ASS3_CREATURE_H
#define ASS3_CREATURE_H

#include "maze.h"
#include <ostream>


class Creature
{
   // prints current creature location: C(row, column)
   friend ostream &operator<<(ostream &Out, const Creature &Creature);

private:
   // FIELDS
   int Row;  // row creature location
   int Col;  // column creature location

public:
   // MUTATORS
   Creature(int Row, int Col);      // constructs creature on row Row and column Col
   string solve(Maze &Maze);        // solves maze with creature and returns path
   string goNorth(Maze &Maze);      // goes north with creature recursively
   string goWest(Maze &Maze);       // goes west with creature recursively
   string goEast(Maze &Maze);       // goes east with creature recursively
   string goSouth(Maze &Maze);      // goes south with creature recursively
   bool setCords(int Row, int Col); // sets creature coordinates to row Row and column Col

   // ACCESSORS
   bool atExit(const Maze &Maze) const;   // returns true if creature is at exit
   int getRow() const;                    // gets current creature row coordinate
   int getColumn() const;                 // gets current creature column coordinate
};

#endif //ASS3_CREATURE_H
