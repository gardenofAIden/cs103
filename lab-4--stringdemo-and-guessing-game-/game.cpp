// game.cpp
// Hangman game illustrates string library functions, 
// character arrays, arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype. we'll define this below.
int processGuess(char* word, const char* targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char* wordBank[] = {"computer", "president", "trojan", "program",
                          "coffee", "library", "football", "popcorn", 
                          "science", "engineer"};

const int numWords = 10;

int main()
{
  srand(time(0));
  char guess;
  bool wordGuessed = false;
  int numTurns = 10;

  // Pick a random word from the wordBank
  const char* targetWord = wordBank[rand() % numWords];

  // More initialization code as needed
  char word[80];  // a blank array to use to build up the answer
                  // It should be initialized with *'s and then
                  //  change them to the actual letters when the 
                  //  user guesses the letter

  //gets length of word
  int word_length = strlen(targetWord);
  int len = strlen(targetWord);
  
  //assign asterick for length of word
  for(int i = 0; i < word_length; i++)
  {
    word[i] = '*';
  }

  //continue doing this while attempts is positive and word length is positive
  while(numTurns > 0 && word_length != 0)
  {
    cout << "Current word: ";
    for(int i = 0; i < len; i++)
    {
      cout << word[i];
    }
    cout << endl;
    cout << numTurns << " remain...Enter a letter to guess:" << endl;
    cin >> guess;
    int count = processGuess(word,targetWord,guess);

    if(count !=0)
    {
      word_length -= count;
    }
    else
    {
      numTurns --;
    }
  }
    if(word_length == 0)
    {
      wordGuessed = true;
      cout << "The word was: " << targetWord << ". You win!" << endl;
    }
    else if(numTurns == 0)
    {
      cout << "Too many turns...You lose!"<<endl;
    }
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  // Print out end of game status 
  return 0;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to 
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
int processGuess(char* word, const char* targetWord, char guess)
{
  int counter = 0;
  int word_length1 = strlen(targetWord);
  for(int i = 0; i < word_length1; i++)
  {
    //if guess is right
    if(guess == targetWord[i])
    {
      word[i] = targetWord[i];
      counter++;
    }
  }

  //returns how many occurences of guess were found
  return counter;
}