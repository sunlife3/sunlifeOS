#ifndef _MEMORYMAP_
#define _MEMORYMAP_

struct MemoryMap{
    unsigned int buffer_size;
    void* buffer;
    unsigned int map_size;
    unsigned int map_key;
    unsigned int descriptor_size;
    unsigned long descriptor_version;
};

#endif