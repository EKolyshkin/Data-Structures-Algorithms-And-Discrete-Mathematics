//
// Created by Yusuf Pisan on 3/26/18.
// Modified by Egor Kolyshkin on 10/06/2021.
//

#ifndef ASS1_LIBRARY_H
#define ASS1_LIBRARY_H

#include <string>

// Only for class code, OK to use namespace
using namespace std;

// Library holds books - can add, remove and list books
class Library
{
   // display all books in library
   friend ostream &operator<<(ostream& Out, const Library& Lib);

public:
   // constructor: initializes library name and number of books to default value of zero
   // pre: Name is desired library name
   // post: new library object is created with number of books zero and name Name
   explicit Library(const string& Name);

   // destructor (nothing on heap)
   // pre: Library object exists
   // post: Library object is destroyed
   virtual ~Library();

   // SETTERS

   // add a new book
   // pre: BookName is desired name of book to add
   // post: return true if successful, false if book already in library
   bool addBook(const string& BookName);

   // remove a book (return true if successfully removed, false if book not in library)
   // pre: BookName is desired name of book to remove
   // post: book is removed, number of books goes down by one
   bool removeBook(const string& BookName);

   // GETTERS

   // list all books in library
   // pre: none
   // post: prints all books in library
   void listAllBooks() const;

   // checks if book is already in library
   // pre: BookName is desired name of book to check for 
   // post: returns true if book found in library and prints message, false otherwise
   bool isInLibrary(const string& BookName) const;

private:
   // maximum number of books in library
   static const int MAX = 100;

   // name of library
   string libraryName;

   // total number of books in library
   int numberOfBooks;

   // array that holds all books in library
   string books[MAX];

   // GETTERS

   // find total number of books
   // pre: BookName is the name of book to find
   // post: returns index if book is in library, -1 if book is not in library
   int findBook(const string& BookName) const;

   // SETTERS

   // moves last book to empty index
   // pre: BookIndex is the index of book to remove
   // post: returns true after decreasing number of books
   // and moving last book in place of removed one
   bool moveLastBook(const int& BookIndex);
};

#endif  // ASS1_LIBRARY_H
