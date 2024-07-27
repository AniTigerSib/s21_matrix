#include "allocator_wrapper.h"

#include <dlfcn.h>

void *malloc(size_t __size) {
  void *result = NULL;
  void *(*libc_malloc)(size_t) = NULL;
  *(void **)(&libc_malloc) = dlsym(RTLD_NEXT, "malloc");
  if (!memory_locked(__size, 0)) result = libc_malloc(__size);
  return result;
}

void *calloc(size_t __nmemb, size_t __size) {
  void *result = NULL;
  void *(*libc_calloc)(size_t, size_t) = NULL;
  *(void **)(&libc_calloc) = dlsym(RTLD_NEXT, "calloc");
  if (!memory_locked(__size, 0)) result = libc_calloc(__nmemb, __size);
  return result;
}