
#include "efi.h"
#include "memorymap.h"

struct EFI_SYSTEM_TABLE *ST;

void Halt(void){
    while (1) __asm__("hlt");
}


EFI_STATUS GetMemoryMap(struct MemoryMap* map,struct EFI_SYSTEM_TABLE *SystemTable){ 
    if(map->buffer == 0){
        return 1;
    }
    ST->ConOut->OutputString(ST->ConOut, L"GetMemoryMap\n");
    map->map_size = map->buffer_size;
    return SystemTable->BootServices->GetMemoryMap(
        &map->map_size,
        (struct EFI_MEMORY_DESCRIPTOR*)map -> buffer,
        &map->map_key,
        &map->descriptor_size,
        &map->descriptor_version);
}

/*EFI_STATUS OpenRootDir(EFI_HANDLE ImageHandle, EFI_FILE_PROTOCOL** root){
    EFI_STATUS status;
    EFI_LOADED_IMAGE_PROTOCOL* loaded_image;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fs;
}*/

CHAR8 memmap_buf[4096*4];

EFI_STATUS EfiMain (EFI_HANDLE ImageHandle,
                    struct EFI_SYSTEM_TABLE *SystemTable){
    EFI_STATUS status;
    ST = SystemTable;
    
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    //SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello UEFI!\n");
    ST->ConOut->OutputString(ST->ConOut, L"Hello UEFI!\n");

    struct MemoryMap memmap = {sizeof(memmap_buf), memmap_buf, 0, 0, 0, 0};
    status = GetMemoryMap(&memmap,SystemTable);
    if(status){
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Failed to open root directory\n");
        Halt();
    }
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"succcess open root directory\n");
    
    //EFI_FILE_PROTOCOL* root_dir;
    //status OpenRootDir(ImageHandle, &root_dir);

    while(1);
    return EFI_SUCCESS;
}
