#pragma once
#include <stdint.h>
#include <Epsilon/uefi/protocol/simple-file-system.h>
#include <Epsilon/uefi/protocol/file.h>
#include <Epsilon/sigma_loader.h>

typedef efi_handle sigma_file_t;

void init_sigma_file();
sigma_file_t* sigma_open_file(char16_t* name);
uint64_t sigma_read_file(sigma_file_t* file, uint64_t offset, uint64_t size, uint8_t* buf);
void sigma_close_file(sigma_file_t* file);
uint64_t sigma_get_file_size(sigma_file_t* file);