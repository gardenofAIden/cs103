#include "bigint.h"
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <string>
using namespace std;
string BigInt:: to_string()
{
  //size of vector
  int size = integers.size();
  //empty string
  string s = "";
  //converts int to char in reverse
  for(int i = size - 1; i >=0; i--)
  {
    char character  = (char)(integers[i]+48);
    s+= character;
  }
  return s;
}
void BigInt:: add(BigInt b)
{
  //gets difference in size of vectors
  int size_diff = integers.size() - b.integers.size();
  //makes it positive since i couldn't get abs() to work
  if(size_diff < 0)
  {
    size_diff = size_diff + (-2*size_diff);
  }
  //adds extra zeroes to one vector or the other
  for(int i = 0; i < size_diff; i++)
  {
    //add zeroes to integers vector if smaller
    if(integers.size() < b.integers.size())
    {
      integers.push_back(0);
    }
    //add zeroes to b vector if smaller
    else if(integers.size() > b.integers.size())
    {
      b.integers.push_back(0);
    }
  }
  // the digit you carry
  int carry_digit = 0;
  //iterates through whole integers vector
  for(unsigned int i = 0; i < integers.size(); i++)
  {
    //adds up the two numbers in the ones place then tens place...
    int temp = integers[i] + b.integers[i] + carry_digit;
    //if temp is like 15 you write the 5 and carry the 1
    carry_digit = temp / 10;
    //the index in vector array will now be equal to 5
    integers[i] = temp % 10;
  }
  //if the carry_digit is greater than 0 then push back the carry digit
  if(carry_digit > 0)
  {
    integers.push_back(carry_digit);
  }

}
BigInt::BigInt(string s)
{
  //converts char to integer
  for(int i = s.size()-1; i >=0; i--)
  {
    int number  = (int)(s[i]) - 48;
    integers.push_back(number);
  }
}