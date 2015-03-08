#include "stdio.h"
#include "string.h"
#include "stdlib.h"

struct action {
	char pref[3];
	int  shift;	// на сколько сдвигаем
	int  add; 	// сколько добавляем
	int  type;
};

struct action acts[] = {
	{"ma", 1, 1, 0},
	{"fe", 1, 0, 0},
	{"cl", 1, 1, 1},
	{"du", 1, 0, 1},
	{"ha", 1, 1, 2},
	{"nh", 1, 0, 2},
	{"tr", 1, 1, 3},
	{"sk", 1, 0, 3},
	{"bn", 2, 0, 4},
	{"rd", 2, 1, 4},
	{"bw", 2, 2, 4},
	{"bk", 2, 3, 4},
	{"bu", 2, 0, 5},
	{"ge", 2, 1, 5},
	{"gy", 2, 2, 5},
	{"da", 2, 3, 5}
};

int act_compare(const void* p1, const void* p2)
{
	struct action* act1 = (struct action*)p1;
	struct action* act2 = (struct action*)p2;
	return act1 -> type - act2 -> type;
}


int main()
{
	FILE* input = fopen("input.txt", "r");

	int key = 0;
	int i = 0;
	char string[3]  = {};
	int  order[100] = {};
	int  types[6]   = {0};
	int  num_order  = 0;
	while (fscanf(input, "%s", string) == 1)
	{
		for (i = 0; i < 15; i+= 1)
			if (strcmp(string, acts[i].pref) == 0)
				break;

		if (types[acts[i].type] == 0)
		{
			order[num_order] = i;
			num_order += 1;
			types[acts[i].type] += 1;
		}
	}

	struct action* array = (struct action*)calloc(num_order, sizeof(struct action));
	for (i = 0; i < num_order; ++i)
		array[i] = acts[order[i]];
	qsort(array, num_order, sizeof(struct action), act_compare);

	for (i = num_order - 1; i >= 0; i--)
	{
		key = key << array[i].shift;
		key = key +  array[i].add;
	}

	printf("%x\n", key);

	fclose(input);
	return 0;
}