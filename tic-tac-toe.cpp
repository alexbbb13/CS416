/***********************************************************************
* Program:
*    Lesson 08, Tic-Tac-Toe
* Summary: 
*    This program reads, displays, and writes a Tic-Tac-Toe board
************************************************************************/

#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;
#define SYMBOL_X 'X'
#define SYMBOL_O 'O'
#define SYMBOL_EMPTY '.'
#define BOARD_SIZE 3

bool read(         char board[][BOARD_SIZE][BOARD_SIZE], const char* fileName);
bool write(  const char board[][BOARD_SIZE][BOARD_SIZE], const char* fileName);
void display(const char board[][BOARD_SIZE][BOARD_SIZE]);
bool didWin( const char board[][BOARD_SIZE][BOARD_SIZE], char turn);

/**********************************************************************
 * Keeps the data and calles the read/display/write functions
 ***********************************************************************/
int main()
{
   char board[BOARD_SIZE][BOARD_SIZE][BOARD_SIZE];

   // read the board
   char fileName[256];
   cout << "Enter source filename: ";
   cin  >> fileName;
   if (!read(board, fileName))
   {
      cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
      return 1;
   }

   // display the board
   display(board);

   // write the board to a file
   cout << "Enter destination filename: ";
   cin  >> fileName;
   if (!write(board, fileName))
   {
      cout << "ERROR: Unable to open file \"" << fileName << "\"\n";
      return 1;
   }

   return 0;
}

/**************************************************************
 * READ
 * Read the board from the specified filename
 *************************************************************/
bool read(char board[][BOARD_SIZE][BOARD_SIZE], const char* fileName)
{
   assert(*fileName);

   // open the file
   ifstream fin(fileName);
   if (fin.fail())
      return false;

   // read 9 symbols, hopefully they are . X O
   for (int z = 0; z < BOARD_SIZE; z++)
      for (int r = 0; r < BOARD_SIZE; r++)
         for (int c = 0; c < BOARD_SIZE; c++)
         {
            fin >> board[r][c][z];
            assert(!fin.fail());
            assert(board[r][c][z] == SYMBOL_X ||
                   board[r][c][z] == SYMBOL_O ||
                   board[r][c][z] == SYMBOL_EMPTY);
         }

   // close the file
   fin.close();
   return true;
}

/**********************************************************
 * WRITE
 * Write to fileName the board data
 *********************************************************/
bool write(const char board[][BOARD_SIZE][BOARD_SIZE], const char* fileName)
{
   assert(fileName[0] != '\0');

   // open the file
   ofstream fout(fileName);
   if (fout.fail())
      return false;

   // write my 9 symbols
   for (int z = 0; z < BOARD_SIZE; z++)
      for (int r = 0; r < BOARD_SIZE; r++)
         for (int c = 0; c < BOARD_SIZE; c++)
            fout << board[r][c][z] << (c == (BOARD_SIZE-1) ? '\n' : ' ');

   // close it!
   fout.close();
   cout << "File written\n";
   return true;
}

/*******************************************************
 * DISPLAY
 * Display the contents the the screen
 *****************************************************/
void display(const char board[][BOARD_SIZE][BOARD_SIZE])
{
   // loop through each row
   for (int z = 0; z < BOARD_SIZE; z++)
   {
   cout << "\nLevel " << z + 1 << endl;   
      for (int r = 0; r < BOARD_SIZE; r++)
      {
         // only the first row is not preceeded with the --+-- magic
         if (r != 0)
         {
            for(int i = 0; i < BOARD_SIZE -1; i++) {
               cout << "---+";  //starting and intermediate   
            }
            cout << "---\n";  //last line
            //cout << "---+---+---\n";
         }   
         // now, on each row, do the column stuff
         for (int c = 0; c < BOARD_SIZE; c++)
         {
            // display a space for the dot
            if (board[r][c][z] == SYMBOL_EMPTY)
               cout << "   ";
            else
               cout << " " << board[r][c][z] << " ";

            // end with a | or a newline
            cout << (c == (BOARD_SIZE - 1) ? '\n' : '|');
         }
      }
   }   

   // display who won
   if (didWin(board, SYMBOL_X))
      cout << "X won!\n";
   if (didWin(board, SYMBOL_O))
      cout << "O won!\n";
   
   return;
}

/********************************************
 * DID WIN
 * Did a given player (determined by the "turn"
 * variable) win the game?
 *******************************************/
bool didWin(const char board[][BOARD_SIZE][BOARD_SIZE], char turn)
{
   //checking x, y planes for each of the z planes
   for (int z = 0; z < BOARD_SIZE; z++)
   {
      //Checking columns
      for (int r = 0; r < BOARD_SIZE; r++)
      {
         bool hadWon = true;
         for (int c = 0; c < BOARD_SIZE; c++)
         {
             if (board[r][c][z] != turn) hadWon = false;
         }
         //check if this row had or had not won;
         //Hooray, we had found the winning column!
         if(hadWon==true) return true;
         // continue
      }
      //Same for rows

      for (int c = 0; c < BOARD_SIZE; c++)
      {
         bool hadWon = true;
         for (int r = 0; r < BOARD_SIZE; r++)
         {
             if (board[r][c][z] != turn) hadWon = false;
         }
         //check if this column had or had not won;
         //Hooray, we had found the winning row!
         if(hadWon==true) return true;
         // continue
      }

      bool hadWon = true;
      //Check diagonal 0,0 - 1,1 - 2-2 etc
      for (int d = 0; d < BOARD_SIZE; d++)
      {
         if (board[d][d][z] != turn) hadWon = false;
      }
      if(hadWon==true) return true;
      hadWon = true;
      //Check diagonal 0,0 - 1,1 - 2-2 etc
      for (int d = 0; d < BOARD_SIZE; d++)
      {
         if (board[d][BOARD_SIZE - d - 1][z] != turn) hadWon = false;
      }
      if(hadWon==true) return true;
   }
   //checking z-plane in the z-column 2d plane
   for (int r = 0; r < BOARD_SIZE; r++)
         for (int c = 0; c < BOARD_SIZE; c++)
         {
             bool hadWon = true;
             for (int z = 0; z < BOARD_SIZE; z++)
             {
                 if (board[r][c][z] != turn) hadWon = false; 
             }
             if(hadWon==true) return true;
         }
   //checking z-plane in the z-row 2d plane
   for (int c = 0; c < BOARD_SIZE; c++)
         for (int r = 0; r < BOARD_SIZE; r++)
         {
             bool hadWon = true;
             for (int z = 0; z < BOARD_SIZE; z++)
             {
                 if (board[r][c][z] != turn) hadWon = false; 
             }
             if(hadWon==true) return true;
         }     
   //checking diagonals on the z-plane
   // a) column is constant  
   for (int c = 0; c < BOARD_SIZE; c++)
   {  
      bool hadWon = true;
      bool hadWonReverse = true; 
      for (int d = 0; d < BOARD_SIZE; d++)
      {
         if (board[d][c][d] != turn) hadWon = false;
         if (board[d][c][BOARD_SIZE - d - 1] != turn) hadWonReverse = false;
      }
      if(hadWon==true || hadWonReverse==true) return true;
   }
   // b) row is constant  
   for (int r = 0; r < BOARD_SIZE; r++)
   {  
      bool hadWon = true;
      bool hadWonReverse = true; 
      for (int d = 0; d < BOARD_SIZE; d++)
      {
         if (board[r][d][d] != turn) hadWon = false;
         if (board[r][d][BOARD_SIZE - d -1] != turn) hadWonReverse = false;
      }
      if(hadWon==true || hadWonReverse==true) return true;
   }   
   return false;
}