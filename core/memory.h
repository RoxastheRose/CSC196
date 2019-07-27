#pragma once
#include <iostream>
#include <assert.h>
void* operator new (size_t size);

void operator delete (void* ptr, size_t size);