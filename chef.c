#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "chef.h"

struct Chef {
	pthread_t tid;
	struct {
		sem_t pita,
			  patates,
			  gyros;
	} for_cook_sems;
	struct {
		sem_t* pita,
			 * patates,
			 * gyros;
	} done_sems;
	Table table;
};

Chef Chef_new()
{
	return malloc(sizeof(struct Chef));
}

void Chef_init(Chef self, sem_t* pita, sem_t* patates, sem_t* gyros, Table table)
{
	sem_init(&self->for_cook_sems.pita, 0, 0);
	sem_init(&self->for_cook_sems.patates, 0, 0);
	sem_init(&self->for_cook_sems.gyros, 0, 0);
	self->done_sems.pita = pita;
	self->done_sems.patates = patates;
	self->done_sems.gyros = gyros;
	self->table = table;
}

void* Chef_run(void* self_)
{
	Chef self = self_;
	while (1) {

		fprintf(stderr, "CHEF:: Placing items\n");
		Chef_place_rand_ingredients_on_table(self);
		fprintf(stderr, "CHEF:: Table now has i1=%d, i2=%d\n", Table_ingredients(self->table)[0], Table_ingredients(self->table)[1]);
		Ingredient missing_ingr = Table_ingredient_not_on_table(self->table);
		fprintf(stderr, "CHEF:: Posting for cook %d\n", missing_ingr);

		sem_t* for_cook,
			 * cook_done;
		switch (missing_ingr) {
		case IPITA:
			for_cook = &self->for_cook_sems.pita;
			cook_done = self->done_sems.pita;
			break;
		case IPATATES:
			for_cook = &self->for_cook_sems.patates;
			cook_done = self->done_sems.patates;
			break;
		case IGYROS:
			for_cook = &self->for_cook_sems.gyros;
			cook_done = self->done_sems.gyros;
			break;
		default:
			fprintf(stderr, "This should not be reached\n");
			exit(1);
		}

		sem_post(for_cook);
		fprintf(stderr, "CHEF:: Waiting for cook %d\n", missing_ingr);
		sem_wait(cook_done);
		fprintf(stderr, "CHEF:: Cook%d done\n", missing_ingr);
	}
	pthread_exit(0);
}

pthread_t* Chef_tid(Chef self)
{
	return &self->tid;
}

sem_t* Chef_cook_semaphore(Chef self, Ingredient i)
{
	switch (i) {
		case IPITA: return &self->for_cook_sems.pita;
		case IPATATES: return &self->for_cook_sems.patates;
		case IGYROS: return &self->for_cook_sems.gyros;
		default: return NULL;
	}
}

void Chef_place_rand_ingredients_on_table(Chef self)
{
	Ingredient i1 = rand() % 3,
			   i2;
	while ((i2 = rand() % 3) == i1)
		;

	Table_set_ingredients(self->table, i1, i2);
}
