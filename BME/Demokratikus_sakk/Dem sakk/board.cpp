#include "board.h"

using std::cout;

/**
 * @brief 
 * 
 * Vissza�ll�tja a t�bl�t az "eredeti" �llapot�ba.
 * 8 vil�gos paraszt szemben 8 s�t�t paraszttal.
 */
void Chessboard::reset() {

	present_team = light;

	for (int o = 0; o < 8; o++)
		board[0][o] = Field(light);

	for (int o = 0; o < 8; o++)
		for (int s = 1; s < 7; s++)
			board[s][o].empty_Field();

	for (int o = 0; o < 8; o++)
		board[7][o] = Field(dark);
}

void Chessboard::print() {

	coordinate present_place = { 0, 0 };

	print_Header();

	for (int th = 0; th < 4; th++) {

		print_line(&present_place, grey, board);

		print_line(&present_place, blue, board);
	}

	print_Header();

	set_Console_color(light_grey, black);

	cout << '\n';

	if(present_team == light)
		cout << "               White moves!";

	else
		cout << "               Black moves!";

	cout << "\n\n";
}

int Chessboard::get_Formation(int s, int o) {

	int content;

	if ((content = board[s][o].get_Content()) == 0)
		return -1;

	switch (o) {

		case 0: if (!board[s + content][o + 1].is_Empty()) return 1; else return -2; break;
		case 7: if (!board[s + content][o - 1].is_Empty()) return 2; else return -2; break;

		default: 

			if (!board[s + content][o + 1].is_Empty() && !board[s + content][o - 1].is_Empty()) return 0;

			else if (!board[s + content][o + 1].is_Empty()) return 1;

			else if (!board[s + content][o - 1].is_Empty()) return 2;

		break;
	}

	return -2;
}

int Chessboard::get_Move_type(step m, List_node* last_Move) {

	int content = board[m.from.x][m.from.y].get_Content();

	if (content == 0 || content != present_team)
		return -1;

	else if ((m.from.x - m.to.x == -content) && (m.from.y - m.to.y == 1 || m.from.y - m.to.y == -1)
		&& (board[m.to.x - content][m.to.y].get_Content() == content * -1) && last_Move->move_type == 2)
		return 3;

	else if ((m.from.x - m.to.x == -content) && (m.from.y - m.to.y == 1 || m.from.y - m.to.y == -1)
		&& board[m.to.x][m.to.y].get_Content() == -content)
		return 1;

	else if ((m.from.x == 0 && m.to.x == 2 && content == light && m.from.y == m.to.y) ||
			 (m.from.x == 7 && m.to.x == 5 && content == dark && m.from.y == m.to.y))
		return 2;

	else if ((m.from.x - m.to.x == -content) && (m.from.y == m.to.y) && board[m.to.x][m.to.y].is_Empty())
		return 0;

	return -1;
}

void Chessboard::reset_Values() {

	for (int o = 0; o < 8; o++)
		for (int s = 0; s < 8; s++)
			board[s][o].reset_Value();
}

void Chessboard::update_Values() {

	reset_Values();

	int type;
	int content;

	for (int o = 0; o < 8; o++) 
		for (int s = 0; s < 8; s++) 
			if ((content = board[s][o].get_Content()) != 0)
				if ((type = get_Formation(s, o)) >= 0)
					switch (type) {

						case 0: board[s + content][o - 1].add_to_Value(content); board[s + content][o + 1].add_to_Value(content);  break;
						case 1: board[s + content][o + 1].add_to_Value(content);  break;
						case 2: board[s + content][o - 1].add_to_Value(content);  break;
						default: break;
					}
}

int Chessboard::get_Value() {

	update_Values();

	int value = 0;

	for (int o = 0; o < 8; o++)
		for (int s = 0; s < 8; s++)
			value += board[s][o].get_Value();

	return value;
}

void Chessboard::move_Figure(step m) {

	board[m.to.x][m.to.y] = board[m.from.x][m.from.y];
	board[m.from.x][m.from.y].empty_Field();
}

void Chessboard::make_a_move(step m, int move_type) {


	int content = board[m.from.x][m.from.y].get_Content();

	move_Figure(m);

	if (move_type == 3)
		board[m.to.x - content][m.to.y].empty_Field();

	present_team *= -1;
}

bool Chessboard::add_Possibilities(Linked_list& list, coordinate from) {

	if (board[from.x][from.y].is_Empty() || board[from.x][from.y].get_Content() != present_team)
		return false;

	Chessboard x = *this;

	step move;

	move.from = from;

	int move_type;

	for (int o = 0; o < 8; o++)
		for (int s = 0; s < 8; s++) {

			move.to = { s, o };

			if ((move_type = x.get_Move_type(move, list.last_Move())) != -1) {

				x.make_a_move(move, move_type);
				list.add(move, x.get_Value(), move_type);
				x = *this;
			}
		}

	return !list.is_Empty();
}

void Chessboard::print_Values() {

	update_Values();

	for (int o = 0; o < 8; o++) {

		for (int s = 0; s < 8; s++) {

			if (board[o][s].get_Value() >= 0)
				cout << "  ";

			else
				cout << ' ';

			cout << board[o][s].get_Value();
		}

		cout << '\n';
	}

	cout << "\n\n";
}

bool Chessboard::test_for_End(List_node *last_move) {

	Linked_list possible_moves;

	for (int o = 0; o < 8; o++)
		for (int s = 0; s < 8; s++)
			if(board[s][o].get_Content() == present_team)
				add_Possibilities(possible_moves, { s, o });

	return possible_moves.is_Empty();
}

int Chessboard::get_Winner(List_node *last_move) {

	if (test_for_End(last_move)) {

		int figures = 0;

		for (int o = 0; o < 8; o++)
			for (int s = 0; s < 8; s++)
				figures += board[s][o].get_Content();

		if (figures < 0)
			return -1;

		else if (figures > 0)
			return 1;

		else return 0;
	}

	return -2;
}

void Chessboard::operator=(Chessboard const& original) {

	present_team = original.present_team;

	for (int o = 0; o < 8; o++)
		for (int s = 0; s < 8; s++)
			board[s][o] = original.board[s][o];
}