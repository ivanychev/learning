#ifndef IV_ALLOC_INCLUDED
#define IV_ALLOC_INCLUDED
#include <algorithm>
#include <cstdint>
#include <vector>

struct ivAllocTable {
  struct ptr_meta {
    void *ptr;
    bool deleted = false;
    size_t size;

    ptr_meta(void *pointer, size_t alloc_size)
        : ptr(pointer), size(alloc_size), deleted(false){};
    ~ptr_meta() {
      ptr = NULL;
      deleted = false;
      size = 0;
    };
  };

  ivAllocTable(){};
  vector<ptr_meta> table;
  void sorted() {
    sort(table.begin(), table.end(), [](ptr_meta x, ptr_meta y) {
      return (uintptr_t)(x.ptr) < (uintptr_t)(y.ptr);
    });
  };

  int search(void *searched);
  void add(void *new_ptr, size_t size);
};

ivAllocTable AllocTable;

int ivAllocTable::search(void *searched) {
  int i = 0;
  int tsiz = table.size();
  while (((uintptr_t)table[i].ptr < (uintptr_t)searched) && (i < tsiz))
    ++i;
  if (i == tsiz)
    return -1;
  if ((uintptr_t)table[i].ptr == (uintptr_t)searched)
    return i;
  return -1;
}

void ivAllocTable::add(void *new_ptr, size_t new_size)

{
  int in_table = -1;
  if ((in_table = search(new_ptr)) != -1) {
    table[in_table].deleted = false;
    table[in_table].size = new_size;
    return;
  }

  table.push_back(ptr_meta(new_ptr, new_size));
  sorted();
}

void *operator new(std::size_t size);
void *operator new(std::size_t size, void *ptr) noexcept;
void operator delete(void *ptr) noexcept;
void operator delete(void *ptr, void *voidptr2) noexcept;

void *operator new(std::size_t size) {
  void *ret = calloc(1, size);
  if (ret == NULL)
    throw(bad_alloc());
  AllocTable.add(ret, size);

  AllocTable.add(ret, size);

  return ret;
}

void *operator new(std::size_t size, void *ptr) noexcept {
  void *ret = calloc(1, size);
  int in_table = -1;

  AllocTable.add(ret, size);
  return ret;
}

void operator delete(void *ptr) noexcept {
  int found = AllocTable.search(ptr);
  if (found == -1) {
    fprintf("Attmept to free memory, that hasn't been "
            "allocated.\nPointer:\t%08x\n Terminating...",
            ptr);
    getchar();
    abort();
  }
  if (AllocTable.table[found].deleted == true) {
    fprintf("Attmept to free memory, that has already been "
            "freed.\nPointer:\t%08x\n Terminating...",
            ptr);
    getchar();
    abort();
  }

  free(ptr);
  AllocTable.table[found].deleted == true;
}

void operator delete(void *ptr, void *voidptr2) noexcept { delete ptr; }

#endif // IV_ALLOC_INCLUDED
