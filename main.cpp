#include <sstream>
#include <fstream>
#include <iostream>
#include <system_error>
#include <string>
#include <vector>
#include <algorithm>
#include "data_container.h"
#include "methods.h"

using namespace std;
int main(){
  ifstream infile;
  ios_base::iostate exceptionMask = infile.exceptions() | ios::failbit;
  infile.exceptions(exceptionMask);
  try{
    infile.open("input.txt");
  }
  catch (std::system_error &e){
    cerr << "Exception opening/reading/closing file " << e.what() << endl;
    exit(0);
  }

  Collection c = read_input(infile);
  infile.close();

  rank_collection(c);

  return 0;
}
  
