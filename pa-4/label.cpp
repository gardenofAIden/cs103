//-------------------
//------------------
//CS103L - Programming Assignment
//------------------
//Justin Lenderman
//lenderma@usc.edu

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "bmplib.h" 
#include "queue.h"
using namespace std;

void usage() { 
    cerr << "usage: ./label <options>" << endl;
    cerr <<"Examples" << endl;
    cerr << "./label test_queue" << endl;
    cerr << "./label gray <input file> <outputfile>" << endl;
    cerr << "./label binary <inputfile> <outputfile>" << endl;
    cerr << "./label segment <inputfile> <outputfile>" << endl;
}

//==============================
//Function prototypes go here
void test_queue();
void clean(unsigned char ***input,unsigned char **gray,unsigned char **binary, int **labeled_image,int height , int width);
//--- TODO: you complete the rest --- CHECKPOINT 0
void rgb2gray (unsigned char ***rgb_in , unsigned char **gray_out, int height, int width );
void gray2binary(unsigned char **gray_in, unsigned char **binary_out, int height, int width);
int component_labeling(unsigned char **binary_in, int **labeled_image, int height, int width);
void label2RGB(int  **labeled_in, unsigned char ***rgb_out,int num_segments,int height,int width);
//==============================
// The main function, you do not need to make any changes to this function 
// However, we encourage you to try to understand what's going on in the main function
int main(int argc,char **argv) {
    srand(time(0));
    if(argc < 2 )  {
        usage();
        return -1;
    }        
    unsigned char ***input=0;
    unsigned char **gray=0;
    unsigned char **binary=0;
    int **labeled_image=0;
    if( strcmp("test_queue",argv[1]) == 0 ) { 
        test_queue();
    } 
    else if(strcmp("gray",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough argument for gray" << endl;
            return -1;
        }
        int height, width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            return -1;
        }
        //dynamically allocated a 2D gray image array            
        gray = new unsigned char*[height];
        for(int i=0;i<height;i++){
          gray[i] = new unsigned char[width];
        }
        //call rgb2gray to get the gray image from rgb
        rgb2gray(input,gray,height,width);
        if(writeGSBMP(argv[3],gray,height,width) != 0) { 
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        //call the function that handles memory deallocation
        clean(input,gray,binary,labeled_image,height,width);
    }
    else if(strcmp("binary",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough arguemnt for binary" << endl;
            return -1;
        }            
        int height,width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }            
        //dynamically allocated a 2D gray image array
        //dynamically allocated a 2D binary image array    
        gray = new unsigned char*[height];
        binary = new unsigned char*[height];
        for(int i=0;i<height;i++){
          gray[i] = new unsigned char[width];
          binary[i] = new unsigned char[width];
        }
        //call rgb2gray to get the gray image from rgb
        rgb2gray(input,gray,height,width);
        //call gray2binary to get the binary image from gray
        gray2binary(gray,binary,height,width);
        if(writeBinary(argv[3],binary,height,width) != 0) { 
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        //call the function that handles memory deallocation
        clean(input,gray,binary,labeled_image,height,width);   
    }
    else if(strcmp("segment",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough arguemnt for segment" << endl;
            return -1;
        } 
        int height,width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }            
        //dynamically allocated a 2D gray image array
        //dynamically allocated a 2D binary image array  
        gray = new unsigned char*[height];
        binary = new unsigned char*[height];
        for(int i=0;i<height;i++){
          gray[i] = new unsigned char[width];
          binary[i] = new unsigned char[width];
        }
        rgb2gray(input,gray,height,width);
        gray2binary(gray,binary,height,width);
        //dynamically allocated a 2D array for labels.
        labeled_image = new int*[height];
        for(int i=0;i<height;i++){
          labeled_image[i] = new int[width];
          for(int j=0;j<width;j++){
            labeled_image[i][j] = 0;
          }
        }
        int segments = component_labeling(binary, labeled_image, height, width); 
        cout<<"Segments found: "<< segments << endl;
        //replace 3D input image with 0 to be used as output.
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                for(int k=0;k<RGB;k++){
                  input[i][j][k] = 0;
                } 
            }
        }
        //label2rgb
        label2RGB(labeled_image, input , segments, height, width);
        if(writeRGBBMP(argv[3],input,height,width) != 0) {
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        //call the function that handles memory deallocation
        clean(input,gray,binary,labeled_image,height,width);
    }
   return 0;
}
//==============================
//Loop over the 'in' image array and calculate the single 'out' pixel value using the formula
// GS = 0.2989 * R + 0.5870 * G + 0.1140 * B 
void rgb2gray(unsigned char ***in,unsigned char **out,int height,int width) {
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            out[i][j] = (in[i][j][0]*0.2989) + (in[i][j][1]*0.5870) + (in[i][j][2]*0.1140);
        }
    }
}
//==============================
//Loop over the 'in' gray scale array and create a binary (0,1) valued image 'out'
//Set the 'out' pixel to 1 if 'in' is above the THRESHOLD (already defined), else 0
void gray2binary(unsigned char **in,unsigned char **out,int height,int width) {
for(int i = 0; i < height; i++)
{
  for(int j = 0; j < width; j++)
  {
    if(in[i][j] > THRESHOLD)
    {
        out[i][j] = 1;
    }
    else
    {
        out[i][j] = 0;
    }
  }
}
}
//==============================
//This is the function that does the work of looping over the binary image and doing the connected component labeling
//See the guide for more detail.
//- Should return number of segments or components found
//- Two disjoint components should not share the same label.
int component_labeling(unsigned char **binary_image,int **label,int height,int width) {
int current_label = 0;
Location current;
Queue q(height*width);
//initialize every cell in label array to 0
for(int i = 0; i < height; i++)
{
  for(int j = 0; j < width; j++)
  {
    label[i][j] = 0;
  }
}
bool **explored = new bool*[height];
for(int i = 0; i < height; i++)
{
  explored[i] = new bool[width];
}
for(int i = 0; i < height; i++)
{
  for(int j = 0; j < width; j++)
  {
    explored[i][j] = false;
  }
}
for(int i = 0; i < height; i++)
{
  for(int j = 0; j < width; j++)
    {
      if(binary_image[i][j] == 1 && !explored[i][j])
      {
        Location pixel;
        pixel.row = i;
        pixel.col = j;
        explored[i][j] = true;
        current_label++;
        q.push(pixel);

        label[pixel.row][pixel.col] = current_label;
        while(!q.is_empty())
        {
          current = q.pop();
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

          for(int k = 0; k < 4; k++)
          {
            int row_x = bor[k].row;
            int col_y = bor[k].col;
            if(row_x < height && col_y < width && row_x >=0 && col_y >=0)
            {
              if(binary_image[row_x][col_y] == 1 && !explored[row_x][col_y])
              {
                explored[row_x][col_y] = true;
                label[row_x][col_y] = current_label;
                q.push(bor[k]);
              }
            }
          }            
        }
      }
      else
      {
        continue;
      }
    }
}
for(int i = 0; i < height; i++)
  {
    delete[] explored[i];
  }     
  delete[] explored;
return (current_label);
}    
//==============================
//Randomly assign a color (RGB) to each segment or component
//No two segments should share the same color.
void label2RGB(int  **labeled_image, unsigned char ***rgb_image,int num_segments,int height,int width)
{
  //-- TODO: You complete -- CHECKPOINT 5
  int **color = new int*[num_segments];
  for(int i = 0; i < num_segments; i++)
  {
    color[i] = new int[RGB];
    for(int j = 0; j < RGB; j++)
    {
      color[i][j] = rand() % 256;
    }
  }
    for(int j = 0; j < height; j++)
    {
      for(int k = 0; k < width; k++)
      {
        int variable = labeled_image[j][k];
        if(labeled_image[j][k] == 0)
        {
          rgb_image[j][k][0] = 0;
          rgb_image[j][k][1] = 0;
          rgb_image[j][k][2] = 0;
        }
        else
        {
          rgb_image[j][k][0] = color[variable-1][0];
          rgb_image[j][k][1] = color[variable-1][1];
          rgb_image[j][k][2] = color[variable-1][2];
        }
      }
    }
    for(int i = 0; i < num_segments; i++)
    {
      delete[] color[i];
    }
    delete[] color;
}
//========= CHECKPOINT 6 ==============
//fill out this function to delete all of the dynamic arrays created
//-- these arrays are created in the main function.
void clean(unsigned char ***input,unsigned char **gray,unsigned char **binary, int **labeled_image,int height , int width) {
    if(input) {
        //TODO: You complete -- delete allocated input image array here (3D)
      for(int i = 0; i < height; i++)
      {
        for(int j = 0; j < width; j++)
        {
          delete[] input[i][j];
        }
        delete[] input[i];
      }
      delete [] input;
    } 
    if(gray){
        //TODO: You complete -- delete allocated gray-scale image here (2D)
      for(int i = 0; i < height; i++)
      {
        delete[] gray[i];
      }
      delete[] gray;
    }
    if(binary){
        //TODO: You complete -- delete allocated binary image array here (2D)
      for(int i = 0; i < height; i++)
      {
        delete[] binary[i];
      }
      delete[] binary;
    }
    if(labeled_image){
        //TODO: You complete -- delete allocated labeled array here (2D)
      for(int i = 0; i < height; i++)
      {
        delete[] labeled_image[i];
      }
      delete[] labeled_image;
    }
}
//==============================
//This function is used to test your queue implementation.
//You do not need to change it
void test_queue() { 
    // create some locations;
    Location three_one, two_two;
    three_one.row = 3; three_one.col = 1;
    two_two.row = 2; two_two.col = 2;

    //create an Queue with max capacity 5
    Queue q(5);

    cout << boolalpha;
    cout << q.is_empty() << endl;           // true
    q.push(three_one);
    cout << q.is_empty() << endl;           // false
    q.push(two_two);

    Location loc = q.pop();
    cout << loc.row << "," << loc.col << endl; // 3 1
    loc = q.pop();
    cout << loc.row << "," << loc.col << endl; // 2 2
    cout << q.is_empty() << endl;           // true
}
//----------------
//----------------
//----------------