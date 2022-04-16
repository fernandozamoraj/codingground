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
int badPaths = 0;
int BOARD_WIDTH = 10;

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
  while(x1 < BOARD_WIDTH){
    
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
  while(y1 < BOARD_WIDTH){
   
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
  while(y1 > 0 && x1 < BOARD_WIDTH)
  {
    if(board[y1][x1] == 1)
      return false;
    y1--;
    x1++;
  }
  y1 = y+1;
  x1 = x-1;
  while(y1 < BOARD_WIDTH && x1 >= 0){

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
  while(y1 < BOARD_WIDTH && x1 < BOARD_WIDTH){
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
  for(int i=0;i<BOARD_WIDTH;i++){
    for(int j=0;j<BOARD_WIDTH;j++){
      sum += board[i][j];
    }
  }

  return sum == BOARD_WIDTH;
}

bool isSolved(int **board){
  log("isSolved");
  if(isComplete(board)){
    for(int i=0;i<BOARD_WIDTH;i++){
      for(int j=0;j<BOARD_WIDTH;j++){
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
  for(int y=0;y<BOARD_WIDTH;y++){
    for(int x=0;x<BOARD_WIDTH;x++){
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

  if(y1 >= BOARD_WIDTH)
    return false;
  if(y1 == BOARD_WIDTH-1 && x1 >= BOARD_WIDTH)
    return false;
  
  for(int y =y1; y < BOARD_WIDTH; y++){
    for(int x=x1; x <BOARD_WIDTH; x++){
 //     if(board[y][x] == 1)
 //       continue;
      loopCount++;
      if(!isValidMove(x, y, board))
        continue;
      board[y][x] = 1;
      solve(0, y+1, board);
      
      if(isSolved(board)){
        return true;
      }
      badPaths++;
      board[y][x] = 0;
    }
  }

  return false;
}



int** initBoard(){
  log("entered init board");
  int** board = new int*[BOARD_WIDTH];
  for(int i=0;i<BOARD_WIDTH;i++){
    board[i] = new int[BOARD_WIDTH];
    for(int j=0;j<BOARD_WIDTH;j++){
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
  cout << "Loop count:       " << loopCount << endl;
  cout << "bad paths:        " << badPaths << endl;
  

  return 0;
}
