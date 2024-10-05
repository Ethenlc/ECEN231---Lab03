/***********************************************************************
 * Header File:
 *    MOVE 
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a single chess move
 ************************************************************************/

#pragma once

#include <string>
#include "position.h"  // Every move has two Positions as attributes
#include "pieceType.h" // A piece type


class TestMove;
class TestBoard;

/***************************************************
 * MOVE
 * One move across the board
 ***************************************************/
class Move
{
public:
   enum MoveType { MOVE, ENPASSANT, CASTLE_KING, CASTLE_QUEEN, MOVE_ERROR };

   friend TestMove;
   friend TestBoard;

   // constructor
   Move();

   // Equality operator
   bool operator==(const Move& rhs) const
   {
	   return (this->source == rhs.source &&
		   this->dest == rhs.dest &&
		   this->promote == rhs.promote &&
		   this->capture == rhs.capture &&
		   this->moveType == rhs.moveType &&
		   this->isWhite == rhs.isWhite);
   }

   // Less than operator for comparison
   bool operator<(const Move& rhs) const
   {
	   if (this->source != rhs.source)
		   return this->source < rhs.source;
	   if (this->dest != rhs.dest)
		   return this->dest < rhs.dest;
	   // Optionally include other fields like promote, capture, etc.
	   return false; // If all are equal, return false
   }

private:
   // Convert PieceType to char
   char letterFromPieceType(PieceType pt)     const 
   { 
	   switch (pt)
	   {
	   case PAWN:   return 'p';
	   case BISHOP: return 'b';
	   case KNIGHT: return 'n';
	   case ROOK:   return 'r';
	   case QUEEN:  return 'q';
	   case KING:   return 'k';
	   case SPACE:  return ' '; // Empty space or no piece
	   default:		return '?'; // Error case
		}
   }

   // Convert char to PieceType
   PieceType pieceTypeFromLetter(char letter) const 
   {
	   switch (letter)
	   {
	   case 'p': return PAWN;
	   case 'b': return BISHOP;
	   case 'n': return KNIGHT;
	   case 'r': return ROOK;
	   case 'q': return QUEEN;
	   case 'k': return KING;
	   case ' ': return SPACE; // Empty space
	   default:  return SPACE; // Default to SPACE for unrecognized input
	   }
   }



   Position  source;    // where the move originated from
   Position  dest;      // where the move finished
   PieceType promote;   // piece to be promoted to
   PieceType capture;   // did a capture happen this move?
   MoveType  moveType;  // what type of move is this?
   bool      isWhite;   // whose turn is it anyway?
   string    text;      // what is the textual version of the move?
};


