#include "ivvector.h"
#include "stdio.h"

#define POINT printf("POINT\n");

int int_sort(const void* p1, const void* p2)
{
//	printf("Comparing %d [%p] %d [%p]\n", *(int*)p1, p1, *(int*)p2, p2);
	return *(int*)p2 - *(int*)p1; 
}

void int_destructor(void* obj)
{
	printf("Destructed %d!\n", *(int*)obj);
}

void* int_do(void* obj, void* args)
{
	printf("Printing element!\n%d\n", *(int*)obj);
	return (void*)1;
}

void big_tester();

int main(int argc, char const *argv[])
{
	for (int i = 0; i < 1; ++i)
		big_tester();
	return 0;
}

void big_tester()
{
	vector_init(first, int, int_destructor);

printf(">>>>>>>0\n");
//	Testing insert and erase

	int a1 =  1;
	int a2 =  2;
	int a3 =  3;
	int a4 =  4;
	int a22 = 2;
	int a32 = 3;

	vector_pushfront(first, &a2);
	POINT;
	vector_pushfront(first, &a1);
	POINT;
	vector_pushback (first, &a3);
	POINT;
	vector_pushback (first, &a4);
printf(">>>>>>>1\n");
	__vector_dump(first);

	vector_insert(first, &a32, 2);
	__vector_dump(first);

	vector_erase(first);
	__vector_dump(first);
printf(">>>>>>>2\n");
	vector_pushfront(first, &a2);
	vector_pushfront(first, &a1);
	vector_pushback (first, &a3);
	vector_pushback (first, &a4);
	__vector_dump(first);
printf(">>>>>>>3\n");
	vector_insert(first, &a32, 2);
	__vector_dump(first);
	vector_remove(first, 1);
	__vector_dump(first);
printf(">>>>>>>4\n");
//	Testing sort
	__vector_dump(first);
	vector_sort(first, int_sort);
	__vector_dump(first);

//	Testing get-set
	int temp = 0;
	vector_get(first, 0, &temp);
	printf("%d\n", temp);
	temp = 0;
printf(">>>>>>>5\n");
	vector_set(first, 0, &temp);
	__vector_dump(first);

	printf( "Size    = %"PRIu32"\n"
		"Esize   = %"PRIu32"\n"
		"Maxsize = %"PRIu32"\n"
		"Alloc   = %"PRIu32"\n",
		vector_size(first),
		vector_esize(first),
		vector_maxsize(first),
		vector_alloc(first));
printf(">>>>>>>6\n");
//	Testing fit
	vector_pushback(first, &a1);
	vector_pushback(first, &a1);
	vector_pushback(first, &a1);
	__vector_dump(first);

	vector_fit(first);
	__vector_dump(first);	
printf(">>>>>>>7\n");
//	Testing is empty
	int is_empty = 0;
	is_empty = vector_empty(first);
	printf("%d\n", is_empty);

	vector_erase(first);

	is_empty = vector_empty(first);
	printf("%d\n", is_empty);
printf(">>>>>>>8\n");
// 	Testing iterators

	vector_iter* first_iter = vector_iter_get(first);
	POINT;
	int cond = vector_iter_next(first_iter, NULL);
	POINT;
	vector_iter_next(first_iter, &temp);
	vector_iter_next(first_iter, &temp);
printf(">>>>>>>9\n");
	printf("cond = %d, temp = %d\n", cond, temp);
	vector_iter_prev(first_iter, NULL);
	vector_iter_prev(first_iter, &temp);
	printf("%d\n", temp);
printf(">>>>>>>10\n");
	vector_pushfront(first, &a2);
	vector_pushfront(first, &a1);
	vector_pushback (first, &a3);
	vector_pushback (first, &a4);
	__vector_dump(first);
printf(">>>>>>>11\n");
	vector_iter_begin(first_iter);
	vector_iter_next(first_iter, &temp);
	vector_iter_next(first_iter, &temp);
	printf("cond = %d, temp = %d\n", cond, temp);
	vector_iter_prev(first_iter, NULL);
	vector_iter_prev(first_iter, &temp);
	printf("%d\n", temp);
printf(">>>>>>>12\n");
	vector_iter_getelem(first_iter, &temp);
	printf("%d\n", temp);
	temp = 100;
	vector_iter_setelem(first_iter, &temp);
	vector_iter_end(first_iter);
	vector_iter_getelem(first_iter, &temp);
	printf("%d\n", temp);
printf(">>>>>>>13\n");
	__vector_dump(first);
	printf("%d %d\n", 	vector_iter_isend (first_iter),
				vector_iter_isbegin(first_iter));


printf(">>>>>>>14\n");
	vector_iter_do(first_iter, NULL, int_do);

// Testing optimization

	vector_pushback (first, &a4);
	vector_pushback (first, &a4);
	vector_pushback (first, &a4);
	vector_pushback (first, &a4);
	vector_pushback (first, &a4);
	vector_pushback (first, &a4);
	vector_pushback (first, &a4);
	__vector_dump(first);
printf(">>>>>>>15\n");
	vector_popback (first, &a4);
	vector_popback (first, &a4);
	__vector_dump(first);
	

	vector_insert(first, &a4, 100);
	vector_get   (first, 100, &a4);
printf(">>>>>>>16\n");



	vector_iter_del(first_iter);
printf(">>>>>>>17\n");

/**/
	vector_delete(first);


}