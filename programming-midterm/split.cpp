#include <iostream>

using namespace std;

int count_delims(char delim, char* str)
{
    //counts number of delimiters
    int counter = 0;
    //pointer to c string
    char * current = str;
    //while deferenced pointer current not equal to null character(loop through c string)
    while(*current != '\0')
    {
        //if equal to delimiter add one to counter
        if(*current == delim)
        {
            counter ++;
        }
        //go to next character in c string
        current++;
    }
    //return number of delimiters counted
    return counter;
}

char** split(char delim, char* str, int *size)
{
    //Use count_delims() to count the number of 
    //delimiters found in the input string.
    //add 1 since number of substrings is always one more than number of delimiters
    *size = count_delims(delim, str) + 1;
    //allocates an array to hold char*'s of size number
    char** w = new char*[*size];
    w[0] = str;
    int next = 1;
    //pointer to c string
    char * current = str;
    //loop through input string
    while(*current != '\0')
    {
        //if is delimiter
        if(*current == delim)
        {
            //set current to null character
            *current = '\0';
            //set next index in w to whatever is next in c string input
            w[next] = current + 1;
            //increment next
            next++;
        }
        //increment
        current++;
    }
    //return w
    return w;
}

#ifndef TEST
int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        cout << "Please enter a delimter and a string as arguments." << endl;
        return 1;
    }
    //do not make any changes to main! If changes to main are needed to make your code work, you have a bug elsewhere!
    int n;
    char** w = split(argv[1][0], argv[2], &n);
    for(int i=0;i<n;i++)
    {
        cout << i << ":" << w[i] << endl;
    }
    delete[] w;
}
#endif

