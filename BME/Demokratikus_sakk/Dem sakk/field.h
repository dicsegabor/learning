#ifndef _FIELD_H
#define _FIELD_H

#include "control.h"

///
/// A sakktábla egy mezejét reprezentálja.
/// Két privát adattagja van "content" és "value".
///
class Field {

	///
	/// A mezõ által tárol figrát. vagy éppen a hiányát jelzi.
	/// Állapotai:
	/// light = világos paraszt = 1
	/// dark = sötét paraszt = -1
	/// neutral = üres = 0
	///
	int content;
	
	///
	/// A mezõ aktuális értékét mutatja.
	/// Érték Pl.: Világos paraszt esetén = 1.
	///
	int value;

public:

	Field(int content = neutral) :content(content), value(content) {}
	Field(const Field& f) :content(f.content), value(f.value) {}

	int get_Content() { return content; }
	int get_Value() { return value; }

	///
	/// Megmutatj, hogy üres-eaz adott mezõ.
	///
	bool is_Empty() { return content == 0; }

	///
	/// A paraméterként kapott integer számot hozzáadja a mezõ értékéhez.
	///
	void add_to_Value(int x) { value += x; }

	///
	/// Kinullázza a mezõt.
	/// A tartalmát "neutral"-ra, azaa üresre, az értékét pedig 0-ra állítja.
	///
	void empty_Field() { content = neutral; value = 0; }

	///
	/// A mezõ értékét visszaállítja az az által tartalmazott paraszt szerint.
	///
	void reset_Value() { value = content; }

	Field& operator=(const Field& f);
};

#endif // !_FIELD_H

