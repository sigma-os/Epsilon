#include <Epsilon/uefi/types.h>
#include <Epsilon/uefi/runtime-services.h>
#include <Epsilon/uefi/system-table.h>
#include <Epsilon/uefi/boot-services.h>

#include <stdint.h>
#include <Epsilon/sigma_loader.h>
#include <Epsilon/sigma_file.h>
#include <Epsilon/sigma_graphics.h>


sigma_booted_header_t sigma_header;
efi_system_table* st;

efi_status efi_main(efi_handle ImageHandle, efi_system_table *SystemTable)
{
    SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, NULL);
    st = SystemTable;

    st->ConOut->OutputString(st->ConOut, L"Booting Epsilon");

    (void)(ImageHandle);

    init_sigma_file();
    init_sigma_graphics();

    while(1);

    return EFI_SUCCESS;
}

efi_system_table* get_system_table(){
    return st;
}