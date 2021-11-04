#ifndef __COOK_H__
#define __COOK_H__

#include <pthread.h>
#include <semaphore.h>

#include "chef.h"
#include "table.h"
#include "ingredient.h"

typedef struct Cook* Cook;

Cook  Cook_new();
void Cook_init(Cook self, sem_t* chef_ready, Table table);
void* Cook_run(void* self_);
sem_t* Cook_semaphore(Cook self);
pthread_t* Cook_tid(Cook self);
void Cook_take_ingredients(Cook self, Ingredient ingredients[2]);

#endif
