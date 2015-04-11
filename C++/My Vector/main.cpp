/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
	@file		main.cpp
	@author		Sergey Ivanychev, sergeyivanychev@gmail.com, MIPT DCAM, 376 group

	@mainpage
	@par		There's a prototype vector realization. 
				-  The size of vector is automatically changing during push_back
				-  Support of		vector + vector (even if sizes are different), 
									double * vector, 
									vector * double, 
									vector[index], 
									vector = vector operators
				-  There are MODULE methon inside
	
	@par		Main function is a complex of vector testing.

	@par		This realization wasn't copied from anywhere and inspired by C++ standard vector class,
				which was used by me few years ago. Theory by Ilya Ruydolphovych and Stephen Pratha.

	@version	V 1.1

	@par		Changelog V1.1
				
				- added support for +=, -=, *= operators
				- APPEND edited to PUSH_BACK
				- added POP_BACK, PUSH_FRONT, POP_FRONT functions. Vector now could represent Stack, Deck, Queue
				- added some usable functions: INSERT, INSERT_ARRAY, SHIFT_LEFT, SHIFT_RIGHT, REMOVE_RANGE
				- fixed operator [] support. Now return value type is double&
				- FIXED: added initialization list of standard constructor

	@todo		- Write detailed documentation
				- Add __FUNCTION__ macros synonyms for GCC and VS using compiler detection
				- Refactor operator+/- and +=/-= functions definition using macroses
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
*/

#define DEBUG_MODE

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef DEBUG_MODE
#include "debug.h"
#endif

#include "vector_header.h"

FILE* STRERR = NULL;
FILE* STRLOG = NULL;

const int RANDOM_RANGE = 20;


int main()
{
	STRERR = stdout;
	STRLOG = stdout;
	
	FILE* strout = fopen("output.txt", "w");
	assert(strout != NULL);

	Vector a;
	for (int i = 0; i < 5 ; ++i)
	{
		a.push_back(rand() % RANDOM_RANGE);
		putc('\n', strout);
		printf("Size = %d, Memory = %d\n", a.get_size(), a.get_memory_size());
	}
	
	a.dump();
	a *= 10;
	a.dump();
	a.shift_left(2);
	a.dump();
	a.shift_right(1);
	a.dump();
	a.insert(3.1415, 3);
	a.dump();
	double data_a[] = {1, 2, 3};
	a.insert_array(data_a, 3, 1);
	a.dump();
	/*
	for (int i = 1; i < 20; ++i) a.push_back(i);

	a.print(strout);
	printf("\n%lg - module\n", a.module());

	a.reset();
	printf("Resetting...\n");
	a.print(strout);

	fputc('\n', strout);

	fprintf(strout, "Checking memory autoallocating...\n");
	for (int i = 0; i < 10; ++i)
	{
		a.push_back(rand() % RANDOM_RANGE);
		putc('\n', strout);
		printf("Size = %d, Memory = %d\n", a.get_size(), a.get_memory_size());
	}
	fprintf(strout, "\nDone\nResetting...\n\n");
	fprintf(strout, "Creating another vector. Testing copying \n");

	Vector b = a;
	a.dump(strout);
	putc('\n', strout);
	b.dump(strout);


	fprintf(strout, "Test done. Resetting and generating random vectors\n");
	a.reset();
	b.reset();
	
	for (int i = 0; i < 3; ++i) 
	{ 
		a.push_back(rand() % RANDOM_RANGE);
		b.push_back(rand() % RANDOM_RANGE);
	}
	b.push_back(rand() % RANDOM_RANGE);

	fprintf(strout, "Dumping first...\n\n");
	a.dump(strout);
	fprintf(strout, "Dumping second...\n\n");
	b.dump(strout);

	Vector c = a + b;
	fprintf(strout, "\nDumping sum...\n\n");
	c.dump(strout);
	
	Vector d = a - b;
	fprintf(strout, "\nDumping difference...\n\n");
	d.dump(strout);
	
	Vector e = a * 10;
	fprintf(strout, "\nDumping first * 10...\n\n");
	e.dump(strout);
	
	Vector f = (1/10.0) * e;
	fprintf(strout, "\nDumping (1/10) * last result...\n\n");
	f.dump(strout);

	double temp_data[] = {1, 2, 3, 4, 5};
	Vector g = {5, temp_data};
	fprintf(strout, "\nTesting creating vector from {1, 2, 3, 4, 5} array\n\n");
	g.dump(strout);

	fprintf(strout, "\nPrinting data using [] operands...\n\n");
	for (int i = 0; i < g.get_size(); ++i) fprintf(strout, "%lg\n", g[i]);
	*/
	system("PAUSE");
	return 0;
}