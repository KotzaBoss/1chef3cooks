#include "table.h"
#include <stdlib.h>
#include <stdbool.h>

struct Table {
	Ingredient ingredients[2];
};

Table Table_new()
{
	Table t = malloc(sizeof(struct Table));
	if (!t) return NULL;

	t->ingredients[0] = INONE;
	t->ingredients[1] = INONE;

	return t;
}

const Ingredient* Table_ingredients(Table self)
{
	return self->ingredients;
}

void Table_set_ingredients(Table self, Ingredient i1, Ingredient i2)
{
	self->ingredients[0] = i1;
	self->ingredients[1] = i2;
}

// @brief A horrible "find missing" algorithm
Ingredient Table_ingredient_not_on_table(Table self)
{
	Ingredient ingrs[] = { IPITA, IPATATES, IGYROS };

	for (int ingr_i = 0; ingr_i < 3; ++ingr_i)
	{
		bool found = false;
		for (int table_i = 0; table_i < 2; ++table_i)
		{
			if (self->ingredients[table_i] == ingrs[ingr_i])
			{
				found = true;
				break;
			}
		}
		if (!found)
			return ingrs[ingr_i];
	}
	return INONE;
}
