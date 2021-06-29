#include "board.h"


Position setPosition(Position& p, uint8_t x, uint8_t y, uint16_t t, int16_t l)
{
	p.x = x;
	p.y = y;
	p.t = t;
	p.l = l;
	return p;
}


//Board class (stores one board)
//Default constructor
Board::Board() : flags(0), t(0), l(0), occ(0), white(0), black(0), kings(0), queens(0), rooks(0), bishops(0), knights(0), pawns(0) {}

//Copy constructor
Board::Board(const Board &board) : flags(board.flags), t(board.t), l(board.l), occ(board.occ), white(board.white), black(board.black), kings(board.kings), queens(board.queens), rooks(board.rooks), bishops(board.bishops), knights(board.knights), pawns(board.pawns) {}

//Timeline class (stores one timeline of the entire gamestate) TODO

//Game class (stores entire gamestate) TODO


//Move class (just two 4d vectors)
Move::Move(Position source, Position target) : m_source(source), m_target(target)
{
}
