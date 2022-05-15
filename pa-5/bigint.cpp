#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

//******************************************************************
//START OF THE CONSTRUCTORS SECTION
//******************************************************************

/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}

/*
//  Create a BigInt from string.
//  Don't forget to set the base accordingly
//  The input string will contain
//      - numbers (0-9) and/or 
//      - uppercase letters (A-Z) [A=10, B=11, ... , Z=35]
//  The input string may contain
//      - a negative sign ('-') to signify that the number is negative.
//  Note: char '0' = int 48 (see ASCII table)
//  Note: char 'A' = int 65
*/
BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
    int size = s.size();
    base = setbase;
    string str = s;
    if(str[0] == '-')
    {
        isPositive = false;
        for(int i = size - 1; i >= 1; i--)
        {
            if(int(str[i] - '0') < 10)
            {
                vec.push_back(int(str[i] - '0'));
            }
            else
            {
                vec.push_back(int(str[i] - 55));
            }
        }
    }
    else
    {
      isPositive = true;
        for(int i = size - 1; i >= 0; i--)
        {
            if(int(str[i] - '0') < 10)
            {
                vec.push_back(int(str[i] - '0'));
            }
            else
            {
                vec.push_back(int(str[i] - 55));
            }
        }
    }
}

/*
//  Create a BigInt from int (base 10).
//  - Convert the int (base 10) input into a specified base (setbase).
//  - Don't forget to set the base accordingly
//  For example:
//     BigInt k(6,2) <- int 6 base 10 to BigInt base 2
//          - Result:  BigInt k with value 110 (base 2)
//     BigInt k(154,16) <- 154 base 10 to BigInt base 16
//          - Result: BigInt k with value 9A (base 16)
*/
BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
    base = setbase;
    int remainder;
    if(input == 0)
    {
      vec.push_back(0);
    }
    if(input >= 0)
    {
        isPositive = true;
    }
    else
    {
        isPositive = false;
        input = input * -1;
    }
    while(input > 0)
    {
        remainder = input % base;
        input = input / base;
        vec.push_back(remainder);
    }
    if(!isPositive)
    {
      vec.push_back('-' - '0');
    }

}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
// (You can also think of this function as the same as the assignment operator (=))
// (but without a return statement because you are overriding the current object)
*/
BigInt::BigInt(const BigInt &b){

    /************* You complete *************/
    *this = b;
}

/*
//  Assignment operator. (i.e., BigInt a = b;)
//  OVERRIDING a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt & BigInt::operator = (const BigInt &b){

    /************* You complete *************/
    vector<int> new_vec = b.vec;
    //int size = vec.size();
    //int new_size = new_vec.size();

    isPositive = b.isPositive;
    base = b.base;
    vec = b.vec;

    return *this; 
}


//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string(){

    /************* You complete *************/
    int size = vec.size();
    string s = "";
    char character;
    for(int i = size - 1; i >=0; i--)
    {
      character = vec[i];
        if(character < 10)
        {
          character  = (char)(vec[i]+48);
        }
        else
        {
          character = (char)(vec[i] + 55);
        }
        s+= character;
    }
  return s;//for now
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt >= INT_MAX, return INT_MAX.
//    If BigInt =< INT_MIN, return INT_MIN.
//  Note: 1. INT_MAX and INT_MIN are already defined for you
//           in the 'climits' library.
//        2. INT_MAX = 2147483647, INT_MIN = -2147483648
//           therefore, INT_MIN does not equal to (-INT_MAX)
*/
int BigInt::to_int() const{

    /************* You complete *************/
    int size = vec.size();
    int total = 0;
    for(int i = 0; i < size; i++)
    {
      int number = vec[i];
      total += ((pow(base,i)) * number);
      if(total == -2147483648 && isPositive == false)
      {
        return INT_MIN;
      }
      if(total == -2147483648 && isPositive == true)
      {
        return INT_MAX;
      }
      //cout << "TOTAL " << total << endl;
    }
    if(isPositive == false)
    {
      //cout << "Is negative" << endl;
      total *= -1;
      //cout <<"NEW TOTAL " << total;
      if(total >= INT_MAX)
      {
        return INT_MAX;
      }
      if(total <= INT_MIN)
      {
        return INT_MIN;
      }
    }
    else
    {
      if(total >= INT_MAX)
      {
        return INT_MAX;
      }
      if(total <= INT_MIN)
      {
        return INT_MIN;
      }
    }

  return total;//for now
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
//  See the HINT below
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    int asize = vec.size();
    int bsize = b.vec.size();
    //cout << b.isPositive << ' ' << isPositive << endl;
    if(isPositive && !b.isPositive)
    {
      return 1;
    }
    else if(!isPositive && b.isPositive)
    {
      return -1;
    }
    else if(asize < bsize && isPositive && b.isPositive)
    {
     // cout <<'a' << endl;
      return -1;
    }
    else if(asize < bsize && !isPositive && !b.isPositive)
    {
     // cout <<'a' << endl;
      return 1;
    }
    else if(asize > bsize && !isPositive && !b.isPositive)
    {
     // cout <<'a' << endl;
      return -1;
    }
    else if(asize > bsize)
    {
      //cout << 'b' << endl;
      return 1;
    }
    else
    {
      for(int i = asize - 1; i >=0; i--)
      {
        if(vec[i] == b.vec[i])
        {
          continue;
        }
        else if(vec[i] < b.vec[i] && isPositive && b.isPositive)
        {
          //cout << 'c' <<endl;
          return -1;
        }
        else if(vec[i] < b.vec[i] && !isPositive && !b.isPositive)
        {
          //cout << 'c' <<endl;
          return 1;
        }
        else if(vec[i] > b.vec[i] && isPositive && b.isPositive)
        {
          //cout << 'd' << endl;
          return 1;
        }
        else if(vec[i] > b.vec[i] && !isPositive && !b.isPositive)
        {
          //cout << 'd' << endl;
          return -1;
        }
      }
      //cout << 'e' << endl;
    }
    
    //HINT:
    //1. do NOT call the to_int() or to_string() function
    //2. do NOT convert bigInt to other datatypes first (e.g., long long, int)
    
    //First let's compare the signs
    //    - if the signs aren't the same,
    //              how do you know which one is larger?

    //If they have the same sign, let's compare their vec sizes 
    //    - what if both are positive, but a's vec is larger (a or b is larger?)
    //    - other cases?
    
    //If they have the same vec size, let's compare their digits one by one
    // Starting from the most-significant digits. --> in what vector position?
    // Remember that the BigInt vectors are in reverse order!
    //    - what if both are positive, but the digit of a is greater than that of b (a or b is larger?)
    //    - other cases?
    
    //If ALL digits are the same, then they MUST be equal!!
    return 0;
}


//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    return a.compare(b) == 0;
  
  //return false;//for now
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  int temp = a.compare(b);
  if(temp != 0)
  {
    return true;
  }
  
  return false;//for now
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
  int temp = a.compare(b);
  if(temp == 0 || temp == -1)
  {
    return true;
  } 
  
  return false;//for now
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    int temp = a.compare(b);
    if(temp == 0 || temp == 1)
  {
    return true;
  } 
  return false;//for now
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    return(a.compare(b) == 1);
  //return false;//for now
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

    
  return(a.compare(b) == -1);
  //return false;//for now
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator + (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  BigInt copy = a;
  copy += b;
  return copy;//for now
}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/

int carry_digit = 0;
bool nochange = false;
int sizea = vec.size();
int sizeb = b.vec.size();
int mina = min(sizea, sizeb);
int borrow = 0;
//gets bigger int on top
if(sizea < sizeb)
{
  nochange = false;
}
else if(sizea > sizeb)
{
  nochange = true;
}
else if(sizea == sizeb)
{
  for(int i = sizea - 1; i >=0; i--)
  {
    if(vec[i] > b.vec[i])
    {
      nochange = true;
      break;
    }
    else if(vec[i] < b.vec[i])
    {
      nochange = false;
      break;
    }
    else
    {
      continue;
    }
  }
}

vector<int> tempb = b.vec;
vector<int> tempa;
if(!nochange)
{
  //cout <<"change "<< endl;
  tempa = vec;
  vec = tempb;
  tempb = tempa;
}
int aSize = vec.size();
int bSize = tempb.size();
//cout << aSize << bSize << endl;

if(vec[0] == 0 && vec.size() == 1)
{
  vec = b.vec;
}
else if(b.vec[0] == 0 && b.vec.size() == 1)
{
  vec = vec;
}
else if((isPositive && b.isPositive) || (!isPositive && !b.isPositive))
{
  for(int i = 0; i < mina; i++)
  {
    int temp = vec[i] + tempb[i] + carry_digit;
    carry_digit = temp / base;
    vec[i] = temp % base;
  }
  int dig;
  if(aSize > bSize)
    {
      for (int i = tempb.size(); i < aSize; i++){
        dig = vec[i] + carry_digit;
        if (dig >= base)
        {
          carry_digit = 1;
          dig -= base;
        } 
        else 
        {
          carry_digit = 0;
        }
        vec[i] = dig;
      }
  }
  if (carry_digit != 0)
  {
    vec.push_back(carry_digit);
  }
}
else if((!isPositive && b.isPositive) || (isPositive && !b.isPositive))
{
  //cout << "different signs" << endl;
  for(int i = 0; i < mina; i++)
  {
    int difference = vec[i] - tempb[i] + borrow;
    if(difference < 0)
    {
      difference = difference + base;
      borrow = -1;
    }
    else{
      borrow = 0;
    }

    vec[i] = difference;
  }
  if(borrow == -1)
    {
      if(aSize > bSize)
      {
        if(vec[bSize] + borrow < 0)
        {
          int g = bSize;
          while(g < aSize)
          {
            if(vec[g] + borrow < 0)
            {
              vec[g] = vec[g] + borrow + base;
              borrow = -1;
            }
            else
            {
              vec[g] = vec[g] + borrow;
              borrow = 0;
            }
            g++;
          }
        }
        else
        {
          vec[bSize] = vec[bSize] + borrow;
        }
      }
    }
}

bool allzero = false;
int i = vec.size() - 1;
while(vec[i] == 0 && vec.size() != 1)
{
  vec.pop_back();
  i--;
}
for(unsigned int i = 0; i < vec.size(); i++)
{
  if(vec[i] == 0)
  {
    allzero = true;
  }
  else
  {
    allzero = false;
  }
}
if(allzero)
{
  for(unsigned int i = vec.size() - 1; i > 0 ; i--)
  {
    vec.pop_back();
  }
}

if(((!isPositive && nochange) || (!b.isPositive && !nochange) || (!isPositive && !b.isPositive)) && (!allzero))
{
  vec.push_back('-' - '0');
}
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator - (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  BigInt copy = a;
  copy -= b;
  return copy;
}


/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
//  Note: Think of base cases (e.g., subtract by itself)
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
bool nochange = true;
int sizea = vec.size();
int sizeb = b.vec.size();
int carry_digit = 0;
int mina = min(sizea, sizeb);
int borrow = 0;
if(sizea < sizeb)
{
  nochange = false;
}
else if(sizea > sizeb)
{
  nochange = true;
}
else if(sizea == sizeb)
{
  for(int i = sizea - 1; i >=0; i--)
  {
    if(vec[i] > b.vec[i])
    {
      nochange = true;
      break;
    }
    else if(vec[i] < b.vec[i])
    {
      nochange = false;
      break;
    }
    else
    {
      continue;
    }
  }
}
vector<int> tempb = b.vec;
vector<int> tempa;
if(!nochange)
{
  //cout <<"change "<< endl;
  tempa = vec;
  vec = tempb;
  tempb = tempa;
}
int aSize = vec.size();
int bSize = tempb.size();

if(vec[0] == 0 && vec.size() == 1)
{
  vec = b.vec;
}
else if(b.vec[0] == 0 && b.vec.size() == 1)
{
  vec = vec;
}
    /************* You complete *************/
    else if((!isPositive && !b.isPositive) || (isPositive && b.isPositive))
    {
      //normal subtraction
      //cout << "different signs" << endl;
      for(int i = 0; i < mina; i++)
      {
        int difference = vec[i] - tempb[i] + borrow;
        if(difference < 0)
        {
          difference = difference + base;
          borrow = -1;
        }
        else
        {
          borrow = 0;
        }

        vec[i] = difference;
      }
  if(borrow == -1)
    {
      if(aSize > bSize)
      {
        if(vec[bSize] + borrow < 0)
        {
          int g = bSize;
          while(g < aSize)
          {
            if(vec[g] + borrow < 0)
            {
              vec[g] = vec[g] + borrow + base;
              borrow = -1;
            }
            else
            {
              vec[g] = vec[g] + borrow;
              borrow = 0;
            }
            g++;
          }
        }
        else
        {
          vec[bSize] = vec[bSize] + borrow;
        }
      }
    }
    }
    else if((isPositive && !b.isPositive) || (!isPositive && b.isPositive))
    {
      //addition
      for(int i = 0; i < mina; i++)
      {
        int temp = vec[i] + tempb[i] + carry_digit;
        carry_digit = temp / base;
        vec[i] = temp % base;
      }
      int dig;
      if(aSize > bSize)
        {
          for (int i = tempb.size(); i < aSize; i++){
            dig = vec[i] + carry_digit;
            if (dig >= base)
            {
              carry_digit = 1;
              dig -= base;
            } 
            else 
            {
              carry_digit = 0;
            }
            vec[i] = dig;
          }
      }
      if (carry_digit != 0)
      {
        vec.push_back(carry_digit);
      }
    }
bool allzero = false;
int i = vec.size() - 1;
while(vec[i] == 0 && vec.size() != 1)
{
  vec.pop_back();
  i--;
}
for(unsigned int i = 0; i < vec.size(); i++)
{
  if(vec[i] == 0)
  {
    allzero = true;
  }
  else
  {
    allzero = false;
  }
}
if(allzero)
{
  for(unsigned int i = vec.size() - 1; i > 0 ; i--)
  {
    vec.pop_back();
  }
}
//cout <<"all zero" << allzero <<endl;
//cout << isPositive << b.isPositive << endl;
  if(((!isPositive && !b.isPositive && nochange && !allzero)))
  {
    //cout <<'a' << endl;
    vec.push_back('-' - '0');
  }
  if(((!isPositive && b.isPositive && !allzero)))
  {
    //cout <<'b' << endl;
    vec.push_back('-' - '0');
  }
  if(((isPositive && b.isPositive && !nochange && !allzero)))
  {
    //cout <<'c' << endl;
    vec.push_back('-' - '0');
  }
  
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator * (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt copy = a;
    copy *= b;
    return copy;

}





/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    //if(isPositive != b.isPositive)
    //{
      //isPositive = false;
    //}
    //else
    //{
      //isPositive = true;
    //}
    BigInt total(0, base);
    int carry = 0;
    int product = 0;
      for(unsigned int i = 0; i < b.vec.size(); i++)
      {
        BigInt tempo(base);
        for(unsigned int k = 0; k < i; k++)
        {
          tempo.vec.push_back(0);
        }
        for(unsigned int j = 0; j < vec.size(); j++)
        {
          product = (b.vec[i] * vec[j]) + carry;
          carry = product / base;
          tempo.vec.push_back(product % base);
          product = 0;
          //cout << tempo.vec[j] << endl;
        }
        if(carry > 0)
        {
          tempo.vec.push_back(carry);
        }
        total += tempo;
        carry = 0;
        //total.vec.push_back(tempo.vec[i]);
      }
      total.isPositive = isPositive;
      *this = total;

bool allzero = false;
int i = vec.size() - 1;
while(vec[i] == 0 && vec.size() != 1)
{
  vec.pop_back();
  i--;
}
for(unsigned int i = 0; i < vec.size(); i++)
{
  if(vec[i] == 0)
  {
    allzero = true;
  }
  else
  {
    allzero = false;
  }
}
if(allzero)
{
  for(unsigned int i = vec.size() - 1; i > 0 ; i--)
  {
    vec.pop_back();
  }
}


    if(((isPositive && !b.isPositive) || (!isPositive && b.isPositive)) && !allzero)
    {
      vec.push_back('-' - '0');
    }
    
return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator / (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt copy = a;
    copy /= b;
    return copy;
}


/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    /************* You complete *************/
    BigInt remainder(base);
    BigInt quotient(base);
    divisionMain(b, quotient, remainder);
    vec = quotient.vec;
    return *this;


}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator % (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt copy = a;
    copy %= b;
    return copy;
}


/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }
    /************* You complete *************/

    BigInt remainder(base);
    BigInt quotient(base);
    divisionMain(b, quotient, remainder);
    vec = remainder.vec;
    return *this;
  
  
  
  
    return *this;
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
//  Note: 1. This should behave like integer division
//        2. What are the base cases?? (e.g., div by itself)
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

    /************* You complete *************/
//a < b = -1
//int quotient = 0;
//int remainder;
//bool nochange = true;
BigInt zero(0, base);
BigInt temp;
BigInt dd(base);
BigInt dr(base);
dd.vec = vec;
dr.vec = b.vec;
int pos;
//cout << "compare " << compare(b) << endl;

//numbers are the same
if(compare(b) == 0)
{
  //cout << "equal numbers" << endl;
  quotient.vec.push_back(1);
  remainder.vec.push_back(0);
}
//dividend is smaller than divisor a < b
else if(compare(b) == -1)
{
  //cout << 'b' << endl;
  quotient.vec.push_back(0);
  remainder.vec = dd.vec;
}
else
{
  pos = vec.size() - 1;
  BigInt dividend_seq(dd.vec[pos], base);
  while(dividend_seq < dr)
  {
    //cout << "enter" << endl;
    pos--;
    dividend_seq.vec.insert(dividend_seq.vec.begin(), dd.vec[pos]);
  }
while(pos >=0)
{
  //cout << "poop" << endl;
  int times = 0;
  while(dividend_seq >= dr)
  {
    dividend_seq -= dr;
    times += 1;
  }
  quotient.vec.insert(quotient.vec.begin(), times);
  if(dividend_seq.vec[0] == 0 && dividend_seq.vec.size() == 1)
  {
    dividend_seq.vec.pop_back();
  }
  if(pos > 0)
  {
    dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos-1]);
  }
  pos--;
}
if(dividend_seq.vec.size() == 0)
{
  dividend_seq.vec.push_back(0);
}
remainder.vec = dividend_seq.vec;
}


bool allzero = false;
bool allzeroremainder = false;
int i = quotient.vec.size() - 1;
while(quotient.vec[i] == 0 && quotient.vec.size() != 1)
{
  quotient.vec.pop_back();
  i--;
}
for(unsigned int i = 0; i < quotient.vec.size(); i++)
{
  if(quotient.vec[i] == 0)
  {
    allzero = true;
  }
  else
  {
    allzero = false;
  }
}
for(unsigned int i = 0; i < remainder.vec.size(); i++)
{
  if(remainder.vec[i] == 0)
  {
    //cout << "is true" << endl;
    allzeroremainder = true;
  }
  else
  {
    //cout << "is false" << endl;
    allzeroremainder = false;
    break;
  }
}
if(allzero)
{
  for(unsigned int i = quotient.vec.size() - 1; i > 0 ; i--)
  {
    quotient.vec.pop_back();
  }
}
if(((isPositive && !b.isPositive) || (!isPositive && b.isPositive)) && !allzero)
  {
    //cout << "quotient negative" << endl;
    quotient.vec.push_back('-' - '0');
  }

  if(((!isPositive && !b.isPositive) || (!isPositive && b.isPositive)) && !allzeroremainder)
  {
    //cout << "remainder negative" << endl;
    remainder.vec.push_back('-' - '0');
  }


}



/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt copy = a;
    copy.exponentiation(b);
    return copy;
}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
    //a is base and b is exponent
    BigInt bottom = *this;
    bottom.isPositive = true;
    BigInt ex = b;
    BigInt one(1, base);
    BigInt two(2, base);
    BigInt zero(0, base);
    BigInt temp = one;
    if(b.vec[0] == 0 && b.vec.size() == 1)
    {
      bottom = one;
    }
    else if(vec[0] == 0 && vec.size() == 1)
    {
      bottom = zero;
    }
    else if(vec[0] == 1 && vec.size() == 1)
    {
      bottom = one;
    }
    else
    {
    while(ex > one)
    {
      if(ex.vec[0] % 2 == 0)
      {
        //then it is even
        bottom = bottom * bottom;
        ex = ex / two;
      }
      else
      {
        //then it is odd
        temp  = temp * bottom;
        //int x = a;
        bottom = bottom * bottom;
        ex = ex / two;
      }
    }
    bottom = bottom * temp;
    }

  bottom.isPositive = isPositive;
  if(!isPositive && (b % two == one))
  {
    cout << "lol" << endl;
    bottom.vec.push_back('-' - '0');
  }
    *this = bottom;
  
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    /************* You complete *************/
    BigInt copy = a;
    copy.modulusExp(b,m);
    return copy;
}


/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus 
//          after every call to the *= operator.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
        BigInt bottom = *this;
    bottom.isPositive = true;
    BigInt ex = b;
    BigInt one(1, base);
    BigInt two(2, base);
    BigInt zero(0, base);
    BigInt temp = one;
    if(b.vec[0] == 0 && b.vec.size() == 1)
    {
      bottom = one;
    }
    else if(vec[0] == 0 && vec.size() == 1)
    {
      bottom = zero;
    }
    else if(vec[0] == 1 && vec.size() == 1)
    {
      bottom = one;
    }
    else
    {
    while(ex > one)
    {
      if(ex.vec[0] % 2 == 0)
      {
        //then it is even
        bottom = bottom * bottom;
        ex = ex / two;
        bottom = bottom % m;
      }
      else
      {
        //then it is odd
        temp  = temp * bottom;
        //int x = a;
        bottom = bottom * bottom;
        ex = ex / two;
        bottom = bottom % m;
        temp = temp % m;
      }

    }
    bottom = bottom * temp;
    bottom = bottom % m;
    }

  bottom.isPositive = isPositive;
  if(!isPositive && (b % two == one))
  {
    cout << "lol" << endl;
    bottom.vec.push_back('-' - '0');
  }
    *this = bottom;

  
  
    return *this;
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF SANITY CHECK FUNCTIONS
//YOU CAN USE THEM, BUT DO NOT CHANGE ANYTHING
//THESE FUNCTIONS ARE COMPLETE.
//******************************************************************
void BigInt::printVecItems(){
  cout<<"[";
  for(size_t i = 0;i<vec.size();i++){
    cout<<vec[i];
    if(i < vec.size()-1){
      cout<<",";
    }
  }
  cout<<"]"<<endl;
}

bool BigInt::getSign(){
	return isPositive;
}

int BigInt::getBase(){
	return base;
}
//******************************************************************
//END OF SANITY CHECKS SECTION
//******************************************************************