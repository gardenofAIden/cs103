/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA 2
/******************************************************************************/
//Justin Lenderman
//lenderma@usc.edu
/* program that plays blackjack against computer*/
// Add other #includes if you need
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */

 //used to switch card values, exchange a[j] and a[i]
void swap (int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
//shuffles the cards
void shuffle(int cards[])
{
  for(int i = NUM_CARDS - 1; i > 0; i--)
  {
    //random integer between 0 and i inclusive
    int j = rand() % (i+1);
    swap(&cards[i], &cards[j]);
  }
}
/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  /******** You complete ****************/
  int number, suitss;

  //gets the mod when dividing by 13 since mod 13 gives number value of card in card array
  number = id % 13;
  //quotient when dividing by 13 tells the suit of card: 0 is hearts, 1 is S etc.
  if(id / 13 == 0)
  {
    suitss = 0;
  }
  else if(id / 13 == 1)
  {
    suitss = 1;
  }
  else if(id / 13 == 2)
  {
    suitss = 2;
  }
  else
  {
    suitss = 3;
  }
  //prints out card number and suit
  cout << type[number] << "-" << suit[suitss] << " ";
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  //mod 13 will give the correct index in values array, will adjust for aces later
  int value_card = id % 13;
  return value[value_card];
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  //prints out all the cards in hand
  for(int i = 0; i < numCards; i++)
  {
    printCard(hand[i]);
  }
  cout << endl;
}
/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
  //score of hand
  int score = 0;
  for(int i = 0; i < numCards; i ++)
  {
    int x = cardValue(hand[i]);
    score += x;
    //if one of the card is an ace and the score is over 21 make ace a 1
    if((score > 21 && (hand[i] == 12 || hand[i] == 25|| hand[i] == 38 || hand[i] == 51))||
      (score > 21 && (hand[1] == 12 || hand[1] == 25|| hand[1] == 38 || hand[1] == 51))||
      (score > 21 &&(hand[0] == 12 || hand[0] == 25|| hand[0] == 38 || hand[0] == 51)))
    {
      score = score - 10;
    }
  }
  return score;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);
  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  //define a variable to see if player wants to play again or not
  char playagain;
  //runs through program once before asking if they want to play again or not
  do{
    //assigns cards array to id values
    for(int i = 0; i < 52; i++) 
    {
      cards[i] = i;
    }
    //shuffles deck
    shuffle(cards);

    /*defines some variables such as size of player/dealers hand, 
    whether they hit or not, index of card deck*/
    char decision;
    int card_counter = 0;
    int d_size = 0;
    int p_size = 0;

    /*gives player and dealer two cards, player gets first and third card
    dealer gets second and fourth*/
    for(int i = 0; i < 4; i++)
    {
      if(i % 2 == 1)
      {
        dhand[d_size] = cards[i];
        card_counter++;
        d_size ++;
      }
      else
      {
        phand[p_size] = cards[i];
        card_counter ++;
        p_size ++;
      }
    }
    //prints out one of dealer's cards and both of player's cards
    cout << "Dealer:  ? ";
    printCard(dhand[1]);
    cout << endl;
    //loops forever, use break to get out of loop
    while(true)
    {
      //prints player hand
      cout << "Player: ";
      printHand(phand, p_size);

      //gets scores for both hands
      int player_score = getBestScore(phand, p_size);
      int dealer_score = getBestScore(dhand, d_size);

      //if player score is over 21 then player loses
      if(player_score > 21)
      {
        cout << "Player busts" << endl;
        cout << "Lose " << player_score << " " << dealer_score;
        break;
      }
      //if player score is 21 they win and dealer draws more cards
      else if(player_score == 21)
      {
        cout << "Dealer: ";
        int dealer_score2 = getBestScore(dhand, d_size);
        //dealer draws cards as long as score is below 17
        for(int i = 2; dealer_score2 < 17; i ++)
        {
          dhand[d_size] = cards[card_counter];
          dealer_score2 = getBestScore(dhand, d_size);
          card_counter ++;
          d_size++;
        }
        //if dealer hand is only 2 cards then print both cards and get score of hand
        if(d_size == 2)
        {
          printHand(dhand, d_size);
          dealer_score2 = getBestScore(dhand, d_size);
        }
        //for some reason if dealer hand is more than 2 cards need to do d_size -1 to print hand and get score
        else if (d_size > 2)
        {
        printHand(dhand, d_size-1);
        dealer_score2 = getBestScore(dhand, d_size-1);
        }
        cout << "Win " << player_score << " " << dealer_score2 << endl;
        //loop terminated
        break;
      }
      //asks user whether they want to hit or stay
      cout << "Type 'h' to hit and 's' to stay:" << endl;
      cin >> decision;

      //player chooses hit
      if(decision == 'h')
      {
        //print out a new card for player and increments hand size and cardindex
        phand[p_size] = cards[card_counter];
        card_counter++;
        p_size++;
        continue;
      }
      //player chooses stand
      else if(decision == 's')
      {
        //print out a new card for dealer
        int dealer_score1 = getBestScore(dhand, d_size);
        //dealer draws as long as score is less than 17
        for(int i = 2; dealer_score1 < 17; i ++)
        {
          dhand[d_size] = cards[card_counter];
          dealer_score1 = getBestScore(dhand, d_size);
          card_counter ++;
          d_size++;
        }
        //same thing as comment on line 235
        cout << "Dealer: ";
        if(d_size == 2)
        {
          printHand(dhand, d_size);
        }
        //same thing as comment on line 241
        else
        {
          printHand(dhand, d_size - 1);
        }
        //if dealer score is over 21 player wins
        if(dealer_score1 > 21)
        {
          cout <<"Dealer busts" << endl;
          cout << "Win " << player_score << " " << dealer_score1;
          break;
        }
        //if scores are equal than they tie
        else if(dealer_score1 == player_score)
        {
          cout << "Tie " << player_score << " " << dealer_score1;
          break;
        }
        //if player score is bigger than dealer score then player wins
        else if(player_score > dealer_score1)
        {
          cout << "Win " << player_score << " " << dealer_score1;
          break;
        }
        //if dealer score is bigger than player score then dealer wins
        else if(dealer_score1 > player_score)
        {
          cout << "Lose " << player_score << " " << dealer_score1;
          break;
        }
      }
    }

    //asks user if they want to play again and reads in answer
    cout << endl << endl <<"Play again? [y/n]" << endl;
    cin >> playagain;

    //if player answers n then exit loop and end program
    if(playagain == 'n')
    {
      break;
    }
    //continue this loop as long as playagain is y
  }while(playagain == 'y');

  //program executed successfully
  return 0;
}
