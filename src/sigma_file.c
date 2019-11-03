#include <Epsilon/sigma_file.h>

efi_simple_file_system_protocol* simple_file_system;
efi_file_protocol* root = 0;
efi_system_table* st;

void init_sigma_file(){
    st = get_system_table();
    efi_status status;
    efi_guid guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
    status = st->BootServices->LocateProtocol(&guid, NULL, (void**)&simple_file_system);
    if(EFI_ERROR(status)){
        st->ConOut->OutputString(st->ConOut, L"Failed locating Simple Filesystem Protocol");
        return;
    }
    status = simple_file_system->OpenVolume(simple_file_system, &root);
    if(EFI_ERROR(status)){
        st->ConOut->OutputString(st->ConOut, L"Failed to open volume");
        return;
    }
}

sigma_file_t* sigma_open_file(char16_t* name){
    efi_handle* file;
    efi_status status;
    
    status = root->Open(root, &file, name, EFI_FILE_MODE_READ, 0);
    if(EFI_ERROR(status)){
        st->ConOut->OutputString(st->ConOut, L"Failed to open file");
        return NULL;
    }

    return (sigma_file_t*)file;
}

uint64_t sigma_read_file(sigma_file_t* file, uint64_t offset, uint64_t size, uint8_t* buf){
    efi_handle* efi_file = (efi_handle*)file;

    efi_status status;

    status = root->SetPosition(efi_file, offset);
    if(EFI_ERROR(status)){
        st->ConOut->OutputString(st->ConOut, L"Failed to seek file");
        return 0;
    }

    
    status = root->Read(efi_file, &size, (void*)buf);
    if(EFI_ERROR(status)){
        st->ConOut->OutputString(st->ConOut, L"Failed to read file");
        return 0;
    }

    return size;
}

void sigma_close_file(sigma_file_t* file){
    efi_handle* efi_file = (efi_handle*)file;

    efi_status status;

    status = root->Close(efi_file);
    if(EFI_ERROR(status)){
        st->ConOut->OutputString(st->ConOut, L"Failed to close file");
        return;
    }
}

uint64_t sigma_get_file_size(sigma_file_t* file){
    efi_handle* efi_file = (efi_handle*)file;

    efi_status status;
    uint64_t size = sizeof(efi_file_info) + 100;
    void* buf = AllocatePool(size);
    efi_guid g = EFI_FILE_INFO_GUID;
    
    status = root->GetInfo(efi_file, &g, &size, buf);
    if(EFI_ERROR(status)){
        st->ConOut->OutputString(st->ConOut, L"Failed to get file data file");
        return 0;
    }

    efi_file_info* f = buf;
    uint64_t ret = f->FileSize;
    FreePool(buf);
}