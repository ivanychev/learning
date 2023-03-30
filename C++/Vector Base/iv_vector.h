/**
 *           @file               iv_vector.h
 *
 *           @par                IV_VECBASE is vector template-based object with
 *potential of creating inheritors. Thanks God, it would be easy with
 *IV_VECBASE. There are only essential methods are implemented, but they are
 *enough to base some inheritors on it.
 **/

#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

#include "exception.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>

#ifdef VECBASE_DEBUG
#define VEC_OUT(str) printf(str);
#define VEC_OUT1(str, arg1) printf(str, arg1);
#define VEC_OUT2(str, arg1, arg2) printf(str, arg1, arg2)
#define VEC_DUMP(vec_ptr) (vec_ptr)->dump(stdout)
#else
#define VEC_OUT(str)
#define VEC_OUT1(str, arg1)
#define VEC_OUT2(str, arg1, arg2)
#define VEC_DUMP(vec_ptr)
#endif // VECBASE_DEBUG

const unsigned VECBASE_STANDARD_BLOCK_SIZE = 10;

template <typename arg_type> class iv_vecbase {
private:
  arg_type **_data;
  unsigned _size;
  unsigned _alloc_size;
  const unsigned _block_size;

  void _pull_apart(unsigned was, unsigned became);

public:
  iv_vecbase();
  explicit iv_vecbase(int vec_size) throw(ivException);

  iv_vecbase(arg_type *arr_ptr, int vec_size) throw(ivException);

  iv_vecbase(const iv_vecbase &copy_vector) throw(ivException);

  iv_vecbase(iv_vecbase &copy_vector, const unsigned from_inclusive,
             const unsigned to_exclusive) throw(ivException);

  virtual bool ok() const;
  char *detailed_ok() const;
  virtual void dump(FILE *stream) const;

  ~iv_vecbase();

  unsigned size() const;
  void set_alloc_size(unsigned new_size);
  void set_size(unsigned new_size);
  void memory_optimize();
  void push_back(const arg_type &added);
  arg_type pop_back();

  void cut(const unsigned from_inclusive, const unsigned to_exclusive);

  arg_type &operator[](unsigned index);
  arg_type operator[](unsigned index) const;

  void insert(const arg_type &obj, const unsigned position);
  void insert(iv_vecbase &vec, const unsigned position);
  void insert(const arg_type *obj, const unsigned amount,
              const unsigned position);
};

#define CHECK(vector) LG_ASSERT(vector.ok() == true, vector.detailed_ok());
#define CHECK_THIS LG_ASSERT(ok() == true, detailed_ok());

const char *CONST_ERROR =
    "Vecbase: Error while constructing objects in constructor";
const char *VER_ERROR = "Vecbase: Verification failed";
const char *COPY_ERROR = "Vecbase: Copying failed";

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>

iv_vecbase<arg_type>::iv_vecbase()
    : _size(0), _alloc_size(VECBASE_STANDARD_BLOCK_SIZE),
      _block_size(VECBASE_STANDARD_BLOCK_SIZE) {
  _data = new arg_type *[_block_size];
  CHECK_THIS;
  VEC_OUT("Vector constructed\n");
};

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>

iv_vecbase<arg_type>::iv_vecbase(int vec_size) throw(ivException)
    :

      _size(vec_size), _block_size(VECBASE_STANDARD_BLOCK_SIZE),
      _alloc_size(vec_size) {
  _data = new arg_type *[vec_size];

  for (int i = 0; i < vec_size; ++i) {
    CALL(_data[i] = new arg_type, CONST_ERROR);
    VEC_OUT1("newing  %08x\n", _data[i]);
  }

  CHECK_THIS;
  VEC_OUT("Vector constructed\n");
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>

iv_vecbase<arg_type>::iv_vecbase(arg_type *arr_ptr,
                                 int vec_size) throw(ivException)
    :

      _size(vec_size), _block_size(VECBASE_STANDARD_BLOCK_SIZE),
      _alloc_size(vec_size) {
  _data = new arg_type *[vec_size];

  for (int i = 0; i < vec_size; ++i) {
    CALL(_data[i] = new arg_type(arr_ptr[i]), COPY_ERROR)
    VEC_OUT1("newing  %08x\n", _data[i]);
  }

  CHECK_THIS;
  VEC_OUT("Vector constructed\n");
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>

iv_vecbase<arg_type>::iv_vecbase(const iv_vecbase &copy_vector) throw(
    ivException)
    :

      _size(copy_vector.size()), _block_size(VECBASE_STANDARD_BLOCK_SIZE),
      _alloc_size(copy_vector.size()) {
  _data = new arg_type *[copy_vector.size()];
  unsigned vec_size = copy_vector.size();

  for (int i = 0; i < vec_size; ++i) {
    CALL(_data[i] = new arg_type(copy_vector[i]), COPY_ERROR);
    VEC_OUT1("newing  %p\n", _data[i]);
  }

  CHECK_THIS;
  VEC_OUT("Vector constructed\n");
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>
iv_vecbase<arg_type>::iv_vecbase(iv_vecbase<arg_type> &copy_vector,
                                 const unsigned from_inclusive,
                                 const unsigned to_exclusive) throw(ivException)
    :

      _size(to_exclusive - from_inclusive),
      _block_size(VECBASE_STANDARD_BLOCK_SIZE),
      _alloc_size(to_exclusive - from_inclusive) {
  VEC_OUT1("Vector constructing...[%08x]\n", this);
  LG_ASSERT(from_inclusive <= to_exclusive,
            "Vecbase: FROM index must not be higher than TO");

  _data = new arg_type *[to_exclusive - from_inclusive + 1];

  unsigned vec_size = to_exclusive - from_inclusive;

  for (int i = 0; i < vec_size; ++i) {
    CALL(_data[i] = new arg_type(copy_vector[from_inclusive + i]), COPY_ERROR);
    VEC_OUT1("newing  %08x\n", _data[i])
  }

  CHECK_THIS;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------
template <typename arg_type>

iv_vecbase<arg_type>::~iv_vecbase() {
  VEC_OUT1("Vector destructing... [%08x]\n", this);
  // VEC_DUMP(this);

  if (_data != NULL) {
    for (int i = 0; i < _alloc_size; ++i)
      if (_data[i] != NULL) {
        VEC_OUT1("deleting %08x\n", _data[i]);
        delete _data[i];

        _data[i] = NULL;
      };
    delete[] _data;
    _data = NULL;
  }

  _size = 0xDEADBABE;
  _alloc_size = 0xDEADBABE;

  VEC_OUT("Vector destructing completed\n");
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

/* DOESN'T WORK
#define CHECK_TEMPLATE(func_name, way1, way2, way3, way4, way5) \
template <typename arg_type> \
bool iv_vecbase<arg_type>::##func_name##() \
{ \
    if (this == NULL)                                       way1; \
    if (_alloc_size < _size)                                way2; \
    if (_data == NULL)                                      way3; \
    for (int i = 0; i < _size; ++i) if (_data[i] == NULL)   way4; \
                                                            way5; \
    } \

CHECK_TEMPLATE( ok,
                return false,
                return false,
                return false,
                return false,
                return true
                )

CHECK_TEMPLATE( detailed_ok,
                return "Vecbase detailed check: THIS pointer is NULL",
                return "Vecbase detailed check: allocated_size if below size of
vector", return "Vecbase detailed check: pointer of pointer array is NULL",
                return "Vecbase detailed check: one of pointers is NULL",
                return "Vecbase detailed check: OK"
                )
*/

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type> bool iv_vecbase<arg_type>::ok() const {
  if (this == NULL)
    return false;
  if (_alloc_size < _size)
    return false;
  if (_data == NULL)
    return false;
  for (int i = 0; i < _size; ++i)
    if (_data[i] == NULL)
      return false;
  return true;
}

template <typename arg_type> char *iv_vecbase<arg_type>::detailed_ok() const {
  if (this == NULL)
    return "Vecbase detailed check: THIS pointer is NULL";
  if (_alloc_size < _size)
    return "Vecbase detailed check: allocated_size if below size of vector";
  if (_data == NULL)
    return "Vecbase detailed check: pointer of pointer array is NULL";
  for (int i = 0; i < _size; ++i)
    if (_data[i] == NULL)
      return "Vecbase detailed check: one of pointers is NULL";
  return "Vecbase detailed check: OK";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>
void iv_vecbase<arg_type>::dump(FILE *stream) const {
  fprintf(stream, "----------------------------------------\n");
  fprintf(stream, "\nVecbase object dump begin\n\n");
  fprintf(stream, "Vector condition:  %s\n", (ok()) ? "OK" : "BAD");
  fprintf(stream, "Address:           %p\n", this);
  fprintf(stream, "Size:              %u\n", _size);
  fprintf(stream, "Allocated size:    %u\n", _alloc_size);
  fprintf(stream, "Block size:        %u\n", _block_size);
  fprintf(stream, "Object pointers printing...\n\n");

  for (int i = 0; i < _alloc_size; ++i)
    fprintf(stream, "%p\n", _data[i]);
  fprintf(stream, "\nVector object dump end\n");
  fprintf(stream, "----------------------------------------\n");
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type> unsigned iv_vecbase<arg_type>::size() const {
  CHECK_THIS;
  return _size;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>
void iv_vecbase<arg_type>::set_alloc_size(unsigned new_size) {
  CHECK_THIS;
  // throw (ivRuntime_error  (
  //                         __FILE__,
  //                         __FUNCSIG__,
  //                         __LINE__,
  //                         "Testing string"
  //                         ));
  VEC_DUMP(this);
  if (new_size == _alloc_size)
    return;
  if (new_size < _alloc_size) {
    CALL(cut(new_size, _size), "Vecbase: cutting failed");
    _data = (arg_type **)realloc((void *)_data, sizeof(arg_type *) * new_size);
    _alloc_size = new_size;
    VEC_DUMP(this);
    RT_ASSERT(_data != NULL, "Vecbase: reallocation failed");
    CHECK_THIS;
    return;
  }

  _data = (arg_type **)realloc((void *)_data, sizeof(arg_type *) * new_size);

  memset(&_data[_alloc_size], 0, new_size - _alloc_size);
  RT_ASSERT(_data != NULL, "Vecbase: reallocation failed");

  _alloc_size = new_size;
  VEC_DUMP(this);
  CHECK_THIS;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>
void iv_vecbase<arg_type>::set_size(unsigned new_size) {
  CHECK_THIS;

  if (new_size == _size)
    return;
  if (new_size < _size) {
    CALL(cut(new_size, _size), "Vecbase: cutting failed");
    CHECK_THIS;
    return;
  }

  //      HERE IF NEW_SIZE > SIZE

  if (_alloc_size < new_size) {
    CALL(set_alloc_size(new_size), "Vecbase: reallocation failed");
    CHECK_THIS;
    return;
  }

  for (int i = new_size; i < _size; ++i) {
    CALL(delete _data[i], "Vecbase: deleting object fail");
    _data[i] = NULL;
  }

  _size = new_size;
  CALL(this->memory_opimize(),
       "Vecbase: memory optimisation failed"); // what the hell I had paste
                                               // "this ->" ??

  CHECK_THIS;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type> void iv_vecbase<arg_type>::memory_optimize() {
  VEC_DUMP(this);
  detailed_ok();
  CHECK_THIS;
  unsigned empty_space = _alloc_size - _size;
  unsigned empty_blocks = empty_space / _block_size;
  bool changed = false;

  if (empty_blocks != 0) {
    CALL(set_alloc_size(_alloc_size - empty_blocks * _block_size),
         "Vecbase: setting new allocation size failed");
    changed = true;
  }

  if (changed) {
    CHECK_THIS;
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>
void iv_vecbase<arg_type>::push_back(const arg_type &added) {
  VEC_DUMP(this);
  CHECK_THIS;

  if (ok() == false)
    throw(ivRuntime_error(
        __FILE__, __FUNCSIG__, __LINE__,
        "Vector verification failed")); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1

  VEC_DUMP(this);
  if (_size == _alloc_size) {
    CALL(set_alloc_size(_size + _block_size),
         "Vecbase: extanding memory failed");
  }
  VEC_DUMP(this);
  _data[_size++] = new arg_type(added);
  CHECK_THIS;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type> arg_type iv_vecbase<arg_type>::pop_back() {
  CHECK_THIS;
  arg_type ret_val = *(_data[--_size]);
  CALL(this->memory_optimize(), "Vecbase: memory optimisation failed");

  CHECK_THIS;
  return ret_val;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>
void iv_vecbase<arg_type>::cut(const unsigned from_inclusive,
                               const unsigned to_exclusive) {
  CHECK_THIS;
  VEC_DUMP(this);
  unsigned to = to_exclusive;
  unsigned from = from_inclusive;
  LG_ASSERT(to >= from, "Vecbase: Bounds error")

  unsigned cut_siz = to - from;
  if (cut_siz == 0)
    return;

  for (int i = from; i < to; ++i) {
    CALL(delete _data[i], "Vecbase: delete error");
    _data[i] = NULL;
  }
  VEC_DUMP(this);
  memcpy(&(_data[from]), &(_data[to]), (_size - to) * sizeof(arg_type *));

  VEC_DUMP(this);
  for (int i = _size - 1; i > _size - 1 - cut_siz; --i)
    _data[i] = NULL;
  _size -= cut_siz;

  VEC_DUMP(this);
  CALL(memory_optimize(), "Vecbase: memory optimization failed");
  CHECK_THIS;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>
arg_type &iv_vecbase<arg_type>::operator[](unsigned index) {
  CHECK_THIS;
  LG_ASSERT(index < _size, "Vecbase: out of bounds");

  arg_type &ret = *(_data[index]);
  return ret;
}

template <typename arg_type>
arg_type iv_vecbase<arg_type>::operator[](unsigned index) const {
  CHECK_THIS;
  LG_ASSERT(index < _size, "Vecbase: out of bounds");

  arg_type ret = *(_data[index]);
  return ret;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>
void iv_vecbase<arg_type>::_pull_apart(unsigned was, unsigned became) {

  CHECK_THIS;
  VEC_DUMP(this);
  LG_ASSERT(became >= was, "Vecbase: BECAME index must not be below WAS");

  if (was == became)
    return;

  unsigned extend = became - was;

  if (_alloc_size < _size + extend)
    set_alloc_size(_size + extend);
  VEC_DUMP(this);

  size_t copying_size = (_size - was) * sizeof(arg_type *);

  char *buffer = new char[copying_size];
  memcpy(buffer, (void *)(&_data[was]), copying_size);
  memcpy((void *)(&_data[became]), buffer, copying_size);
  delete[] buffer;

  VEC_DUMP(this);
  memset((void *)(&_data[was]), 0, extend * sizeof(arg_type *));
  VEC_DUMP(this);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>
void iv_vecbase<arg_type>::insert(const arg_type &obj,
                                  const unsigned position) {

  CHECK_THIS;
  VEC_DUMP(this);
  CALL(_pull_apart(position, position + 1), "Vecbase: pulling apart failed");
  VEC_DUMP(this);
  _data[position] = new arg_type(obj);
  _size++;

  CHECK_THIS;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>
void iv_vecbase<arg_type>::insert(iv_vecbase &vec, const unsigned position) {
  CHECK_THIS;

  iv_vecbase<arg_type> pasting = vec;

  RT_ASSERT(pasting.ok() == true, "Argumented vecbase is invalid");
  unsigned new_position = position + pasting.size();
  CALL(_pull_apart(position, new_position), "Vecbase: pulling apart failed");

  for (int i = position; i < new_position; ++i) {
    pasting.dump(stdout);
    CALL(_data[i] = new arg_type(pasting[i - position]),
         "Vecbase: copying failed");
  }
  _size += pasting.size();

  dump(stdout);
  CHECK_THIS;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename arg_type>
void iv_vecbase<arg_type>::insert(const arg_type *obj, const unsigned amount,
                                  const unsigned position) {
  CHECK_THIS;
  unsigned new_position = position + amount;
  CALL(_pull_apart(position, new_position), "Vecbase: pulling apart failed");
  for (int i = position; i < new_position; ++i) {
    CALL(_data[i] = new arg_type(obj[i - position]), "Vecbase: copying failed");
  }
  _size += amount;
  dump(stdout);
  CHECK_THIS;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // VECTOR_INCLUDED
