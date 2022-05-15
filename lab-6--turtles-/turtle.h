//This file starts out empty!
//Define the Turtle class here.
#include "draw.h"
class Turtle{
  public:
    Turtle (double x0, double y0, double dir0);
    void move(double dist);
    void turn(double deg);
    void setColor(Color c);
    void off();
    void on();
  private:
    double x_pos;
    double y_pos;
    double dir;
    bool turned_on;
    Color color;
    int r;
    int g;
    int b;
};