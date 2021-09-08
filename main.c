
#include "efi.h"
#include "debug.h"
#include "memorymap.h"

struct EFI_SYSTEM_TABLE *ST;
struct EFI_BOOT_SERVICES *BS;
EFI_GUID gEfiBlockIoProtocolGuid;
EFI_GUID gEfiLoadedImageProtocolGuid;

void Halt(void){
    while (1) __asm__("hlt");
}

EFI_STATUS GetMemoryMap(struct MemoryMap* map,struct EFI_SYSTEM_TABLE *SystemTable){ 
    if(map->buffer == 0){
        return 1;
    }
    ST->ConOut->OutputString(ST->ConOut, L"GetMemoryMap\r\n");
    map->map_size = map->buffer_size;
    return SystemTable->BootServices->GetMemoryMap(
        &map->map_size,
        (struct EFI_MEMORY_DESCRIPTOR*)map -> buffer,
        &map->map_key,
        &map->descriptor_size,
        &map->descriptor_version);
}

EFI_STATUS OpenRootDir(EFI_HANDLE ImageHandle, struct EFI_FILE_PROTOCOL** root){
    EFI_STATUS status;
    struct EFI_LOADED_IMAGE_PROTOCOL* loaded_image;
    struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* fs;
    status = ST->BootServices->OpenProtocol(
        ImageHandle,
        &gEfiLoadedImageProtocolGuid,
        (VOID**)&loaded_image,
        ImageHandle,
        0,
        EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
    );
    if(status){
        retErrMsg(status);
        ST->ConOut->OutputString(ST->ConOut,msg);
        return status;
    }
    ST->ConOut->OutputString(ST->ConOut, L"OpenProtocol2\r\n");
    status = ST->BootServices->OpenProtocol(
        loaded_image->DeviceHandle,
        &gEfiSimpleFileSystemProtocolGuid,
        (VOID**)&fs,
        ImageHandle,
        0,
        EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL
    );
    if(status){
        retErrMsg(status);
        ST->ConOut->OutputString(ST->ConOut,msg);
        return status;
    }
    ST->ConOut->OutputString(ST->ConOut, L"OpenRootDir3 done\n");
    return fs->OpenVolume(fs, root);
}

CHAR8 memmap_buf[4096*4];

EFI_STATUS EfiMain (EFI_HANDLE ImageHandle,
                    struct EFI_SYSTEM_TABLE *SystemTable){
    EFI_STATUS status;
    ST = SystemTable;
    BS = SystemTable->BootServices;
    
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    //SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello UEFI!\n");
    ST->ConOut->OutputString(ST->ConOut, L"Hello UEFI!\n");

    struct MemoryMap memmap = {sizeof(memmap_buf), memmap_buf, 0, 0, 0, 0};
    status = GetMemoryMap(&memmap,SystemTable);
    if(status){
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Failed to open root directory\n");
        Halt();
    }
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"succcess open root directory\r\n");
    
    struct EFI_FILE_PROTOCOL* root_dir;
    status = OpenRootDir(ImageHandle, &root_dir);
    

    while(1);
    return EFI_SUCCESS;
}
