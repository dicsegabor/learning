#ifndef _BOARD_H
#define _BOARD_H

#include "field.h"
#include "graphics.h"
#include "linked_list.h"

///
/// Az oszt�ly mag�t a sakkt�bl�t reprezent�lja.
/// K�t priv�t adattagja van "board" �s "present_team".
///
class Chessboard {

	///
	/// Egy 8x8-as k�tdimenzi�s t�mb, amely "Field" oszt�lyokb�l �ll.
	///
	Field board[8][8];

	///
	/// Az aktu�lisan l�p� csapatot mutatja. 
	///
	int present_team;

public:

	Chessboard() :present_team(light) {}

	int get_Present_team() { return present_team; }

	void reset();

	///
	/// Kirajzolja a t�bla tartalm�t a konzolba.
	/// Ehhez seg�ts�g�l h�v tagf�ggv�nyeket a "graphics.h"-b�l.
	/// Kirajzol�s el�tt t�rli a k�perny�t, �s a t�bla ut�n kett� �res sort hagy.
	///
	void print();

	///
	/// Visszat�r�si �rt�k�vel jelzi, hogy az adott mez�n �ll-e paraszt,
	/// �s ha igen, akkor a paraszt �ltal v�dett mez�k�n �llnak-e parasztok.
	/// -2 = Nem v�d semmit a paraszt.
	/// -1 = �res a mez�.
	/// 0 = Mindk�t v�dett mez�n �ll paraszt.
	/// 1 = A parasztt�l jobbra l�v� v�dett mez�n �ll paraszt.
	/// 2 = A parasztt�l balra l�v� v�dett mez�n �ll paraszt.
	///
	int get_Formation(int s, int o);

	///
	/// Megadja egy param�terk�nt megadott l�p�sr�, hogy milyen t�pus�.
	/// Param�terk�nt kapja tov�bb� a legutols� megt�rt�nt l�p�st, �s az aktu�lis csapatot.
	/// Visszat�r�si �rt�kei:
	/// -1 = �rv�nytelen l�p�s.
	/// 0 = sima egyes l�p�s.
	/// 1 = �t�s.
	/// 2 = dupla l�p�s (csak a legels� lehet az).
	/// 3 = en passant.
	///
	int get_Move_type(step m, List_node* last_Move);

	///
	/// A t�bl�n l�v� mez�k �rt�k�t be�ll�tja alap�rtelmezettre
	/// (azaz a tartalmukt�l f�gg�re) a mez�k kapcsolat�nak figyelembe v�tele n�lk�l.
	///
	void reset_Values();

	///
	/// A mez�k kapcsolata alapj�n (azaz a mez�n �ll� paraszt mely mez�ket v�di)
	/// be�ll�tja az �rintett mez�k �rt�k�t.
	/// El�sz�r vissza�ll�tja a mez�k �rt�k�t alap�rtelmezettre.
	/// Ha a mez� v�dett, akkor a mez�n �ll� paraszt �ltal v�dett nem �res mez�k �rt�k�t
	/// n�veli, illetve cs�kkenti a paraszt sz�n�t�l f�gg�en.
	///
	void update_Values();

	///
	/// Visszat�r a t�bla �sszes�tett �rt�k�vel.
	/// El�sz�r friss�ti a t�bla mez�inek �rt�keit,
	/// majd egyes�vel �sszeadja �ket.
	///
	int get_Value();

	///
	/// �tm�solja a megadott mez� tartalm�t a megadott helyre.
	/// Param�terk�nt egy "step"-et kap, ami egy kiindul�-
	/// �s egy c�lkoordin�t�t tartamaz.
	/// V�g�l kinull�zza a kiindul� mez�t.
	///
	void move_Figure(step m);

	/// 
	/// V�grehajt egy l�p�st �s �t�ll�tja a k�vetkez� csapatot.
	/// Param�terk�nt egy l�p�st �s a fajt�j�t kapja meg.
	/// Az en passant �t�se itt t�rt�nik meg.
	/// 
	void make_a_move(step m, int move_type);

	/// 
	/// A param�terk�nt megadott koordin�t�hoz/mez�h�z tartoz�
	/// �sszes lehets�ges l�p�st berakja egy param�terk�nt megadott
	/// l�ncolt list�ba.
	/// Ha �res mez�t, vagy nem megfelel� sz�n�t v�lasztottunk, akkor
	/// hamis �rt�kkel t�r vissza, egy�bk�nt igazzal.
	/// 
	bool add_Possibilities(Linked_list& list, coordinate from);

	///
	/// Ki�rja a mez�k �rt�keit. (F�leg debughoz)
	/// Egyes�vel ki�rja az adott mez� �rt�k�t,
	/// j�l olvashat� form�tumban, ami egyezik a sakkt�bl��val.
	///
	void print_Values();

	bool test_for_End(List_node *last_move);

	int get_Winner(List_node *last_move);

	void operator=(Chessboard const& original);
};

#endif // !_BOARD_H

