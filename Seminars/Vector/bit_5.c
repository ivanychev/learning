#include "stdio.h"
#include "string.h"

struct action {
	char pref[3];
	int  shift;	// на сколько сдвигаем
	int  add; 	// сколько добавляем
}

struct action* acts[] = {
	{"ma", 1, 1},
	{"fe", 1, 0},
	{"cl", 1, 1},
	{"du", 1, 0},
	{"ha", 1, 1},
	{"nh", 1, 0},
	{"tr", 1, 1},
	{"sk", 1, 0},
	{"bn", 2, 0},
	{"rd", 2, 1},
	{"bw", 2, 2},
	{"bk", 2, 3},
	{"bu", 2, 0},
	{"ge", 2, 1},
	{"gy", 2, 2},
	{"da", 2, 3}
};


int main(int argc, char const *argv[])
{
	int key = 0;
	int i = 0;
	char string[3] = {};
	while (scanf("%s", string))
	{
		for (i = 0; i < 15; i+= 1)
			if (strcmp(string, acts[i].pref) == 0)
				break;
		key  = key << acts[i].shift;
		key += acts[i].add;
	}

	printf("%x", key);
	return 0;
}