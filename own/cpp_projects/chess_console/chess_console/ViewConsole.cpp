#include "ViewConsole.h"
#include <Windows.h>

int ViewConsole::getColorNumber(Piece* piece)
{
	if (piece == nullptr || piece->color() == Color::BLACK)
		return 0;
	else
		return 15;
}


void ViewConsole::printBoard(Board board)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int b;

	b = 4;

	std::cout << "  ABCDEFGH\n";

	for (int r = 0; r < board.height(); r++)
	{
		std::cout << r + 1 << " ";

		for (int c = 0; c < board.width(); c++) {
			SetConsoleTextAttribute(hConsole,
				b * 16 + getColorNumber(board.fields()[c][r].piece()));
			std::cout << board.fields()[c][r].toChar();
			b == 4 ? b = 8 : b = 4;
		}
		
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << " " << r + 1 << "\n";

		b == 4 ? b = 8 : b = 4;
	}

	std::cout << "  ABCDEFGH\n";
}

Move ViewConsole::inputToMove()
{
	std::string line;
	std::getline(std::cin, line);

	if (strlen(line.c_str()) != 4)
		std::getline(std::cin, line);

	line[0] -= 49;
	line[1] -= 1;
	line[2] -= 49;
	line[3] -= 1;

	return Move(Coordinate(std::stoi(line.substr(1, 1)), std::stoi(line.substr(0, 1))),
				Coordinate(std::stoi(line.substr(3, 1)), std::stoi(line.substr(2, 1))));
}