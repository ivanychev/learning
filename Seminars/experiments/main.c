#include "stdio.h"
#include "assert.h"
#include "stdlib.h"


// typedef  struct Cd{
//     int x,y;
// } Coord;

// typedef struct Rc{
//   Coord leftH,rightL;
// } Rectangle;


void getCoord(Coord* a)
{
	assert(a);
	scanf("%d %d", &(a -> x), &(a -> y));
}

void printCoord(Coord a)
{
	printf("(%d,%d)", a.x, a.y);
}

void getDataRec(Rectangle* a)
{
	getCoord(&((*a).leftH ));
	getCoord(&((*a).rightL));
	
}

void printRec(Rectangle a)
{
	printCoord(a.leftH);
	putchar(' ');
	printCoord(a.rightL);
	putchar('\n');
}

int min (int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int max (int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int crossed(Rectangle a, Rectangle b)
{
	Coord al = a.leftH;
	Coord ar = a.rightL;
	Coord bl = b.leftH;
	Coord br = b.rightL;

	if (ar.y > bl.y)
	{
		//printf("ar.y > bl.y");
		return 0;
	}
	if (ar.x < bl.x)
	{
		//printf("ar.x < bl.x\n%d %d\n", ar.x, bl.x);
		return 0;
	}
	
	if (al.y < br.y)
	{
		//printf("al.y < br.y");
		return 0;
	}
	if (al.x > br.x)
	{
		//printf("al.x > br.x");
		return 0;
	}
	return 1;
}

Rectangle* findCrossRec(Rectangle a, Rectangle b)
{
	if (crossed(a, b))
	{
		Rectangle* new = calloc(1, sizeof(Rectangle));
		new -> leftH.x = max(a.leftH.x, b.leftH.x);
		new -> leftH.y = min(a.leftH.y, b.leftH.y);
		
		new -> rightL.x = min(a.rightL.x, b.rightL.x);
		new -> rightL.y = max(a.rightL.y, b.rightL.y);
		
		return new;
	}
	else 
		return 0;
}

int deleteRec(Rectangle* a)
{
	if (a != 0)
		free(a);
	return 1;
}

// int main()
// {
// 	Rectangle a;
// 	Rectangle b;
// 	getDataRec(&a);
// 	getDataRec(&b);

// //	printRec(a);
// //	printRec(b);

// 	Rectangle* c = findCrossRec(a, b);

// 	if (c != 0)
// 		printRec(*c);
// 	else
// 		printf("No cross\n");
// }