/***********************************************************************
 * Source File:
 *    MOVE 
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#include "move.h"
#include "pieceType.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

/***************************************************
 * MOVE : DEFAULT CONSTRUCTOR
 ***************************************************/
Move::Move()
{
	source.setInvalid();
	dest.setInvalid();
	promote = SPACE;		// Default piece type is SPACE
	capture = SPACE;		// Default capture is no capture (SPACE)
	moveType = MOVE;		// Default move type
	isWhite = true;			// Default isWhite to true
}



