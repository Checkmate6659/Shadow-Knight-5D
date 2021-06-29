#ifndef __INC_BOARD__
#define __INC_BOARD__

#include <cinttypes>
#include <vector> //variable length arrays (game and timeline), maybe partial rewrite to reduce time lost due to reallocation (the standard vector class does that a lot)
#include <intrin.h> //intrinsics will be used in bitboard spatial move generation
#include <iostream> //display game/board/moves

//#pragma intrinsic(_BitScanForward64)
//#pragma intrinsic(_BitScanReverse64)

//Board flags
//KQkqEFFF......TA (castle rights, then en passant flag, then en passant file, then 6 unused bits, then turn, then activity bit)
#define ACTIVE_BF 0x0001
#define TURN_BF 0x0002
#define EP_FILE_BF 0x0700
#define EP_BF 0x0800
#define CASTLE_BF 0xF000

typedef uint64_t U64;

typedef struct Position Position;
struct Position
{
	uint8_t x, y;
	uint16_t t;
	int16_t l;
};

Position setPosition(Position& p, uint8_t x, uint8_t y, uint16_t t, int16_t l);


class Move
{
public:
	Move(Position source, Position target);

	Position m_source, m_target;

	//display move to console in Alexbay's raw notation and in probably one of the ugliest ways possible
	//https://github.com/adri326/5dchess-notation/pull/7
	friend std::ostream& operator<<(std::ostream& output, Move& move) {
		output << '(';
		output << move.m_source.l;
		output << 'T';
		output << move.m_source.t;
		output << ')';
		output << char('a' + move.m_source.x);
		output << char('1' + move.m_source.y);
		if (move.m_source.t != move.m_target.t)
		{
			output << ">>";
			output << '(';
			output << move.m_target.l;
			output << 'T';
			output << move.m_target.t;
			output << ')';
		}
		else if (move.m_source.l != move.m_target.l)
		{
			output << '>';
			output << '(';
			output << move.m_target.l;
			output << 'T';
			output << move.m_target.t;
			output << ')';
		}
		output << char('a' + move.m_target.x);
		output << char('1' + move.m_target.y);
		return output;
	}

};

class Game
{
	//gamestate: vector of timelines
	//we still need an efficient way of making the vector "grow" both ways without losing efficiency for jumping move generation
};

class Timeline
{
	//timeline: vector of boards
};

class Board
{
public:
	uint16_t flags; //KQkqEFFF......TA (castle rights, then en passant flag, then en passant file, then 6 unused bits, then turn, then activity bit)
	U64 occ, white, black, kings, queens, rooks, bishops, knights, pawns;
	uint16_t t, l;
	//Game& parent; //Use this for non-spatial (branching and jumping) move generation

	Board(); //default constructor
	Board(const Board& board); //copy constructor

	//display board's 2D fen, along with non-spatial coordinates
	//[FEN:L:T:turn]
	friend std::ostream& operator<<(std::ostream& output, Board& board) {
		output << "[";
		
		uint16_t empty_squares = 0; //empty squares
		for (U64 offset = 1; offset; offset <<= 1)
		{
			if (board.occ & offset)
			{
				if (empty_squares) output << empty_squares;
				empty_squares = 0;

				char symbol = 'B';
				if (board.black & offset) symbol += 'b' - 'B';
				if (board.kings & offset) symbol += 'K' - 'B';
				if (board.queens & offset) symbol += 'Q' - 'B';
				if (board.rooks & offset) symbol += 'R' - 'B';
				if (board.knights & offset) symbol += 'N' - 'B';
				if (board.pawns & offset) symbol += 'P' - 'B';

				output << symbol;
			}
			else
			{
				empty_squares += 1;
			}

			if (offset & 0x8080808080808080) //new row
			{
				if (empty_squares) output << empty_squares;
				if (offset & 0x80808080808080)
				{
					output << "/"; //output new row slash
					empty_squares = 0;
				}
			}
		}
		
		output << ":";
		output << board.l;
		output << ":";
		output << board.t;
		output << ":";
		output << (board.flags & TURN_BF) ? "b" : "w";
		output << "]";
		return output;
	}
};

#endif
