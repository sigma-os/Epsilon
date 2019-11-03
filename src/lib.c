#include <Epsilon/lib.h>

void* AllocatePool(uint64_t size){
    void* buf = NULL;
    efi_status status = get_system_table()->BootServices->AllocatePool(EfiLoaderData, size, &buf);
    if(EFI_ERROR(status)){
        get_system_table()->ConOut->OutputString(get_system_table()->ConOut, "Failed to allocate pool");
        return NULL;
    }
    return buf;
}

void FreePool(void* ptr){
    efi_status status = get_system_table()->BootServices->FreePool(ptr);
    if(EFI_ERROR(status)){
        get_system_table()->ConOut->OutputString(get_system_table()->ConOut, "Failed to free pool");     
    }
}