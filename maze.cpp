#include <array>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "maze.h"


using namespace std;





//dumb method that i had to write to get the size
std::vector<int> getDimensions(string file)
{
  std::vector<int> dims;
  int x = 0;
  int y = 0;
  int rows = 0;
  int cols = 0;
  ifstream myfile(file);
  char c;

  while (myfile.good() && c != '\n'){
    c = myfile.get();
    if(c != '\n' && c > 0){
      ++x;
    }
  }//get cols
  cols = x;
  ++y;

  std::string line;

  while (myfile.good())          // loop while extraction from file is possible
    {
      std::getline(myfile,line);       // get character from file
      ++y;

    }//while
  rows = y;

  dims.push_back(cols);
  dims.push_back(rows);
  myfile.close();
  return dims;

}



int main(int argc, char *argv[] )
{

      std::vector<int> dims = getDimensions(argv[1]);
      int W = dims[0];
      int H = dims[1];
      cout << "Width: " << W << '\n';

      cout << "Height: " << H << '\n';


      std::vector<std::vector<int>> 
        vSquare(H, std::vector<int>(W, ' '));

      ifstream myfile;
      myfile.open (argv[1]);
      


      //populate the maze

      int x = 0;
      int y = 0;
      int rows = 0;
      int Ex = 0;
      int Ey = 0;
      char c;

      if(W == 1 && H == 1){
        cout<< "Just an entrance.\n";
        return 0;
      }


      while (myfile.good())          // loop while extraction from file is possible
      {
        c = myfile.get();       // get character from file



        if (myfile.good() && c != '\n')
        {
        //std::cout << c;
        //std::cout.flush();
          if (c == 'E') 
          {
            Ex = x; 
            Ey = y;
            vSquare[y][x] = 2;
          } //if E
          else {
            vSquare[y][x] = c - 48;

          }//anything else
          ++x;

        }//if file is open
        else
          {
            rows = x;
            x = 0;
            ++y;
          }//else
      }//while
      

    	myfile.close();

      std::cout << "\nMaze:";
      print(std::cout, vSquare, H, W);

      solve(vSquare, H, W, Ey, Ex);
  	return 0;

 //std::vector<std::vector<unsigned int>> 
 //	vMaze(N, std::vector<unsigned int>(N, ' '));


}//main

