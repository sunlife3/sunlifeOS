#include "efi.h"
#include "common.h"

#ifndef _MEM_H_
#define _MEM_H_

#define PAGE_SIZE	4096

void dump_memmap(struct MemoryMap* map){

    struct EFI_MEMORY_DESCRIPTOR *p =  (struct EFI_MEMORY_DESCRIPTOR *) map -> buffer;
	ST->ConOut->OutputString(ST->ConOut,L"written");
    unsigned int mem_desc_num;
	mem_desc_num = 20;//map->map_size / map->descriptor_size;
	ST->ConOut->OutputString(ST->ConOut,L"written2");
    for(int i=0; i < map->descriptor_size; i++){
        puth((unsigned long long)p, 16);
		//putc(L' ');
		puth(p->Type, 2);
		//putc(L' ');
		puth(p->PhysicalStart, 16);
		//putc(L' ');
		puth(p->VirtualStart, 16);
		//putc(L' ');
		puth(p->NumberOfPages, 16);
		//putc(L' ');
		puth(p->Attribute, 16);
		puts(L"\r\n");

		p = (struct EFI_MEMORY_DESCRIPTOR *)(
			(unsigned char *)p + map -> descriptor_size);
    }
}

#endif

