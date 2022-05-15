/* 
mazeio.cpp
Justin Lenderman
lenderma@usc.edu
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a 
 *  2D dynamically  allocated array.
 * 
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem, 
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and 
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns 
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols) 
{
   // *** You complete **** CHECKPOINT 1
   //reads in file, rows, and cols
	ifstream ifile(filename);

  //if something goes wrong return NULL
  if(ifile.fail())
  {
    return NULL;
  }
  ifile >> *rows >> *cols;
  //gets how big maze array should be
  char **maze = new char*[*rows];
  char in;
  //reads in to array
  for(int i = 0; i < *rows; i ++)
  {
    maze[i] = new char[*cols + 1];
    for(int j = 0; j < *cols; j ++)
    {
      ifile >>in;
      maze[i][j] = in;
      if(maze[i][j] != '.'|| maze[i][j] != '#' || maze[i][j] != 'S' || maze[i][j] != 'F')
      {
        cout << "Error, input format incorrect.";
      }
    }
  }
  //close file and return maze
	ifile.close();
  return maze;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) 
{
   // *** You complete **** CHECKPOINT 1
   //prints out the number of rows and columns
  cout << rows << cols <<endl;

  //prints out maze
  for(int i = 0; i < rows; i ++)
  {
    for(int j = 0; j < cols; j++)
      cout << maze[i][j];
    cout << endl;
  }
  
}

