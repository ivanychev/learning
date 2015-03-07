#include "stdint.h"

struct 	Vector_elem;
typedef Vector_elem Vector_e;
struct 	Vector;
// {
// 	uint32_t size;
// 	uint32_t maxsize;
// 	uint32_t iter;
// 	uint32_t elem_size;
// 	Vector_e* begin;
// 	uint32_t alloc;
// };
typedef struct Vector Vector_t;

struct Vector_iter_s;
// {
// 	Vector_t* ptr;
// 	uint32_t num;
// };
typedef struct Vector_iter_s Vector_iter;

int Vector_new   (Vector_t* this);
int Vector_new   (Vector_t* this, const Vector_t copied);
int Vector_new 	 (Vector_t* this, Vector_iter begin, Vector_iter end);
int Vector_delete(Vector_t* this);

int Vector_copy (Vector_t* src,  Vector_t* dest);
int Vector_equal(Vector_t* vec1, Vector_t* vec2);
int Vector_at 	(Vector_t* this, uint32_t index, Vector_e* dest);
int Vector_front(Vector_t* this, Vector_e* dest);
int Vector_back (Vector_t* this, Vector_e* dest);

int Vector_begin(Vector_t* this, Vector_i* dest);
int Vector_end  (Vector_t* this, Vector_i* dest);

int 	 Vector_empty 	(Vector_t* this);
uint32_t Vector_size    (Vector_t* this);
uint32_t Vector_maxsize (Vector_t* this);
uint32_t Vector_capacity(Vector_t* this);

int Vector_clear (Vector_t* this);
int Vector_insert(Vector_t* this, uint32_t index, Vector_e* elem);
int Vector_insert(Vector_t* this, uint32_t index, Vector_t* src);
int Vector_insert(Vector_t* this, uint32_t index, Vector_t* src, uint32_t from, uint32_t to);

int Vector_erase (Vector_t* this, uint32_t index);
int Vector_erase (Vector_t* this, uint32_t from, uint32_t to);

int Vector_pushback (Vector_t* this, Vector_e* elem);
int Vector_pushfront(Vector_t* this, Vector_e* elem);
int Vector_popfront (Vector_t* this, Vector_e* dest);
int Vector_popback  (Vector_t* this, Vector_e* dest);

int Vector_next	   (Vector_iter* iter, Vector_e* dest);
int Vector_prev	   (Vector_iter* iter, Vector_e* dest);
int Vector_getelem (const Vector_iter* iter, Vector_e* dest);
int Vector_setelem (Vector_iter* iter, const Vector_e* dest);
int Vector_begin   (Vector_iter* iter, Vector_e* dest);
int Vector_end     (Vector_iter* iter, Vector_e* dest);
int Vector_get_iter(const Vector* this);
int Vector_islast  (const Vector_iter* iter);
int Vector_isfirst (const Vector_iter* iter);

int Vector_do(Vector_iter* iter, void* args, void (do)(void* argv));