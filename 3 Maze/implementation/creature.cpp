// Creature methods
// Modified by Egor Kolyshkin on 10/31/21

#include "creature.h"
// #include <iostream>


// CONSTRUCTORS

// constructs creature on row Row and column Col
Creature::Creature(int Row, int Col) : Row(Row), Col(Col)
{
}


// MUTATORS

// prints current creature location: C(row, column)
std::ostream &operator<<(std::ostream &Out, const Creature &Creature)
{
   Out << "C(" << Creature.getRow() << ", " << Creature.getColumn() << ")";
   return Out;
}

// solves maze with creature and returns path
string Creature::solve(Maze &Maze)
{
   string Path;                              // path to exit in direction characters
   Maze.markAsPath(getRow(), getColumn());   // marks starting location as path

   if (!atExit(Maze))                     
   {                                // if starting location is not an exit
      Path = goNorth(Maze);         // try going north
      if (!atExit(Maze))
      {                             // if exit wasn't reached
         Path = goWest(Maze);       // try going west
         if (!atExit(Maze))
         {                          // if exit wasn't reached
            Path = goEast(Maze);    // try going east

            if (!atExit(Maze))
            {                        // if exit wasn't reached
               Path = goSouth(Maze); // try going south
            }
         }
      }
   }

   return Path;
}

// goes north with creature recursively
string Creature::goNorth(Maze &Maze)
{
   string Path;                  // path to exit in direction characters
   int NextRow = getRow() - 1;   // next north cell row
   int NextCol = getColumn();    // next north cell column

   // if next cell is clear, inside the maze, and not visited
   if (Maze.isClear(NextRow, NextCol) && Maze.isInside(NextRow, NextCol) && !Maze.isVisited(NextRow, NextCol))
   {
      setCords(NextRow, NextCol);         // moves creature to next north cell
      Maze.markAsPath(NextRow, NextCol);  // marks creature cell as path
      Path = "N";                         // marks north as path direction

      // std::cout << "Going to " << NextRow << ", " << NextCol << "." << std::endl;

      if (!atExit(Maze))                  
      {                                   // if exit not reached
         Path.append(goNorth(Maze));      // try going north
         if (!atExit(Maze))
         {                                // if exit still not reached
            Path.append(goWest(Maze));    // then try going west
            if (!atExit(Maze))
            {                             // if exit still not reached
               Path.append(goEast(Maze)); // then try going east
               if (!atExit(Maze))         
               {                          // if exit NEVER reached 
                  Maze.markAsVisited(NextRow, NextCol);  // mark as visited
                  setCords(NextRow + 1, NextCol);        // then backtrack to south
               }
            }
         }
      }
   }

   return Path; // returns empty path if creature already at exit
}

// goes west with creature recursively
string Creature::goWest(Maze &Maze)
{
   string Path;                        // path to exit in direction characters
   int NextRow = getRow();             // next west cell row
   int NextCol = getColumn() - 1;      // next west cell column

   // if next cell is clear, inside the maze, and not visited
   if (Maze.isClear(NextRow, NextCol) && Maze.isInside(NextRow, NextCol) && !Maze.isVisited(NextRow, NextCol))
   {
      setCords(NextRow, NextCol);         // moves creature to next west cell
      Maze.markAsPath(NextRow, NextCol);  // marks creature cell as path
      Path = "W";                         // marks west as path direction

      // std::cout << "Going to " << NextRow << ", " << NextCol << "." << std::endl;

      if (!atExit(Maze))                  
      {                                   // if exit not reached
         Path.append(goNorth(Maze));      // try going north
         if (!atExit(Maze))
         {                                // if exit still not reached
            Path.append(goWest(Maze));    // then try going west
            if (!atExit(Maze))
            {                             // if exit still not reached
               Path.append(goSouth(Maze));// then try going south
               if (!atExit(Maze))         
               {                                         // if exit NEVER reached 
                  Maze.markAsVisited(NextRow, NextCol);  // mark as visited
                  setCords(NextRow, NextCol + 1);        // then backtrack to east
               }
            }
         }
      }
   }
   
   return Path; // returns empty path if creature already at exit
}

// goes east with creature recursively
string Creature::goEast(Maze &Maze)
{
   string Path;                        // path to exit in direction characters
   int NextRow = getRow();             // next east cell row
   int NextCol = getColumn() + 1;      // next east cell column

   // if next cell is clear, inside the maze, and not visited
   if (Maze.isClear(NextRow, NextCol) && Maze.isInside(NextRow, NextCol) && !Maze.isVisited(NextRow, NextCol))
   {
      setCords(NextRow, NextCol);         // moves creature to next east cell
      Maze.markAsPath(NextRow, NextCol);  // marks creature cell as path
      Path = "E";                         // marks east as path direction

      // std::cout << "Going to " << NextRow << ", " << NextCol << "." << std::endl;

      if (!atExit(Maze))                  
      {                                   // if exit not reached
         Path.append(goNorth(Maze));      // try going north
         if (!atExit(Maze))
         {                                // if exit still not reached
            Path.append(goEast(Maze));    // then try going east
            if (!atExit(Maze))
            {                             // if exit still not reached
               Path.append(goSouth(Maze));// then try going south
               if (!atExit(Maze))         
               {                                         // if exit NEVER reached 
                  Maze.markAsVisited(NextRow, NextCol);  // mark as visited
                  setCords(NextRow, NextCol - 1);        // then backtrack to east
               }
            }
         }
      }
   }
   
   return Path; // returns empty path if creature already at exit
}

// goes south with creature recursively
string Creature::goSouth(Maze &Maze)
{
   string Path;                     // path to exit in direction characters
   int NextRow = getRow() + 1;      // next south cell row
   int NextCol = getColumn();       // next south cell column

   // if next cell is clear, inside the maze, and not visited
   if (Maze.isClear(NextRow, NextCol) && Maze.isInside(NextRow, NextCol) && !Maze.isVisited(NextRow, NextCol))
   {
      setCords(NextRow, NextCol);         // moves creature to next south cell
      Maze.markAsPath(NextRow, NextCol);  // marks creature cell as path
      Path = "S";                         // marks south as path direction

      // std::cout << "Going to " << NextRow << ", " << NextCol << "." << std::endl;

      if (!atExit(Maze))                  
      {                                   // if exit not reached
         Path.append(goWest(Maze));       // try going north
         if (!atExit(Maze))
         {                                // if exit still not reached
            Path.append(goEast(Maze));    // then try going east
            if (!atExit(Maze))
            {                             // if exit still not reached
               Path.append(goSouth(Maze));// then try going south
               if (!atExit(Maze))         
               {                                         // if exit NEVER reached 
                  Maze.markAsVisited(NextRow, NextCol);  // mark as visited
                  setCords(NextRow - 1, NextCol);        // then backtrack to north
               }
            }
         }
      }
   }
   
   return Path; // returns empty path if creature already at exit
}

// sets creature coordinates to row Row and column Col
bool Creature::setCords(int Row, int Col)
{
   this->Row = Row;
   this->Col = Col;
   return true;
}


// ACCESSORS

// returns true if creature is at exit
bool Creature::atExit(const Maze &Maze) const
{
   return (getRow() == Maze.getExitRow() && getColumn() == Maze.getExitColumn());
}

// gets current creature row coordinate
int Creature::getRow() const
{
   return Row;
}

// gets current creature column coordinate
int Creature::getColumn() const
{
   return Col;
}