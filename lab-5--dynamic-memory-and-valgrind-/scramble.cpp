// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <cstring>
#include <fstream>

using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);

int main(int argc, char *argv[]) {
  if(argc != 2)
  {
    cout <<"Try again.";
    return 1;
  }
  ifstream ifile (argv[1]);
  if(ifile.fail())
  {
    cout << "Couldn't open file." << endl;
    return 1;
  }
  int x;
  ifile >> x;
  if(ifile.fail())
  {
    cout << "Not an int." << endl;
    return 1;
  }
  srand(time(0));
  char guess[80];

  bool wordGuessed = false;
  int numTurns = 10;
  int numWords, numLetters, string_length;

  /* Add code to declare the wordBank array, read in each word
     and store it */
  char **wordBank = new char*[x];
  char buffer[41];
  char file_input = 'a';
  for(int i = 0; i < x; i ++)
  {
    ifile >> buffer;
    string_length = strlen(buffer);
    wordBank[i] = new char[string_length + 1];
    strcpy(wordBank[i], buffer);
  }

  ifile.close();
    
  // Pick a random word from the wordBank
  int target = rand() % x;
  int targetLen = strlen(wordBank[target]);

  // Make a dynamically-allocated copy of the word and scramble it
  char* word = new char[targetLen+1];
  strcpy(word, wordBank[target]);
  permute(word, targetLen);
  
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while (!wordGuessed && numTurns > 0) {
    cout << "Scrambled word: " << word << endl;
    cout << "What do you guess the original word is? ";
    cin >> guess;
    /* Complete the next line of code */
      
    // ADD code to check if the guess is equal to the chosen word.
                  // wordGuessed should be true if they are equal, and false otherwise
    if(strcmp(guess, wordBank[target]) == 0)
    {
      wordGuessed = true;
    }  
    numTurns--;   // Every guess counts as a turn
  }
  if (wordGuessed) {
    cout << "You win!" << endl;
  }
  else {
    cout << "Too many turns...You lose!" << endl;
  }
  /* Free up any necessary memory */
    
  delete [] word;
  for(int i = 0; i < x; i++)
  {
    delete[] wordBank[i];
  }
  delete [] wordBank;
  return 0;
}

// Scramble the letters. See "Knuth shuffle".
void permute(char items[], int len) {
  for (int i = len-1; i > 0; --i) {
    int r = rand() % i;
    char temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}

