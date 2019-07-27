#include "memory.h"
#include "heap.h"

#include <iostream>

heap g_mainHeap;

void* operator new (size_t size)
{
	return g_mainHeap.allocate(size);
}

void operator delete (void* ptr, size_t size)
{
	g_mainHeap.free(ptr);
}