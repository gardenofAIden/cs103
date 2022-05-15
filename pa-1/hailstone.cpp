#include <iostream>
using namespace std;

int main()
{
int number;
int length = 0;
cout << "Enter a number: ";
cin >> number;
while(number != 1)
{
  if(number % 2 == 1)
  {
    number = (number * 3) + 1;
    length ++;
    cout << number << " ";
  }
  else
  {
    number /= 2;
    length ++;
    cout << number << " ";
  }


}
  cout << endl << "Length: " << length;

  
}