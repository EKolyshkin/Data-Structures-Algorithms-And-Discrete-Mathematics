#include "Student.h"
#include "Index.h"

#include <iostream> //cout
#include <memory>   //shared pointer
#include <vector>   //vector
#include <string>   //string
#include <fstream>
#include <algorithm>

using namespace std;

bool isAlphaNum(char c)
{
   return (c > 64 && c < 91) || (c > 96 && c < 123) || (c > 47 && c < 58);
}

void printPair(shared_ptr<string> key, int value)
{
   cout << *key << ", " << value << endl;
}

string removePunc(string word)
{
   string newWord = "";
   
   for (char c : word)
   {
      if (isAlphaNum(c))
      {
         newWord.push_back(tolower(c));
      }
   }

   return newWord;
}

int main()
{
   Index i;
   fstream file;
   string word, t, q;
   string filename = "book.txt";
   file.open(filename.c_str());

   while (file >> word)
   {
      shared_ptr<string> key = make_shared<string>(removePunc(word));
      int value = i.Find(key);
      
      if (value == -1)
      { // if adding for the first time, initialize the count
         value = 1;
      }
      else
      { // increment current count
         value += 1;
      }

      i.Insert(key, value);
   }

   i.InOrderVisit(printPair);
}