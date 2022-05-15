#include <iostream>
#include <fstream>
#include <string>
#include "banner.h"

using namespace std;

#ifdef RF
Letter* read_font(const char* fname)
{
    //open fname file
    ifstream ifile(fname);
    //if opening file fails return NULL
    if(ifile.fail())
    {
        return NULL;
    }
    //allocate on heap an array of 
    //letter structs of length 95
    Letter* array = new Letter[95];
    int i = 0;
    //loops through all 95 characters in font
    while(i < 95)
    {
        //read over sets of 8 lines
        for(int j = 0; j < 8; j ++)
        {
            string line;
            //reads in each line
            getline(ifile, line);
            //first line goes into .lines[0] then .lines[1] etc...
            array[i].lines[j] = line;
        }
        //converts to character
        array[i].c = char(i + 32);
        //increment
        i++;
    }
    //return pointer to array of letter structs
    return array;   
}
#endif

#ifdef MB
Banner make_banner(string message, Letter* font)
{
    //Instantiate a local Banner struct
    Banner real_message;
    //set .message data member to input parameter message
    real_message.message = message;
    //loops through every line
    for(int i = 0; i < 8; i ++)
    {
        //loops through each character in message
        for(int j = 0; j < message.length(); j++)
        {
            //creates message by adding individual characters(of 8 line)
            // of a certain font
            real_message.output[i] += font[int(message[j]) - 32].lines[i];
        }
    }
    return real_message;
}
#endif

#ifdef PB
void print_banner(Banner b)
{
    for(int i=0;i<8;i++)
    {
        cout << b.output[i] << endl;
    }
}
#endif

#ifdef MAIN
int main(int argc, char* argv[])
{
    //checks that at least one command line argument is given
    if(argc < 2)
    {
        cout << "No font file given." << endl;
        return 1;
    }
    //calls read_font and knows what kind of font message is in
    //and saves it to a Letter pointer
    Letter * font_file = read_font(argv[1]);
    //if read_font returns NULL quit program
    if(font_file == NULL)
    {
        cout << "Unable to read font file." << endl;
        return 2;
    }
    string line;
    cout << "Enter your message:" << endl;
    getline(cin,line);
    //creates banner and saves it to realest_message, type Banner
    Banner realest_message = make_banner(line, font_file);
    //prints the message
    print_banner(realest_message);

    //deallocate memory from read_font()
    delete[] font_file;
}
#endif
