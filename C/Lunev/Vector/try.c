#include "ivvector.h"
#include "stdio.h"

// #define TRY_DEBUG

#ifdef TRY_DEBUG
#define POINT POINT1
#define POINT1 printf("POINT 1 !!!!!!!!!!!!!!!!\n");
#define POINT2 printf("POINT 2 !!!!!!!!!!!!!!!!\n");
#define POINT3 printf("POINT 3 !!!!!!!!!!!!!!!!\n");
#define POINT4 printf("POINT 4 !!!!!!!!!!!!!!!!\n");
#define VECTOR_DUMP(vecptr) __vector_dump(vecptr);
#else
#define POINT
#define POINT1
#define POINT2
#define POINT3
#define POINT4
#define VECTOR_DUMP(vecptr)
#endif

int int_sort(const void *p1, const void *p2) {
  //	printf("Comparing %d [%p] %d [%p]\n", *(int*)p1, p1, *(int*)p2, p2);
  return *(int *)p2 - *(int *)p1;
}

void int_destructor(void *obj) { printf("Destructed %d!\n", *(int *)obj); }

void *int_do(void *obj, void *args) {
  printf("Printing element!\n%d\n", *(int *)obj);
  return (void *)1;
}

void big_tester();

int main(int argc, char const *argv[]) {
  for (int i = 0; i < 100; ++i)
    big_tester();
  return 0;
}

void big_tester() {
  vector_init(first, int, int_destructor);

  // fprintf(stderr, ">>>>>>>0\n");
  //	Testing insert and erase

  int a1 = 1;
  int a2 = 2;
  int a3 = 3;
  int a4 = 4;
  int a22 = 2;
  int a32 = 3;

  vector_pushfront(first, &a2);
  POINT;
  vector_pushfront(first, &a1);
  POINT;
  vector_pushback(first, &a3);
  POINT;
  vector_pushback(first, &a4);
  // fprintf(stderr, ">>>>>>>1\n");
  VECTOR_DUMP(first);

  vector_insert(first, &a32, 2);
  vector_insert(first, &a22, 2);
  VECTOR_DUMP(first);

  vector_erase(first);
  VECTOR_DUMP(first);
  // fprintf(stderr, ">>>>>>>2\n");
  vector_pushfront(first, &a2);
  vector_pushfront(first, &a1);
  vector_pushback(first, &a3);
  vector_pushback(first, &a4);
  VECTOR_DUMP(first);
  // fprintf(stderr, ">>>>>>>3\n");
  vector_insert(first, &a32, 2);
  VECTOR_DUMP(first);
  vector_remove(first, 1);
  VECTOR_DUMP(first);
  // fprintf(stderr, ">>>>>>>4\n");
  //	Testing sort
  VECTOR_DUMP(first);
  vector_sort(first, int_sort);
  VECTOR_DUMP(first);

  //	Testing get-set
  int temp = 0;
  vector_get(first, 0, &temp);
  printf("%d\n", temp);
  temp = 0;
  // fprintf(stderr, ">>>>>>>5\n");
  vector_set(first, 0, &temp);
  VECTOR_DUMP(first);

  printf("Size    = %" PRIu32 "\n"
         "Esize   = %" PRIu32 "\n"
         "Maxsize = %" PRIu32 "\n"
         "Alloc   = %" PRIu32 "\n",
         vector_size(first), vector_esize(first), vector_maxsize(first),
         vector_alloc(first));
  // fprintf(stderr, ">>>>>>>6\n");
  //	Testing fit
  vector_pushback(first, &a1);
  vector_pushback(first, &a1);
  vector_pushback(first, &a1);
  VECTOR_DUMP(first);

  vector_fit(first);
  VECTOR_DUMP(first);
  // fprintf(stderr, ">>>>>>>7\n");
  //	Testing is empty
  int is_empty = 0;
  is_empty = vector_empty(first);
  printf("%d\n", is_empty);

  vector_erase(first);

  is_empty = vector_empty(first);
  printf("%d\n", is_empty);
  // fprintf(stderr, ">>>>>>>8\n");
  //  	Testing iterators

  vector_iter *first_iter = vector_iter_get(first);
  POINT;
  int cond = vector_iter_next(first_iter, NULL);
  POINT1;
  vector_iter_next(first_iter, &temp);
  vector_iter_next(first_iter, &temp);
  // fprintf(stderr, ">>>>>>>9\n");
  printf("cond = %d, temp = %d\n", cond, temp);
  vector_iter_prev(first_iter, NULL);
  vector_iter_prev(first_iter, &temp);
  printf("%d\n", temp);
  // fprintf(stderr, ">>>>>>>10\n");
  vector_pushfront(first, &a2);
  vector_pushfront(first, &a1);
  vector_pushback(first, &a3);
  vector_pushback(first, &a4);
  VECTOR_DUMP(first);
  vector_popfront(first, &a1);
  // fprintf(stderr, ">>>>>>>11\n");
  vector_iter_begin(first_iter);
  vector_iter_next(first_iter, &temp);
  vector_iter_next(first_iter, &temp);
  printf("cond = %d, temp = %d\n", cond, temp);
  vector_iter_prev(first_iter, NULL);
  vector_iter_prev(first_iter, &temp);
  printf("%d\n", temp);
  // fprintf(stderr, ">>>>>>>12\n");
  vector_iter_getelem(first_iter, &temp);
  printf("%d\n", temp);
  temp = 100;
  vector_iter_setelem(first_iter, &temp);
  vector_iter_end(first_iter);
  vector_iter_getelem(first_iter, &temp);
  printf("%d\n", temp);
  // fprintf(stderr, ">>>>>>>13\n");
  VECTOR_DUMP(first);
  printf("%d %d\n", vector_iter_isend(first_iter),
         vector_iter_isbegin(first_iter));

  // fprintf(stderr, ">>>>>>>14\n");
  vector_iter_do(first_iter, NULL, int_do);

  // Testing optimization

  vector_pushback(first, &a4);
  vector_pushback(first, &a4);
  vector_pushback(first, &a4);
  vector_pushback(first, &a4);
  vector_pushback(first, &a4);
  vector_pushback(first, &a4);
  vector_pushback(first, &a4);
  VECTOR_DUMP(first);
  // fprintf(stderr, ">>>>>>>15\n");

  VECTOR_DUMP(first);
  vector_popback(first, &a4);
  VECTOR_DUMP(first);
  vector_popback(first, &a4);
  VECTOR_DUMP(first);

  vector_insert(first, &a4, 100);
  vector_get(first, 100, &a4);
  vector_set(first, 100, &a4);
  vector_remove(first, 100);
  // fprintf(stderr, ">>>>>>>16\n");

  __vector_iter_dump(first_iter);
  vector_iter_del(first_iter);
  // fprintf(stderr, ">>>>>>>17\n");

  /**/
  vector_delete(first);
  POINT4;
}