#ifndef __CHEF_H__
#define __CHEF_H__

#include <pthread.h>
#include <semaphore.h>

#include "cook.h"
#include "table.h"
#include "ingredient.h"

typedef struct Chef* Chef;

Chef Chef_new();
void Chef_init(Chef self, sem_t* pita, sem_t* patates, sem_t* gyros, Table table);
void* Chef_run(void* self_);

pthread_t* Chef_tid(Chef self);
sem_t* Chef_cook_semaphore(Chef self, Ingredient i);

void Chef_place_rand_ingredients_on_table(Chef self);

#endif
