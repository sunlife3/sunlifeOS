#include "efi.h"
#include "debug.h"
#include "common.h"
#include "mem.h"

void Halt(void){
    while (1) __asm__("hlt");
}

EFI_STATUS getMemoryMap(struct MemoryMap* map, struct EFI_SYSTEM_TABLE *SystemTable){ 
    if(map->buffer == 0){
        return 1;
    }
    //ST->ConOut->OutputString(ST->ConOut, L"GetMemoryMap\r\n");
    map->map_size = map->buffer_size;
    return SystemTable->BootServices->GetMemoryMap(
        &map->map_size,
        (struct EFI_MEMORY_DESCRIPTOR *)map -> buffer,
        &map->map_key,
        &map->descriptor_size,
        &map->descriptor_version);
}

EFI_STATUS SaveMemoryMap(struct MemoryMap* map, struct EFI_FILE_PROTOCOL* file){
    EFI_STATUS status=0;
    //CHAR8 buf[256];
    UINTN len;

    CHAR8* header = "Index, Type, Type(name), PhysicalStart, NumberOfPages, Attribute\n";
    len = charStrLen (header);
    file -> Write(file, &len, header);
    dump_memmap(map);
    //ST->ConOut->OutputString(ST->ConOut,L"written");
    // TO BE IMPLEMENTED :: SAVE MEMORYMAP (referense osbook02b)
    return status;
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
    return fs->OpenVolume(fs, root);
}

EFI_STATUS EfiMain (EFI_HANDLE ImageHandle,
                    struct EFI_SYSTEM_TABLE *SystemTable){
    EFI_STATUS status;
    ST = SystemTable;
    BS = SystemTable->BootServices;
    
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    ST->ConOut->OutputString(ST->ConOut, L"Hello UEFI!\r\n");

    CHAR8 memmap_buf[4096 * 4];
    struct MemoryMap memmap = {sizeof(memmap_buf), memmap_buf, 0, 0, 0, 0};
    status = getMemoryMap(&memmap, SystemTable);
    if(status){
        ST->ConOut->OutputString(ST->ConOut, L"Failed to get memory map\r\n");
        Halt();
    }else{
        ST->ConOut->OutputString(ST->ConOut, L"GetMemoryMap Status: 0\r\n");
    }
    
    struct EFI_FILE_PROTOCOL* root_dir;
    status = OpenRootDir(ImageHandle, &root_dir);
    if(status){
        retErrMsg(status);
        ST->ConOut->OutputString(ST->ConOut, L"Failed to open root directory\n");
        ST->ConOut->OutputString(ST->ConOut, msg);
        Halt();
    }

    struct EFI_FILE_PROTOCOL* memmap_file;
    status = root_dir->Open(
      root_dir, &memmap_file, L"\\memmap",
      EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0);
    if(status){
        retErrMsg(status);
        ST->ConOut->OutputString(ST->ConOut, L"Failed to open '\\memmap'\n");
        ST->ConOut->OutputString(ST->ConOut, msg);
        Halt();
    }
    //SaveMemoryMap(&memmap, memmap_file);
    status = memmap_file->Close(memmap_file);
    //ST->ConOut->OutputString(ST->ConOut, L"CLOSED");
    

    //loading kernel
    struct EFI_FILE_PROTOCOL* kernel_file;
    root_dir->Open(
        root_dir, &kernel_file, L"\\kernel.elf" , EFI_FILE_MODE_READ, 0);
    if(status){
        retErrMsg(status);
        ST->ConOut->OutputString(ST->ConOut, L"[FAILED] root_dir -> Open: ");
        ST->ConOut->OutputString(ST->ConOut, msg);
        Halt();
    }else{
        ST->ConOut->OutputString(ST->ConOut, L"[SUCCESS] root_dir -> Open: \r\n");
    }

    UINTN file_info_size = sizeof(EFI_FILE_INFO) + sizeof(CHAR16) * 12;
    UINT8 file_info_buffer[file_info_size];
    status = kernel_file->GetInfo(kernel_file, &gEfiFileInfoGuid, &file_info_size, file_info_buffer);
    if(status){
        retErrMsg(status);
        ST->ConOut->OutputString(ST->ConOut, L"[FAILED] kernel_file -> GetInfo: ");
        ST->ConOut->OutputString(ST->ConOut, msg);
        Halt();
    }else{
        ST->ConOut->OutputString(ST->ConOut, L"[SUCCESS] kernel_file -> GetInfo\r\n");
    }

    EFI_FILE_INFO* file_info = (EFI_FILE_INFO*)file_info_buffer;
    UINTN kernel_file_size = file_info->FileSize;
    EFI_PHYSICAL_ADDRESS kernel_base_addr = 0x100000;
    status = BS -> AllocatePages(AllocateAddress, EfiLoaderData, (kernel_file_size + 0xfff)/0x1000, &kernel_base_addr);
    if(status){
        retErrMsg(status);
        ST->ConOut->OutputString(ST->ConOut, L"[FAILED] AllocatePages: ");
        ST->ConOut->OutputString(ST->ConOut, msg);
        Halt();
    }else{
        ST->ConOut->OutputString(ST->ConOut, L"[SUCCESS] AllocatePages\r\n");
    }
    ST->ConOut->OutputString(ST->ConOut, L"at Read:");
    status = kernel_file->Read(kernel_file, &kernel_file_size, (VOID*)kernel_base_addr);
    if(status){
        retErrMsg(status);
        ST->ConOut->OutputString(ST->ConOut, L"at Read:");
        ST->ConOut->OutputString(ST->ConOut, msg);
        Halt();
    }else{
        ST->ConOut->OutputString(ST->ConOut, L"kernelfile->Read DONE\r\n");
    }

    ST->ConOut->OutputString(ST->ConOut,L"DONE");

    while(1);
    return EFI_SUCCESS;
}
