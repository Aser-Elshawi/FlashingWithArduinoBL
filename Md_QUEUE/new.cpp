/*
 * new.cpp
 *
 *  Created on: Jan 30, 2024
 *      Author: aser_
 */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <new.h>

void *operator new(size_t size) {
  return malloc(size);
}

void *operator new[](size_t size) {
  return malloc(size);
}

void operator delete(void * ptr) {
  free(ptr);
}

void operator delete[](void * ptr) {
  free(ptr);
}



