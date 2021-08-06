
#include "efi.h"
#include "memorymap.h"

EFI_SYSTEM_TABLE *gST;
EFI_BOOT_SERVICES *gBS;


EFI_STATUS GetMemoryMap(struct MemoryMap* map){
    if(map->buffer == 0){
        return 1;
    }
    map->map_size = map->buffer_size;
    return gBS->GetMemoryMap(
        &map->map_size,
        (EFI_MEMORY_DESCRIPTOR*)map -> buffer,
        &map->map_key,
        &map->descriptor_size,
        &map->descriptor_version);
}


EFI_STATUS EfiMain (EFI_HANDLE ImageHandle,
                    EFI_SYSTEM_TABLE *SystemTable){
    EFI_STATUS status;

    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello UEFI!\n");
    
    //char memmap_buf[8000];
    //int a[1];
    //struct nMemoryMap memmap = {sizeof(memmap_buf), memmap_buf, 0, 0, 0, 0};
    //status = GetMemoryMap(&memmap);

    while(1);
    return EFI_SUCCESS;
}
