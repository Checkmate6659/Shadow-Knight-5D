#include "board.h"
#include "debug.h"

//https://github.com/adri326/5dchess-tools/tree/v2

int main()
{
	Position source;
	Position target;
	setPosition(source, 6, 0, 1, 0);
	setPosition(target, 5, 2, 1, 0);

	Move move(source, target); //this is the move Nf3 (or should i say (0T1)g1(0T1)f3?)
	std::cout << move << std::endl;

	Board board;
	//fen 4k3/8/8/8/8/8/8/3QK3 w - - in normal chess
	board.t = 1;
	board.occ = 0x1800000000000010;
	board.white = 0x1800000000000000;
	board.black = 0x10;
	board.kings = 0x1000000000000010;
	board.queens = 0x800000000000000;

	std::cout << board << std::endl;

	return 0;
}
