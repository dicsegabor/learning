#include "field.h"

Field& Field::operator=(const Field& f) {

	content = f.content;
	value = f.value;

	return *this;
}