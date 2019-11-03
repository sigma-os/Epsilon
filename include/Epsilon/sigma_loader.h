#pragma once

#include <Epsilon/uefi/types.h>
#include <Epsilon/uefi/runtime-services.h>
#include <Epsilon/uefi/system-table.h>
#include <Epsilon/uefi/boot-services.h>
#include <stdint.h>

typedef struct {
    uint64_t* mmap;
    uint64_t* mmap_end;
    uint64_t memorySize;
    uint64_t* acpiPointer;
} sigma_booted_header_t;

efi_system_table* get_system_table();