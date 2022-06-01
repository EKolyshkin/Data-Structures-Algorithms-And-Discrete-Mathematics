/* Created by Egor Kolyshkin on 02/08/2022 */

#include <string>

#ifndef STUDENT_H
#define STUDENT_H

class Student
{
public:
   Student()
   {
   }

   std::string FirstName()
   {
      return "Egor";
   }

   std::string LastName()
   {
      return "Kolyshkin";
   }

   int StudentIdentifier()
   {
      return 1611725;
   }
};

#endif // STUDENT_H