//Justin Lenderman
//lenderma@usc.edu
#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int top, int left, int height, int width) {
  //image[top][left] = 0;
  for(int a = 0; a < height; a++)
  {
    if(a + top >= 0 && left>=0 && a + top <=256 && left <=256){
    image[a + top][left] = 0;
    }
  }
  for(int b = 0; b < width; b++)
  {
    if(b + left >= 0 && top>=0 && b + left <=256 && top <= 256){
    image[top][b + left] = 0;
    }
  }
  for(int c = 0; c < height; c++)
  {
    if(c + top >=0 && c + top <=256 && width + left <=256 && width + left >=0){
    image[c + top][width + left] = 0;
    }
  }
  for(int d = 0; d < width; d++)
  {
    if(d + left >= 0 && d + left <=256 && height + top <=256 && height + top >= 0){
    image[height + top][d + left] = 0;
    }
  }
}


// Fill in this function:
void draw_ellipse(int cy, int cx, int height, int width) 
{
double rx = (width / 2);
double ry = (height / 2);

for (double theta=0.0; theta < 2*M_PI; theta += .01) 
{
  double x = (rx * cos(theta)) + (cx);
  double y = (ry * sin(theta)) + (cy);
  if(x >=0 && y >=0 && x <= 256 && y <= 256){
  image[(int)y][(int)x] = 0;
  }
}
}
int main() {
  int input, one, two, three, four;
   // initialize the image to all white pixels
   cout << "To draw a rectangle, enter: 0 top left height width" << endl<<
    "To draw an ellipse, enter: 1 cy cx height width" << endl <<
    "To save your drawing as output.bmp and quit, enter: 2" << endl;
    cin >> input;
    //sets screen white
   for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
         image[i][j] = 255;
      }
   }
   
   // Main program loop here
   while(input != 2)
   {
    if(input == 0 || input == 1)
    {
      cin >> one >> two >> three >> four;
    }
    if(input == 2)
   {
     writeGSBMP("output.bmp", image);
     exit(0);
   }
    else if(input == 0)
    {
      draw_rectangle(one, two, three, four);
    }
    else if(input == 1)
    {
      draw_ellipse(one, two, three, four);
    }
    cin >> input;
    }
   // Write the resulting image to the .bmp file
   writeGSBMP("output.bmp", image);
   
   return 0;
}
