#include "draw.h"
#include "turtle.h"

int main()
{
  draw::setrange(-100,100);
  draw::setpenwidth(5);
  Turtle turtle1(20,20,50);
  Turtle turtle2(30,30,90);
  Turtle turtle3(40,40,70);
  Turtle turtle4(50,50,80);

  turtle1.setColor(draw::BLACK);
  turtle2.setColor(draw::PINK);
  turtle3.setColor(draw::BLUE);
  turtle4.setColor(draw::RED);
  for(int i = 0; i< 10; i++)
  {
    turtle1.move(2*i);
    turtle2.move(i);
    turtle3.move(2*i);
    turtle4.move(i);
    draw::show(50);
  }

}

void turn90 (Turtle turtle, )