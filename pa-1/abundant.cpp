/********************************************************
 * Description:
 *   Displays the top 3 most "abundant" (see writeup)
 *   numbers in the input sequence.  The input sequence
 *   is assumed to be valid natural numbers separated
 *   by spaces and ending with 0.
 *
 *   ABSOLUTELY NO ARRAY or `string`/`vector`/etc. usage
 *   is allowed!

 *   You may only declare: bool, int, or unsigned int
 *   No library functions (beyond cin/cout) are allowed.
 *
 *   You may NOT modify any of the given template code.
 *   This ensures our automated checkers can parse your
 *   output.  Failure to follow this direction will lead
 *   to a score of 0 on this part of the assignment.
 ********************************************************/
 // Justin Lenderman
 //lenderma@usc.edu
#include <iostream>
using namespace std;
int main()
{
  // n1 is the number with the highest abundance, a1
  // n2 is the number with the 2nd-highest abundance, a2
  // n3 is the number with the 3rd-highest abundance, a3
  unsigned int n1 = 0, n2 = 0, n3 = 0;
  int a1 = 0, a2 = 0, a3 = 0;

  // num_abundant counts how many numbers in the input
  // sequence are abundant
  int num_abundant = 0;

  cout << "Enter a sequence of natural numbers, separated by spaces, ";
  cout << "and ending with 0."<< endl;

  /*====================*/
  /* Start of your code */
  int abundant_value = 0;
  int number_input;

  cin >> number_input;
  while(number_input != 0)
  {
    for (int i = 1; i <= number_input/ 2; i++)
    {
      if(number_input % i == 0)
      {
        abundant_value += i;
      }
    }
  
  if(abundant_value > number_input)
  {
    num_abundant ++;
  if(abundant_value > a1)
  {
    a3 = a2;
    n3 = n2;
    a2 = a1;
    n2 = n1;
    a1 = abundant_value;
    n1 = number_input;
    
  }
  else if(abundant_value > a2)
  {
    a3 = a2;
    n3 = n2;
    a2 = abundant_value;
    n2 = number_input;
    
  }
  else if(abundant_value > a3)
  {
    a3 = abundant_value;
    n3 = number_input;
  }
  }
  cin >> number_input;
  abundant_value = 0;
}
  /* End of your code */
  /*==================*/
  
  cout << "Abundant number count: " << num_abundant << endl;
  cout << "Top 3 most abundant numbers: " << endl;
  cout << n1 << " : " << a1 << endl;
  cout << n2 << " : " << a2 << endl;
  cout << n3 << " : " << a3 << endl;

  return 0;
}
