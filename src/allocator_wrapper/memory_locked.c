#include "allocator_wrapper.h"

int memory_locked(size_t size, int locked) {
  static size_t value = 0;
  int result = 0;
  if (locked == 1) value = size;
  if (locked == -1) value = 0;
  if (locked == 0 && value == size) result = 1;
  return result;
}