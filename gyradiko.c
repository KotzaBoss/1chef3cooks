#include <stdlib.h>
#include <stdio.h>

#include "gyradiko.h"
#include "chef.h"
#include "cook.h"
#include "table.h"
#include "ingredient.h"

struct Gyradiko {
	Chef chef;
	Cook cook1,
		 cook2,
		 cook3;
	Table table;
};

Gyradiko Gyradiko_new()
{
	Gyradiko g = malloc(sizeof(struct Gyradiko));
	if (!g) return NULL;

	Chef cf = Chef_new();
	if (!cf) return NULL;

	Cook ck1 = Cook_new();
	if (!ck1) return NULL;

	Cook ck2 = Cook_new();
	if (!ck2) return NULL;

	Cook ck3 = Cook_new();
	if (!ck3) return NULL;

	Table t = Table_new();
	if (!t) return NULL;

	Chef_init(cf, Cook_semaphore(ck1), Cook_semaphore(ck2), Cook_semaphore(ck3), t);
	Cook_init(ck1, Chef_cook_semaphore(cf, IPITA), t);
	Cook_init(ck2, Chef_cook_semaphore(cf, IPATATES), t);
	Cook_init(ck3, Chef_cook_semaphore(cf, IGYROS), t);

	g->chef = cf;
	g->cook1 = ck1;
	g->cook2 = ck2;
	g->cook3 = ck3;
	return g;
}

void Gyradiko_start(Gyradiko g)
{
	pthread_create(Chef_tid(g->chef), NULL, Chef_run, g->chef);
	pthread_create(Cook_tid(g->cook1), NULL, Cook_run, g->cook1);
	pthread_create(Cook_tid(g->cook2), NULL, Cook_run, g->cook2);
	pthread_create( Cook_tid(g->cook3), NULL, Cook_run, g->cook3);
}

void Gyradiko_stop(Gyradiko g)
{
	pthread_join(*Chef_tid(g->chef), NULL);
	pthread_join(*Cook_tid(g->cook1), NULL);
	pthread_join(*Cook_tid(g->cook2), NULL);
	pthread_join(*Cook_tid(g->cook3), NULL);
}
