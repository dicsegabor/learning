#ifndef LINKED_LIST
#define LINKED_LIST

#include "control.h"

/// 
/// A láncolt lista egy eleme.
/// Tárol egy lépést, az ahhoz tartozó tábla értékét,
/// a lépés típusát és a "next" pointert.
/// Rendelkezik "==" és "!=" operátorokkal.
/// 
struct List_node {

	step move;
	int board_value;
	int move_type;
	List_node *next;

	bool operator==(List_node rhs) const;

	bool operator!=(List_node rhs) const;
};

/// 
/// Maga a láncolt lista.
/// Két privát tagja van:
/// "head" : a legelsõ elemre mutató pointer
/// "length" : a lista hosszát mutatja.
/// 
class Linked_list {
public:

	int length;
	List_node *head;

	/// 
	/// Iterátor osztály, amely a lista használhatóságát segíti.
	/// Egy tagja van, ami a lista egy elemére mutató pointer.
	/// 
	class Iterator {

		List_node *node;

	public:

		Iterator(List_node *element = NULL) :node(element) {}

		Iterator& operator++() { if (node != NULL) node = node->next; return *this; }

		Iterator operator++(int) { Iterator masolat = *this; ++(*this); return masolat; }

		step get_Move() { return node->move; }

		int get_Move_type() { return node->move_type; }

		int get_Board_value() { return node->board_value; }

		List_node* get_Next() { return node->next; }

		List_node get_Node() { return *node; }

		void set_Next(List_node* next) { node->next = next; }

		bool operator==(Iterator rhs) const { return node == rhs.node; }

		bool operator!=(Iterator rhs) const { return node != rhs.node; }
	};

	Linked_list() :length(0), head(NULL) {}

	int get_Length() { return length; }

	bool is_Empty() { return length == 0; }

	/// 
	/// A lista felépítéséért felelõs.
	/// A lista végéhez fûzi az elemeket.
	/// 
	void add(step move, int board_value, int move_type);

	/// 
	/// Visszatér a lista legutolsó elemével.
	/// 
	List_node* last_Move();

	/// 
	/// Visszatér a lista legmagasabb értékkel rendelkezõ elemével.
	/// 
	List_node get_Max();

	/// 
	/// Visszatér a lista legalacsonabb értékkel rendelkezõ elemével.
	/// 
	List_node get_Min();

	/// 
	/// Kitörli a listát.
	/// 
	void delete_list();

	/// 
	/// Kiírja a listát tagonként, minden belsõ változót.
	/// 
	void print_List();

	Iterator begin() { return Iterator(head); }

	Iterator end() { return Iterator(NULL); }

	~Linked_list();
};

#endif
