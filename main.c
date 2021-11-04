#include <stdio.h>

#include "chef.h"
#include "cook.h"
#include "gyradiko.h"


int main(void)
{
	Gyradiko g = Gyradiko_new();
	if (!g)
	{
		printf("??????????\n");
		return 1;
	}
	Gyradiko_start(g);
	Gyradiko_stop(g);
}
