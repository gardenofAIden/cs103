/********************************************************
 * Description:
 *  Displays a 64-bit integer (long long) with
 *   commas for thousands, millions, billions, etc.
 *
 * ** ABSOLUTELY NO ARRAYS, NO `string`, NO `vector` **
 *  usage is allowed.
 *
 * Instead, you may only declare:
 *
 *    bool,
 *    int, or
 *    int64_t (long long)
 *
 *  The only library function allowed is pow(base, exp)
 *    defined in the <cmath> library.
 *
 ********************************************************/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  long long n;
  
  cout << "Enter an integer:" << endl;
  /*====================*/
  /* Start of your code */
  int length = 0;
  int digits, divisor, num_commas;
  int counter = 0;
  cin >> n;
  if(n < 0)
  {
    cout << "-";
  }
  n = abs(n);
  long long same = n;
  // if only 3 digits then don't need to worry about commas
  if(n < 1000)
  {
    cout << n;
  }
  while( n != 0)
  {
    length ++;
    n /= 10;
  }
  if(length % 3 == 0)
  {
    num_commas = (length / 3) - 1;
  }
  else
  {
    num_commas = length / 3;
  }
  for(int len_copy = length; len_copy != 0; len_copy--)
  {
    divisor = pow(10, length - 1);
    digits = same/divisor;
    same = same % divisor;
    if(length % 3 ==1 || length % 3 ==2 )
    {
      cout << digits;
      length = length - 1;
    }
    else
    {
      cout <<"," << digits;
      length = length - 1;
    }
  }
  /* End of your code */
  /*==================*/
  return 0;
}
