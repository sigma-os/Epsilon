#include <Epsilon/sigma_graphics.h>

efi_graphics_output_protocol* graphics;
efi_graphics_output_mode_information** modes;
uint64_t* mode_sizes;

void init_sigma_graphics(){
    efi_system_table* st = get_system_table();

    efi_status status;
    efi_guid guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    status = st->BootServices->LocateProtocol(&guid, NULL, (void**)&graphics);
    if(EFI_ERROR(status)){
        st->ConOut->OutputString(st->ConOut, L"Failed locating GOP");
        return;
    }

    modes = AllocatePool(sizeof(efi_graphics_output_mode_information*) * (graphics->Mode->MaxMode));
    mode_sizes = AllocatePool(sizeof(uint64_t) * graphics->Mode->MaxMode);

    for(uint64_t i = 0; i < graphics->Mode->MaxMode; i++){
        mode_sizes[i] = sizeof(efi_graphics_output_mode_information);
        status = graphics->QueryMode(graphics, i, &(mode_sizes[i]), &(modes[i]));
        if(EFI_ERROR(status)){
            st->ConOut->OutputString(st->ConOut, L"Failed locating Mode");
            return;
        }
    }

    /*for(UINTN i = 0; i < graphics->Mode->MaxMode; i++){
        Print(L"%d, %d ", modes[i]->HorizontalResolution, modes[i]->VerticalResolution);
        if((i % 4) == 0) Print(L"\n");
    }*/
}

void sigma_set_video_mode(uint64_t width, uint64_t height){
    efi_system_table* st = get_system_table();
    efi_status status;

    for(uint64_t i = 0; i < graphics->Mode->MaxMode; i++){
        if(modes[i]->HorizontalResolution == width && modes[i]->VerticalResolution == height){
            status = graphics->SetMode(graphics, i);
            if(EFI_ERROR(status)){
                st->ConOut->OutputString(st->ConOut, L"Failed setting mode");
                return;
            }
        }
    }

    st->ConOut->OutputString(st->ConOut, L"Failed requested setting requested mode setting mode 0");
    status = graphics->SetMode(graphics, 0);
    if(EFI_ERROR(status)){
        st->ConOut->OutputString(st->ConOut, L"Failed setting mode 0");
        return;
    }
}

void* sigma_get_framebuffer(){
    return (void*)graphics->Mode->FrameBufferBase;
}

size_t sigma_get_framebuffer_size(){
    return graphics->Mode->FrameBufferSize;
}