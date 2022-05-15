//Justin Lenderman
//lenderma@usc.edu

#include <iostream>
using namespace std;

int main()
{
  int min, max, num1, num2;
  int max_len = 0;
  int length = 0;
  int min_len = 999999999;
  cout << "Enter the range that you want to search: ";
  cin >> num1 >> num2;
  int num1_copy = num1;
  if(num2 < num1)
  {
    cout << "Invalid range";
  }

  for(int i = num1; i <= num2; i ++)
  {
    while(num1 != 1)
    {
      if(num1 % 2 == 1)
      {
        num1 = (num1 * 3) + 1;
        length ++;
      }
      else
      {
        num1 /= 2;
        length ++;
      }
    }
    if(length < min_len)
    {
      min_len = length;
      min = num1_copy;
    }
    if(length > max_len)
    {
      max_len = length;
      max = num1_copy;
    }
    num1_copy ++;
    num1 = num1_copy;
    length = 0;
  }


  cout << "Minimum length: " << min_len << endl << "Achieved by: "
  << min << endl << "Maximum length: " << max_len << endl << "Achieved by: "
  << max;

}