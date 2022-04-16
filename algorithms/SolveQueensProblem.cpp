//use backtracking to solve 8 queens problem
//other uses for backtracking are
//finding min number of colors for a map
//finding way out of maze
//solving sudoku problem
#include <iostream>
#include <string>

using namespace std;
int recursionCount = 0;
int loopCount = 0;

void log(string line){
  //cout << line << endl;
}

bool clearHorizontal(int x, int y, int **board){
  log("entere clear horizontal");
  int x1 = x-1;
  while(x1 >= 0)
  {
    if(board[y][x1] == 1)
      return false;
    x1--;
  }
  x1 = x+1;
  while(x1 < 8){
    
    if(board[y][x1] == 1)
      return false;
    x1++;
  }
  return true;
}

bool clearVertical(int x, int y, int **board){
  log("entered clear vertical");
  int y1 = y-1;
  while(y1 >= 0)
  {
    
    if(board[y1][x] == 1)
      return false;
    y1--;
  }
  y1 = y+1;
  while(y1 < 8){
   
    if(board[y1][x] == 1)
      return false;
     y1++;
  }
  return true;
}

bool clearDiagonalUp(int x, int y, int **board){
  log("entered clear diagonal up");
  int y1 = y-1;
  int x1 = x+1;
  while(y1 > 0 && x1 < 8)
  {
    if(board[y1][x1] == 1)
      return false;
    y1--;
    x1++;
  }
  y1 = y+1;
  x1 = x-1;
  while(y1 < 8 && x1 >= 0){

    if(board[y1][x1] == 1)
      return false;
    y1++;
    x1--;
  }
  return true;
}

bool clearDiagonalDown(int x, int y, int **board){
  log("clear diagonal down");
  int y1 = y-1;
  int x1 = x-1;
  while(y1 >= 0 && x1 >= 0)
  {
    if(board[y1][x1] == 1)
      return false;
    y1--;
    x1--;
  }
  y1 = y+1;
  x1 = x+1;
  while(y1 < 8 && x1 < 8){
    if(board[y1][x1] == 1)
      return false;
    y1++;
    x1++;
  }
  return true;
}

bool isValidMove(int x, int y, int **board){
  log("entered is valid move");
  if(!clearHorizontal(x, y, board))
    return false;
  if(!clearVertical(x,y, board))
    return false;
  if(!clearDiagonalUp(x,y, board))
    return false;
  if(!clearDiagonalDown(x,y,board))
    return false;

  return true;
}

bool isComplete(int **board){
  log("entered is complete");
  int sum = 0;
  for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      sum += board[i][j];
    }
  }

  return sum == 8;
}

bool isSolved(int **board){
  log("isSolved");
  if(isComplete(board)){
    for(int i=0;i<8;i++){
      for(int j=0;j<8;j++){
        if(board[i][j] == 1){
          if(!isValidMove(j,i,board))
            return false;
          loopCount++;
        }
      }
    }
    return true;
  }
  return false;
}

void display(int **board){
  log("entered display");
  for(int y=0;y<8;y++){
    for(int x=0;x<8;x++){
      cout << board[y][x] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

bool solve(int x1, int y1, int **board){
  log("entered solve");
  recursionCount++;
  //int x;
 // cout << "enter y  to continue";
  //cin >> x;
  
  if(isSolved(board))
    return true;

  if(y1 >= 8)
    return false;
  if(y1 == 7 && x1 >= 8)
    return false;
  
  for(int y =y1; y < 8; y++){
    for(int x=x1; x < 8; x++){
 //     if(board[y][x] == 1)
 //       continue;
      loopCount++;
      //do not allow invalid moves down the pipe
      if(!isValidMove(x, y, board))
        continue;
      board[y][x] = 1;
      solve(0, y+1, board);
      
      if(isSolved(board)){
        return true;
      }
      board[y][x] = 0;
    }
  }

  return false;
}



int** initBoard(){
  log("entered init board");
  int** board = new int*[8];
  for(int i=0;i<8;i++){
    board[i] = new int[8];
    for(int j=0;j<8;j++){
      board[i][j] = 0;
    }
  }

  return board;
}


int main() {
  int** board = initBoard();
  board[0][3] = 1;
  recursionCount = 0;
  display(board);
  solve(0,0,board);
  display(board);
  if(isSolved(board)){
    cout  << "Congratulations you solved it!!!!" << endl;
  }
  else{
    cout  << "You failed to solve the queens problem" << endl;
  }

  cout << "Recursion count:  " << recursionCount << endl;
  cout << "Loop count:  " << loopCount << endl;
  
  //did not run with this but may need fixing here
  //or delete it since it's the end of the program
  for(int i=0;i<8;i++)
    delete [] board[i];
  delete [] board;

  return 0;
}
