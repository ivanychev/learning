#ifndef VECTOR_HEADER_
#define VECTOR_HEADER_

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								INCLUDED HEADERS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <assert.h>
#include <crtdbg.h>
#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								CLASS
//DESCRIPTION
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

class Vector {
public:
  double *data;
  int push_back(double value);
  double pop_back();
  int push_front(double value);
  double pop_front();

  int reset();
  double module() const;
  int insert(double value, int place);
  int insert_array(double *array_, int array_size, int place);
  int remove(int index);
  int remove_range(int from, int to);
  int shift_right(int step);
  int shift_left(int step);

  void print(FILE *stream = stdout);
  void dump(FILE *stream = stdout);
  int get_memory_size();
  int get_size();

  Vector();
  Vector(const Vector &a);
  Vector(int size, double *array);
  ~Vector();
  Vector operator+(const Vector &that) const;
  Vector operator-(const Vector &that) const;
  Vector operator*(double value) const;
  friend Vector operator*(double value, const Vector &that);
  void operator+=(const Vector &that);
  void operator-=(const Vector &that);
  void operator*=(double value);

  double &operator[](int index) const;

private:
  int _memory_size;
  int _set_size(int new_size);
  int _realloc_memory(int new_memory_size);
  int _optimize_memory();
  int _extend_data();
  int _cut_data();
  const int MEMORY_BLOCK_SIZE = 10;
  int check() const;
  int size;
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								CONSTANTS
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

enum Vector_constants {
  VECTOR_OK = 1001,
  VECTOR_NO_MEMORY = 1002,
  VECTOR_CUT_FAILED = 1003,
  VECTOR_INDEX_BAD = 1004,
  VECTOR_THIS_NULL = 1005,
  VECTOR_DATA_NULL = 1006,
  VECTOR_DATA_LEAK = 1007,
  VECTOR_NOT_EGH_MEM = 1008,
  VECTOR_OPTIM_FAIL = 1009,
  VECTOR_BAD = 1010,
};

const int POISON = 0xDEADBABE;

#endif