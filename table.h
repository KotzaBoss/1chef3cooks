#ifndef __TABLE_H__
#define __TABLE_H__

#include "ingredient.h"

typedef struct Table* Table;

Table Table_new();
void Table_place(Ingredient i1, Ingredient i2);
const Ingredient* Table_ingredients(Table self);
void Table_set_ingredients(Table self, Ingredient i1, Ingredient i2);
Ingredient Table_ingredient_not_on_table(Table self);

#endif
