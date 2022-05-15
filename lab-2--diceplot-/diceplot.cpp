//Justin Lenderman
//lenderma@usc.edu
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int roll()
{
  
  int r = rand() % 6 + 1;
  return r;
}

void printHistogram(int counts[])
{
  for(int i = 0; i < 21; i++)
  {
    cout << i+4 << ":";
    for(int x = 0; x < counts[i]; x++)
    {
      cout << "X";
    }
    cout << endl;
  }
}

int main()
{
  srand(time(0));
  int number; 
  cout << "Enter a number: ";
  cin >> number;
  int testCounts[21] = {0};
  int sum, first, second, third, fourth;
  for(int i = 0; i < number; i++)
  {
    first = roll();
    second = roll();
    third = roll();
    fourth = roll();
    sum = first + second + third + fourth;
    testCounts[sum] += 1;
  }
  printHistogram(testCounts);
  return 0;
}


