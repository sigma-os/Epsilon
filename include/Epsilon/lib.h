#pragma once

#include <stdint.h>
#include <Epsilon/sigma_loader.h>

void* AllocatePool(uint64_t size);
void FreePool(void* ptr);