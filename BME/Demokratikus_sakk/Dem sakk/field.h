#ifndef _FIELD_H
#define _FIELD_H

#include "control.h"

///
/// A sakkt�bla egy mezej�t reprezent�lja.
/// K�t priv�t adattagja van "content" �s "value".
///
class Field {

	///
	/// A mez� �ltal t�rol figr�t. vagy �ppen a hi�ny�t jelzi.
	/// �llapotai:
	/// light = vil�gos paraszt = 1
	/// dark = s�t�t paraszt = -1
	/// neutral = �res = 0
	///
	int content;
	
	///
	/// A mez� aktu�lis �rt�k�t mutatja.
	/// �rt�k Pl.: Vil�gos paraszt eset�n = 1.
	///
	int value;

public:

	Field(int content = neutral) :content(content), value(content) {}
	Field(const Field& f) :content(f.content), value(f.value) {}

	int get_Content() { return content; }
	int get_Value() { return value; }

	///
	/// Megmutatj, hogy �res-eaz adott mez�.
	///
	bool is_Empty() { return content == 0; }

	///
	/// A param�terk�nt kapott integer sz�mot hozz�adja a mez� �rt�k�hez.
	///
	void add_to_Value(int x) { value += x; }

	///
	/// Kinull�zza a mez�t.
	/// A tartalm�t "neutral"-ra, azaa �resre, az �rt�k�t pedig 0-ra �ll�tja.
	///
	void empty_Field() { content = neutral; value = 0; }

	///
	/// A mez� �rt�k�t vissza�ll�tja az az �ltal tartalmazott paraszt szerint.
	///
	void reset_Value() { value = content; }

	Field& operator=(const Field& f);
};

#endif // !_FIELD_H

