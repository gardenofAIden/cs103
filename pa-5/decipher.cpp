#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

	/************* You complete *************/
  try
  {
    int base = 0;
    string key = "";
    string modulus = "";
    string result = "";
    ifstream ifile(argv[1]);
    ifile >> base >> key >> modulus;
    string result1 = "";
    BigInt key1(key,base);
    BigInt mod1(modulus, base);

    while(!ifile.fail())
    {
      ifile >> result;
      BigInt secret_code(result, base);
      secret_code.modulusExp(key1, mod1);
      result1 += (char)secret_code.to_int();
    }
    result1.pop_back();
    cout << result1 << endl;
  }
  catch(exception& e)
  {
    cout << e.what() << endl;
    return -1;
  }

	return 0;
}
