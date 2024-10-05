/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    Ethen Campbell & Joseph Gyman
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#pragma once

#include <string>
#include <cstdint>
#include <iostream> // Move iostream include here for ostream and istream
using std::string;
using std::ostream;
using std::istream;

const int SIZE_SQUARE = 32;   // number of pixels in a square by default
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

const Delta ADD_R = { 1,  0 };
const Delta ADD_C = { 0,  1 };
const Delta SUB_R = { -1,  0 };
const Delta SUB_C = { 0, -1 };

class PositionTest;

/***************************************************
 * POSITION
 * The location of a piece on the board
 ***************************************************/
class Position
{
    friend class PositionTest;
public:
    Position() : colRow(0x99) {}
    Position(int c, int r) : colRow((uint8_t)((c << 4) | (r & 0x0F))) {}
    Position(int location) { setLocation(location); }
    Position(const Position& rhs) { this->colRow = rhs.colRow; }
    Position(const char* s) { *this = s; }

    bool isInvalid() const { return (colRow & 0x88) != 0; }
    bool isValid()   const { return (colRow & 0x88) == 0; }
    void setValid() { colRow &= ~0x88; }
    void setInvalid() { colRow = 0xFF; }

    bool operator <  (const Position& rhs) const { return colRow < rhs.colRow; }
    bool operator == (const Position& rhs) const { return colRow == rhs.colRow; }
    bool operator != (const Position& rhs) const { return !(*this == rhs); }
    const Position& operator = (const Position& rhs) { this->colRow = rhs.colRow; return *this; }
    const Position& operator = (const char* rhs);
    const Position& operator = (const string& rhs) { return *this = rhs.c_str(); }

    int getLocation() const;
    void setLocation(int location);

    virtual int getCol() const;
    virtual int getRow() const;
    void setCol(int c);
    void setRow(int r);
    void set(int c, int r);

    int getX()   const;
    int getY()   const;
    void setXY(double x, double y);

    Position(const Position& rhs, const Delta& delta) : colRow(-1) { }
    void adjustRow(int dRow);
    void adjustCol(int dCol);

    const Position& operator += (const Delta& rhs);
    Position operator + (const Delta& rhs) const;

private:
    uint8_t colRow;
    static double squareWidth;
    static double squareHeight;

    void set(uint8_t colRowNew) { colRow = colRowNew; }
};

// Overload stream operators
ostream& operator << (ostream& out, const Position& pos);
istream& operator >> (istream& in, Position& pos);

