/* 
maze.cpp
Justin Lenderman
lenderma@usc.edu
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
   int rows, cols, result;
   char** mymaze = NULL;
   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
   // <---TASK: COMPLETE THIS FOR CHECKPOINT 1
   mymaze = read_maze(argv[1], &rows, &cols);
   
   if (mymaze == NULL) {
      cout << "Error, input format incorrect." << endl;
      return 1;
   }
	 //================================
   // When working on Checkpoint 4, you will call maze_search here.
   // But for Checkpoint 1, just assume we found the path.
  
   result = maze_search(mymaze, rows, cols);
	
	
   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

	 //================================
   // ADD CODE BELOW
   // to delete all memory that read_maze allocated: CHECKPOINT 2
   for(int i = 0; i < rows; i ++)
   {
     delete [] mymaze[i];
   }
  delete [] mymaze;
  return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols) 
{
  // *** You complete **** CHECKPOINT 4
  Queue q(rows*cols);
  Location s;
  Location current;
  int start_found = 0; 
  int finish_found = 0;
  bool completed = false;

  //Find the start and finish cells 
  //and check that the maze is valid. Return -1 for a badly-formatted maze.
  for(int i = 0; i < rows; i ++)
  {
    for(int j = 0; j < cols; j ++)
    {
      if(maze[i][j] == 'S')
      {
        s.row = i;
        s.col = j;
        start_found ++;
      }
      if(maze[i][j] == 'F')
      {
        //f.row = i;
        //f.col = j;
        finish_found ++;
      }
    }
  }
  if(start_found != 1 || finish_found != 1)
  {
    return -1;
  }

  //Dynamically allocate the predecessor and explored arrays. 
  //If applicable, you may also need to initialize them.
  bool ** explored = new bool*[rows];
  for(int i = 0; i < rows; i++)
  {
    explored[i] = new bool[cols];
  }
  for(int i = 0; i < rows; i ++)
  {
    for(int j = 0; j < cols; j++)
    {
      explored[i][j] = false;
    }
  }
  Location **predecessor = new Location*[rows];
  for(int i = 0; i < rows; i ++)
  {
    predecessor[i] = new Location[cols];
  }
  
  //add start to the back
  q.add_to_back(s);

  //while queue is not empty and maze has not been completed
  while(!q.is_empty() && !completed)
  {
    current = q.remove_from_front();
    Location north, south, east, west;

    north.col = current.col + 1;
    north.row = current.row;
    west.col = current.col;
    west.row = current.row - 1;
    south.col = current.col - 1;
    south.row = current.row;
    east.col = current.col;
    east.row = current.row + 1;
    Location bor[4] = {north, west, south, east};

    //for each neighbor/border
    for(int i = 0; i < 4; i ++)
    {
      int row_x = bor[i].row;
      int col_y = bor[i].col;

      //if valid border
      if(row_x < rows && col_y < cols && row_x >=0 && col_y >=0)
      {
        //if valid, open, and not yet explored
        if (maze[row_x][col_y] == '.' && !explored[row_x][col_y])
        {
          //add to back of queue
          q.add_to_back(bor[i]);
          //mark as explored
          explored[row_x][col_y] = true;
          //set predecessor of the neighbor = loc?
          predecessor[row_x][col_y] = current;
        }
        //else you found the end!!!
        else if(maze[row_x][col_y] == 'F')
        {
          explored[row_x][col_y] = true;
          predecessor[row_x][col_y] = current;
          completed = true;
          break;
        }
      }
    }
  }
  
  //if maze was completed
  if(completed)
  {
    while(maze[current.row][current.col] != 'S')
    {
      maze[current.row][current.col] = '*'; 
      current = predecessor[current.row][current.col];
    }
  }
  
  //deallocate memory
  for(int i = 0; i < rows; i ++)
  {
    delete [] explored[i];
    delete [] predecessor[i];
  }
  delete[] explored;
  delete[] predecessor;

  return completed;
}