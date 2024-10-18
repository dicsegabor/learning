#include "graphics.h"

using std::cout;
using std::endl;

void print_Figure(coordinate present_place, int color, Field board[8][8]) {

	if (!board[present_place.y][present_place.x].is_Empty()) {

		if(board[present_place.y][present_place.x].get_Content() == light)
			set_Console_color(white, color);

		else
			set_Console_color(black, color);

		cout << 'P';
	}

	else
		cout << ' ';
}

void print_left_edge(int ch, coordinate present_place) {

	set_Console_color(white, dark_green);

	if (present_place.x == 0 && ch == 1)
		cout << present_place.y + 1;

	else if (present_place.x == 0)
		cout << ' ';
}

void print_right_edge(int ch, coordinate present_place) {

	set_Console_color(white, dark_green);

	if (present_place.x == 8 && ch == 1)
		cout << present_place.y + 1;

	else if (present_place.x == 8)
		cout << ' ';
}

void print_Header() {

	set_Console_color(white, dark_green);
	cout << "   A    B    C    D    E    F    G    H   " << endl;
}

void print_cell_bit(int ch, coordinate *present_place, int color, Field board[8][8]) {

	set_Console_color(black, color);

	for (int cw = 0; cw < 5; cw++) {

		if (cw == 2 && ch == 1)
			print_Figure(*present_place, color, board);

		else
			cout << ' ';

		if (cw == 2)
			present_place->x++;
	}
}

void print_line_bit(int ch, coordinate *present_place, int first_color, Field board[8][8]) {

	print_left_edge(ch, *present_place);

	for (int tw = 0; tw < 4; tw++) {

		if (first_color == grey) {

			print_cell_bit(ch, present_place, grey, board);
			print_cell_bit(ch, present_place, blue, board);
		}

		else {

			print_cell_bit(ch, present_place, blue, board);
			print_cell_bit(ch, present_place, grey, board);
		}
	}

	print_right_edge(ch, *present_place);

	cout << endl;

	present_place->x = 0;
}

void print_line(coordinate *present_place, int first_color, Field board[8][8]) {

	for (int ch = 0; ch < 3; ch++) {

		print_line_bit(ch, present_place, first_color, board);
	}

	present_place->y++;
}

void print_Winner(int winner) {

	if (winner != -2) {

		if (winner == -1) cout << "Black won!";

		else if (winner == 0) cout << "Drawn!";

		else cout << "White won!";
	}
}