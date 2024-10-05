/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#pragma once

#include <string>
#include <cstdint>
using std::string;
using std::ostream;
using std::istream;

const int SIZE_SQUARE  = 32;   // number of pixels in a square by default
const int OFFSET_BOARD = 50;   // boarder between the board and the edge of screen

/***********************************************
 * DELTA
 * Movement in a direction (dRow and dCol)
 **********************************************/
struct Delta
{
   int dRow;
   int dCol;
};

const Delta ADD_R = { 1,  0};
const Delta ADD_C = { 0,  1};
const Delta SUB_R = {-1,  0};
const Delta SUB_C = { 0, -1};


class PositionTest;

/***************************************************
 * POSITION
 * The location of a piece on the board
 ***************************************************/
class Position
{
   friend class PositionTest;
public:

   // Position :    The Position class can work with other positions,
   //               Allowing for comparisions, copying, etc.
   Position(const Position& rhs)  { this->colRow = rhs.colRow; }
   Position() : colRow(0x99)      {              }

   // Constructor using the row / column
   // Set colRow using the bit-shift and mask technique
   Position(int c, int r) : colRow(0x99) { colRow = (uint8_t)((c << 4) | (r & 0x0F)); }

   // Constructor using location (0-63)
   // Converts location to row / column
   Position(int location) { setLocation(location); }

   bool isInvalid() const         { return (colRow & 0x88) != 0; } // If top bit is set, it's invalid
   bool isValid()   const         { return (colRow & 0x88) == 0; } // Both top bits must be 0 for valid
   void setValid()                { colRow &= ~0x88; } // Clear the top bits to make valid
   void setInvalid()              { colRow = 0xFF; } // Set to 0xFF to make invalid

   // Comparison operators
   bool operator <  (const Position & rhs) const { return colRow < rhs.colRow; }
   bool operator == (const Position& rhs) const { return colRow == rhs.colRow; }
   bool operator != (const Position & rhs) const { return !(*this == rhs); }
   const Position& operator =  (const Position& rhs) { this->colRow = rhs.colRow; return *this; }
   
   // Location : The Position class can work with locations, which
   //            are 0...63 where we start in row 0, then row 1, etc.
   int getLocation() const               { 
       if (isInvalid())
           return -1;
       int row = getRow();
       int col = getCol();
       return row + (col * 8); } // Convert the row and column to a single location (0-63)
   void setLocation(int location)        { // Convert location (0-63) to row and column
       int col = location % 8;
       int row = location / 8;
       colRow = (uint8_t)((col << 4) | (row & 0x0F));
   }

   
   // Row/Col : The position class can work with row/column,
   //           which are 0..7 and 0...7
   virtual int getCol() const { 
       if (isInvalid())
           return -1;
       return (colRow & 0xF0) >> 4; } // Extract upper nibble (column) and shift right
   virtual int getRow() const { 
       if (isInvalid())
           return -1;
       return (colRow & 0x0F); } // Extract the lower nibble (row)
   void setRow(int r)                     { colRow = (uint8_t)((colRow & 0xF0) | (r & 0x0F)); } // Clear the row bits and set the new row
   void setCol(int c)                     { colRow = (uint8_t)((colRow & 0x0F) | (c << 4)); } // Clear the column bits and set the new column
   void set(int c, int r)                 { colRow = (uint8_t)((c << 4) | (r & 0x0F)); } // Set both row and column

   // Text:    The Position class can work with textual coordinates,
   //          such as "d4"
   
   Position(const char* s) { *this = s; } // Position using Text ("xx")

   // Convert Text to Position ("xx" -> Row/Column)
   const Position& operator=(const char* rhs)
   {
       if (rhs && strlen(rhs) == 2)
       {
           char col = rhs[0];
           char row = rhs[1];

           // Convert 'a'-'h' to 0-7 (columns) and '1'-'8' to 0-7 (rows)
           int colValue = col - 'a';
           int rowValue = row - '1';

           // Only assign if column and row are valid
           if (colValue >= 0 && colValue <= 7 && rowValue >= 0 && rowValue <= 7)
               colRow = (colValue << 4) | (rowValue & 0x0F);
           else
               colRow = 0xFF; // Invalid value
       }
       else
       {
           colRow = 0xFF; // Invalid value
       }

       return *this;
   }

   const Position& operator=(const string& rhs)
   {
       return *this = rhs.c_str();
   }
   
   // Pixels:    The Position class can work with screen coordinates,
   //            a.k.a. Pixels, these are X and Y coordinates. Note that
   //            we need to scale them according to the size of the board.
   int getX()   const { return 99; }
   int getY()   const { return 99; }
   void setXY(double x, double y) { }
   double getSquareWidth()  const { return 99; }
   double getSquareHeight() const { return 99; }
   void setSquareWidth (double width )  {  }
   void setSquareHeight(double height)  {  }

   // Delta:    The Position class can work with deltas, which are
   //           offsets from a given location. This helps pieces move
   //           on the chess board.
   Position(const Position & rhs, const Delta & delta) : colRow(-1) {  }
   void adjustRow(int dRow)   { 
       int newRow = getRow() + dRow;
       if (newRow >= 0 && newRow <= 7) // Check the new row is valid
           setRow(newRow);
       else
           setInvalid();
   }
   void adjustCol(int dCol)   { 
       int newCol = getCol() + dCol;
       if (newCol >= 0 && newCol <= 7) // Check the new column is valid
           setCol(newCol);
       else
           setInvalid();
   }
   const Position & operator += (const Delta & rhs) { 
       adjustRow(rhs.dRow);
       adjustCol(rhs.dCol);
       return *this;
   }
   Position operator + (const Delta & rhs) const { 
       Position result = *this;
       result.adjustRow(rhs.dRow);
       result.adjustCol(rhs.dCol);
       return result;
   }

private:
    void set(uint8_t colRowNew) { colRow = colRowNew; }
   
   uint8_t colRow;
   static double squareWidth;
   static double squareHeight;
};


ostream & operator << (ostream & out, const Position & pos);
istream & operator >> (istream & in,  Position & pos);
      
