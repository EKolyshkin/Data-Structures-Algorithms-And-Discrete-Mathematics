// Created by Egor Kolyshkin on 10/06/2021.
// Library class demonstrating partially filled arrays.
// Can add/remove/find books in library.

#include "library.h"
#include <iostream>

using namespace std;

// constructor: initializes library name and number of books to default value of zero
// pre: Name is desired library name
// post: new library object is created with number of books zero and name Name
Library::Library(const string& Name) : libraryName(Name), numberOfBooks(0)
{
}

// destructor (nothing on heap)
// pre: Library object exists
// post: Library object is destroyed
Library::~Library()
{
}

// SETTERS

// add a new book
// pre: BookName is desired name of book to add
// post: return true if successful, false if book already in library
bool Library::addBook(const string& BookName)
{
   if (findBook(BookName) == -1 && numberOfBooks < MAX)
   {
      books[numberOfBooks] = BookName;
      numberOfBooks++;
      return true;
   }
   else
   {
      return false;
   }
}

// remove a book (return true if successfully removed, false if book not in library)
// pre: BookName is desired name of book to remove
// post: book is removed, number of books goes down by one
bool Library::removeBook(const string &BookName)
{
   int index = findBook(BookName);

   if (index == -1)
   {
      return false;
   }
   else
   {
      // move last book to empty index
      moveLastBook(index);
      return true;
   }
}

// moves last book to empty index
// pre: BookIndex is the index of book to remove
// post: returns true after decreasing number of books
// and moving last book in place of removed one
bool Library::moveLastBook(const int& BookIndex)
{
   books[BookIndex] = books[numberOfBooks];
   numberOfBooks--;
   return true;
}

// GETTERS

// list all books in library
// pre: none
// post: prints all books in library
void Library::listAllBooks() const
{
   cout << *this;
}

// checks if book is already in library
// pre: BookName is desired name of book to check for 
// post: returns true if book found in library and prints message, false otherwise
bool Library::isInLibrary(const string &BookName) const
{
   if (findBook(BookName) != -1)
   {
      cout << "Book is already in library!" << endl;
      return true;
   }

   return false;
}

// find total number of books
// pre: BookName is the name of book to find
// post: returns index if book is in library, -1 if book is not in library
int Library::findBook(const string& BookName) const
{
   for (int i = 0; i < numberOfBooks; i++)
   {
      if (books[i] == BookName)
      {
         return i;
      }
   }

   return -1;
}

// display all books in library
// pre: Out is desired ostream object, Lib is desired library to out
// post: returns Out ostream
ostream& operator<<(ostream& Out, const Library& Lib)
{
   for (int i = 0; i < Lib.numberOfBooks; i++)
   {
      Out << Lib.books[i] << endl;
   }
   
   return Out;
}
