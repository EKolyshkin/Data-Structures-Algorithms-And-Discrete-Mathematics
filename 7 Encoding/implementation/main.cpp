/* Created by Egor Kolyshkin on 01/15/2022 */

#include "Encoder.h"
#include "HuffNode.h"
#include "Student.h"

#include <bitset>
#include <iostream>
#include <assert.h>

using namespace std;

void testStudent()
{
   cout << endl;
   Student me = Student();
   cout << "Created by: ";
   cout << me.FirstName() << " ";
   cout << me.LastName() << endl;
   cout << "Student ID: ";
   cout << me.StudentIdentifier();
   cout << endl
        << endl;
}

void testErrors()
{
   // INVALID MESSAGE CHARACTER
   try
   {
      vector<int> values =
          {8, 16, 1, 21, 19, 5, 20, 23, 14, 25, 4, 12,
           22, 10, 9, 11, 17, 24, 6, 3, 0, 7, 18, 15, 13, 2};
      Encoder test1(make_shared<vector<int>>(values));
      test1.Encode("hi ");
   }
   catch (const char *message)
   {
      cerr << message << endl;
   }

   // NOT ENOUGH FREQUENCIES
   try
   {
      vector<int> values =
          {8, 16, 1, 21, 19, 5, 20, 23, 14, 25,
           4, 12, 22, 10, 9, 11, 17, 24, 6, 3};
      Encoder test2(make_shared<vector<int>>(values));
   }
   catch (string message)
   {
      cerr << message << endl;
   }

   // INVALID FREQUENCIES

   try
   {
      vector<int> values =
          {8, 16, 1, 21, 19, 5, 20, 23, 14, 25, 0,
           12, 22, 10, 9, 11, 17, 24, 6, 3, 64, 36,
           47, 28, 17, 0};
      Encoder test3(make_shared<vector<int>>(values));
      test3.Encode("test failed");
   }
   catch (const char *message)
   {
      cerr << message << endl;
   }
}

void test1()
{
   vector<int> values =
      {8,16,1,21,19,5,20,23, 14, 25, 4, 12, 22, 10, 9,
       11, 17, 24, 6, 3, 26, 7, 18, 15, 13, 2,};
   Encoder test1(make_shared<vector<int>>(values));
   string messageString;
   shared_ptr<vector<char>> messageEncoded;

   test1.printTree();

   // test cases
   messageString = "whyisitdoingthat";
   messageEncoded = test1.Encode(messageString);
   shared_ptr<vector<char>> messageDecoded;

   cout << "Original message: " << messageString << endl;
   cout << "Encoded message: ";
   for (char c : *messageEncoded)
   {
      bitset<8> bits(c);
      cout << bits << " ";
   }
   cout << endl;
   cout << "Decoded message: ";
   cout << test1.Decode(test1.Encode(messageString)) << endl;

   messageString = "abcdefghijklmnopqrstuvwxyz";
   messageEncoded = test1.Encode(messageString);
   cout << "Original message: " << messageString << endl;
   cout << "Encoded message: ";
   for (char c : *messageEncoded)
   {
      bitset<8> bits(c);
      cout << bits << " ";
   }
   cout << endl;
   cout << "Decoded message: ";
   cout << test1.Decode(test1.Encode(messageString)) << endl;
   assert(test1.Decode(test1.Encode(messageString)) == messageString);

   assert(*test1.Encode(messageString) == *test1.Encode(test1.Decode(test1.Encode(messageString))));
}

void test2()
{
   vector<int> values =
       {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
   Encoder test1(make_shared<vector<int>>(values));

   // test1.printTree();

   // test cases
   string messageString = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
   shared_ptr<vector<char>> messageEncoded = test1.Encode(messageString);

   cout << "Original message: " << messageString << endl;
   cout << "Encoded message: ";
   for (char c : *messageEncoded)
   {
      bitset<8> bits(c);
      cout << bits;
   }
   cout << endl;
   cout << "Decoded message: ";
   cout << test1.Decode(messageEncoded) << endl;

   // empty message test
   try 
   {
      messageString = "";
      messageEncoded = test1.Encode(messageString);
      cout << "Original message: " << messageString << endl;
      cout << "Encoded message: ";
   }
   catch (const char* message)
   {
      cerr << message << endl;
   }

   for (char c : *messageEncoded)
   {
      bitset<8> bits(c);
      cout << bits;
   }
   cout << endl;
}

void customTest()
{
   srand(time(0));

   string messageString = "";
   cout << "Type the message you want to encode: ";
   getline(cin >> ws, messageString);
   cout << messageString << endl;

   vector<int> values = {};
   for (int i = 0; i < 26; i++)
   { // generates random frequencies
      values.push_back(rand() % 300);
   }

   Encoder test1(make_shared<vector<int>>(values));
   shared_ptr<vector<char>> messageEncoded = test1.Encode(messageString);

   // test1.printTree();

   cout << "Encoded message: ";
   for (char c : *messageEncoded)
   {
      bitset<8> bits(c);
      cout << bits;
   }
   cout << endl;
   cout << "Decoded message: ";
   cout << test1.Decode(test1.Encode(messageString)) << endl;
}

int main()
{
   testStudent();
   testErrors();
   test1();
   test2();
   customTest();

   return 0;
}