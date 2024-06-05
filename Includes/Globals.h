#include <stdio.h>
#include <cstdint>

typedef uint64_t Bitboard;

// Enums

enum Pieces { None, Pawn, Knight, Bishop, Rook, Queen, King};
//	  0		1	  2		  3		  4		5	   6

enum Colors { White = 0, Black = 8};