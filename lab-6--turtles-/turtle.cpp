//This file also starts out empty.
//Implement the Turtle class here.
#include "turtle.h"
#include <cmath>
Turtle:: Turtle (double x0, double y0, double dir0){
      x_pos = x0;
      y_pos = y0;
      dir = dir0; 
      color = draw:: BLACK;
      turned_on = true;
    } 
void Turtle:: turn(double deg)
{
  dir = dir + deg;
}

void Turtle:: move(double dist)
{
  double x1 = x_pos;
  double y1 = y_pos;
  double dir_radians = dir * (M_PI/180);
  double x2 = x1 +  dist*cos(dir_radians);
  double y2 = y1 + dist*sin(dir_radians);
  if(turned_on)
  {
    draw::setcolor(r, g, b);
    draw::line(x1, y1, x2, y2);
  }
  x_pos = x2;
  y_pos = y2;
}
void Turtle :: setColor(Color c)
{
  r = c.red;
  g = c.green;
  b = c.blue;
}

void Turtle :: off()
{
  turned_on = false;
}

void Turtle :: on()
{
  turned_on = true;
}