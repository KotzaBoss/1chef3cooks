#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "cook.h"
#include "table.h"

static inline
void createANDconsume()
{
	sleep(rand() % 1);
}

struct Cook {
	pthread_t tid;
	sem_t done;
	sem_t* chef_ready;
	Table table;
};

Cook Cook_new()
{
	return malloc(sizeof(struct Cook));
}

void Cook_init(Cook self, sem_t* chef_ready, Table table)
{
	sem_init(&self->done, 0, 0);
	self->chef_ready = chef_ready;
	self->table = table;
}

void* Cook_run(void* self_)
{
	Cook self = self_;
	while (1) {
		fprintf(stderr, "COOK:: Waiting for chef\n");
		sem_wait(self->chef_ready);
		Ingredient i = Table_ingredient_not_on_table(self->table);
		fprintf(stderr, "COOK%d:: Consuming\n", i);
		Ingredient ingredients[2];
		Cook_take_ingredients(self, ingredients);
		fprintf(stderr, "COOK%d:: i1=%d, i2=%d\n", i, ingredients[0], ingredients[1]);
		createANDconsume();
		fprintf(stderr, "COOK%d:: Posting for chef\n", i);
		sem_post(&self->done);
	}
	pthread_exit(0);
}

sem_t* Cook_semaphore(Cook self)
{
	return &self->done;
}

pthread_t* Cook_tid(Cook self)
{
	return &self->tid;
}

void Cook_take_ingredients(Cook self, Ingredient ingredients[2])
{
	const Ingredient* is = Table_ingredients(self->table);
	ingredients[0] = is[0];
	ingredients[1] = is[1];
	Table_set_ingredients(self->table, INONE, INONE);

}
