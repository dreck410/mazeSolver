#include <array>
#include <vector>
#include <stack>
#include <queue>
#include <iomanip>
#include <iostream>
#include <stdlib.h>




template <unsigned int N> 
using grid = std::array<std::array<char, N>, N>;

class point;

class point
{

	public:
		unsigned int y;
		unsigned int x;

		point (int newY, int newX){
			y = newY;
			x = newX;
			
		}

		int gx(){return x;}
		int gy(){return y;}
};//point

char getRightChar(int input){
	if (input == 0) {
		return ' ';
	}else{
		if(input == 1){
			return '|';
		} else{
			if (input == 2){
				return 'E';
			}else{
				if(input == -1){
					return 'X';
				}
				return ' ';
			}
		}
	}	
}//getRigthChar


//pretty print
template <typename Grid>
void print(std::ostream &os, Grid &theGrid, unsigned int H, unsigned int W) {
  unsigned int j,k;

  for (j=0; j < H; ++j) {
        os << '\n';
        os << getRightChar(theGrid[j][0]);
    for (k=1; k < W; ++k) {
        os << getRightChar(theGrid[j][k]);

    }//for
  }//for
	std::cout << "\n\n";
  os.flush();
}//print


//ugly print
template <typename Grid>
void uprint(std::ostream &os, Grid &theGrid, unsigned int H, unsigned int W) {
  unsigned int j,k;

  for (j=0; j < H; ++j) {
        os << '\n';
        os << theGrid[j][0] << ' ';
    for (k=1; k < W; ++k) {
        os << theGrid[j][k] << ' ';

    }//for
  }//for
	std::cout << "\n\n";
  os.flush();
}//print


template <typename Grid>
void checkDirection(int dirV, int dirH, Grid &theGrid,
 point curPoint, std::queue<point> &newQueue,int d)
{


	point nPoint(curPoint.gy() + dirV, curPoint.gx() + dirH);

	if(theGrid[nPoint.gy()][nPoint.gx()] == 0)
	{
		//mark it as visited
		theGrid[nPoint.y][nPoint.x] = d;
		
		newQueue.push(nPoint);

	}
	
}

//checks all of the squares around the cell for life
template <typename Grid>
void check(Grid &theGrid, unsigned int H, unsigned int W,
point currentP, std::queue<point> &newQueue, int count)
{ 
	int checkUp    = -1;
	int checkDown  =  1;
	int checkLeft  = -1;
	int checkRight =  1;
	
	//bounds checking

	if (currentP.gy() > 0){
		checkDirection(-1, 0, theGrid, currentP, newQueue, count);
	}
	if (currentP.gy() < H - 1){	
		checkDirection(1 , 0, theGrid, currentP, newQueue, count);
	}
	if (currentP.gx() < W - 1){
		checkDirection(0 , 1, theGrid, currentP, newQueue, count);
	}
	if (currentP.gx() > 0){	
		checkDirection(0 ,-1, theGrid, currentP, newQueue, count);
	}


}//checkDirection


template <typename Grid>
std::queue<point> process(Grid &theGrid, unsigned int H, unsigned int W,
 std::queue<point> &theQueue, int count)
{
	std::queue<point> newQueue;
	while(!theQueue.empty() && 
		(	theQueue.front().gy() != H - 1 ||
    		theQueue.front().gx() != W - 1 ||
    		theQueue.front().gx() != 0 || 
    		theQueue.front().gy() != 0)){

		check(theGrid, H, W, theQueue, newQueue, count);
		//point curLoc = theQueue.front();
		
		theQueue.pop();

	}
	//print(std::cout, theGrid, H, W);
	return newQueue;

}



template <typename Grid>
point checkPrior(Grid &theGrid, point curLoc, int spot, unsigned int H, unsigned int W)
{
	point output = curLoc;
    

	//check up

	if (curLoc.gy() > 0 && spot - 1 == theGrid[curLoc.gy() -1][curLoc.gx()]){

		return point(curLoc.gy() -1, curLoc.gx());
	}
	
	//check down
	if (curLoc.gy() < H - 1 && spot - 1 == theGrid[curLoc.gy() + 1][curLoc.gx()]){
		return point(curLoc.gy()  + 1, curLoc.gx());		
	}

	//checks left
	if (curLoc.gx() > 0 && spot - 1 == theGrid[curLoc.gy()][curLoc.gx() - 1]){
		return point(curLoc.gy(), curLoc.gx() - 1);
	}

	//checkz right
	if (curLoc.gx() < W && spot - 1 == theGrid[curLoc.gy()][curLoc.gx() + 1]){
		return point(curLoc.gy(), curLoc.gx() + 1);
	}

	return output;
}




template <typename Grid>
std::stack<point> getPath(Grid &theGrid, point ex, unsigned int H, unsigned int W)
{
	point curLoc = ex;
	int spot = theGrid[curLoc.gy()][curLoc.gx()];
	std::stack<point> returnStack;
	returnStack.push(curLoc);


	while (spot != 2){

		curLoc = checkPrior(theGrid, curLoc, spot, H, W);

		--spot;
		returnStack.push(curLoc);
	}

	return returnStack;


}


template <typename Grid>
void format(Grid &theGrid, point curP){
	theGrid[curP.gy()][curP.gx()] = -1;
}


//yay actual logic
template <typename Grid>
void solve(Grid &theGrid, unsigned int H, unsigned int W, unsigned int Ey, unsigned int Ex) 
{

	//while not an edge
	std::queue<point> theQueue;
//	Grid originalGrid = theGrid;
//	std::cout << "we are here\n";
//	uprint(std::cout, theGrid, H, W);
//	uprint(std::cout, originalGrid, H, W);
//	std::cout << "now we are here\n";

	point start(Ey, Ex);
	int count = 3;
	theQueue.push(start);
	bool going = true;
	point ex(-1,-1);


    while (going && !theQueue.empty())
    		{	

    			//theQueue = process(theGrid, H, W, theQueue, count);
    			std::queue<point> newQueue;
				while(!theQueue.empty())
				{
					check(theGrid, H, W, theQueue.front(), newQueue, count);

					//point curLoc = theQueue.front();

					if (theQueue.front().gy() == H - 1 || theQueue.front().gx() == W - 1 || 
			    		theQueue.front().gx() == 0	   || theQueue.front().gy() == 0)
					{
						//std::cout << "EDGE" << '\n';

						if (theGrid[theQueue.front().y][theQueue.front().x] != 2)
						{
							//finish 
							std::cout << "Finished"<< "\n";
							going = false;
							ex = theQueue.front();
							//std::cout << "Exit Location: " << ex.gx() << ", " << ex.gy() << '\n';
							//uprint(std::cout, theGrid, H, W);

							break;
							
						}//if
					}//if
					theQueue.pop();

				}//while

				theQueue = newQueue;

    			++count;
    		}//while 

    	int numOfSteps = 0;
    	if ( -1 != ex.gx() && -1 != ex.gy()){
    		//found an exit
			std::cout << "Exit: " << ex.gx() << ", " << ex.gy() << '\n';

    		std::cout << "\nExit Found\n\n";

    		std::cout << "Path through maze\n";

			std::stack<point>path = getPath(theGrid, ex, H, W);
    		//print(std::cout, theGrid, H, W);
    		numOfSteps = path.size();
    		for (int i = 0; i != path.size(); path.pop()){
    			std::cout << "X: " << path.top().gx() << " | Y: " << path.top().gy() << '\n';
    			//format(originalGrid,  path.top());
    			format(theGrid,  path.top());
    		}
			print(std::cout, theGrid, H, W);

    		std::cout << "Number of Steps: " << numOfSteps << '\n';

    	}else{
    		std::cout << "No Exit\n";
    	}
//std::cout << "Width :" << W << "  Height: " << H;
//print(std::cout, originalGrid, H, W);




}//solve

