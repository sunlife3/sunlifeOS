
#include "efi.h"
#include "memorymap.h"

EFI_SYSTEM_TABLE *gST;
EFI_BOOT_SERVICES *gBS;

void Halt(void){
    while (1) __asm__("hlt");
}


EFI_STATUS GetMemoryMap(struct MemoryMap* map,EFI_SYSTEM_TABLE *SystemTable){ 
    if(map->buffer == 0){
        return 1;
    }
    map->map_size = map->buffer_size;
    return SystemTable->BootServices->GetMemoryMap(
        &map->map_size,
        (EFI_MEMORY_DESCRIPTOR*)map -> buffer,
        &map->map_key,
        &map->descriptor_size,
        &map->descriptor_version);
}

CHAR8 memmap_buf[4096*4];

EFI_STATUS EfiMain (EFI_HANDLE ImageHandle,
                    EFI_SYSTEM_TABLE *SystemTable){
    EFI_STATUS status;
    
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello UEFI!\n");
    
    struct MemoryMap memmap = {sizeof(memmap_buf), memmap_buf, 0, 0, 0, 0};
    status = GetMemoryMap(&memmap,SystemTable);
    if(status){
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Failed to open root directory\n");
        Halt();
    }
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"succcess open root directory\n");
    while(1);
    return EFI_SUCCESS;
}
