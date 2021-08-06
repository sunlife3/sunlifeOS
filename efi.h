#ifndef _EFI_H_
#define _EFI_H_

#define IN
#define OUT
#define EFIAPI
#define EFI_SUCCESS 0

typedef char                BOOLEAN;
typedef int                 INTN;
typedef unsigned int        UINTN;
typedef char                INT8;
typedef unsigned char       UINT8;
typedef short               INT16;
typedef unsigned short      UINT16;
typedef long                INT32;
typedef unsigned long       UINT32;
typedef long long           INT64;
typedef unsigned long long  UINT64;
typedef char                CHAR8;
typedef unsigned short      CHAR16;
typedef void                VOID;
typedef unsigned long long  EFI_STATUS;
typedef VOID*               EFI_HANDLE;
typedef VOID*               EFI_EVENT;
typedef UINT64              EFI_LBA;
typedef UINTN               EFI_TPL;

struct  EFI_INPUT_KEY;
struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
struct _EFI_FILE_PROTOCOL;

typedef EFI_STATUS (*EFI_INPUT_READ_KEY)(
    IN struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
    OUT struct EFI_INPUT_KEY *ReadKey,
    void *WaitForKey
    );

typedef struct {
	UINT64 Signature;
	UINT32 Rivision;
	UINT32 HeaderSize;
	UINT32 CRC32;
	UINT32 Reserved;
} EFI_TABLE_HEADER;

struct EFI_INPUT_KEY {
	unsigned short ScanCode;
	unsigned short UnicodeChar;
};

typedef struct _EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    unsigned long long _buf;
    EFI_INPUT_READ_KEY ReadKeyStroke;
    void *WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;


////////// EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL ////////////
typedef EFI_STATUS (*EFI_TEXT_STRING) (
    IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
    CHAR16                                   *String
    );
typedef EFI_STATUS (*EFI_TEXT_CLEAR_SCREEN) (
    IN struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This
    );
typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    void             *a;
    EFI_TEXT_STRING  OutputString;
    EFI_STATUS _buf2[4];
    EFI_TEXT_CLEAR_SCREEN ClearScreen;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;


/////////////////// EFI_BOOT_SERVICES /////////////////
typedef EFI_TPL (*EFI_RAISE_TPL)(IN EFI_TPL NewTpl);
typedef VOID (*EFI_RESTORE_TPL)(IN EFI_TPL OldTpl);
typedef enum {
	AllocateAnyPages, AllocateMaxAddress, AllocateAddress, MaxAllocateType
} EFI_ALLOCATE_TYPE;
typedef enum {
    EfiReservedMemoryType, EfiLoaderCode, EfiLoaderData, EfiBootServicesCode,
    EfiBootServicesData, EfiRuntimeServicesCode, EfiRuntimeServicesData, EfiConventionalMemory,
    EfiUnusableMemory, EfiACPIReclaimMemory, EfiACPIMemoryNVS, EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace, EfiPalCode, EfiPersistentMemory, EfiUnacceptedMemoryType, EfiMaxMemoryType
} EFI_MEMORY_TYPE;
typedef UINT64  EFI_PHYSICAL_ADDRESS;
typedef EFI_STATUS (*EFI_ALLOCATE_PAGES)(IN EFI_ALLOCATE_TYPE  Type,
			IN EFI_MEMORY_TYPE MemoryType, IN UINTN Pages, IN OUT EFI_PHYSICAL_ADDRESS *Memory);
typedef EFI_STATUS (*EFI_FREE_PAGES)(IN EFI_PHYSICAL_ADDRESS Memory, IN UINTN Pages);
typedef UINT64  EFI_VIRTUAL_ADDRESS;
typedef struct {
	UINT32                Type; 
	EFI_PHYSICAL_ADDRESS  PhysicalStart;
	EFI_VIRTUAL_ADDRESS   VirtualStart;
	UINT64                NumberOfPages;
	UINT64                Attribute;
} EFI_MEMORY_DESCRIPTOR;
typedef EFI_STATUS (*EFI_GET_MEMORY_MAP)(IN OUT UINTN *MemoryMapSize, IN OUT EFI_MEMORY_DESCRIPTOR *MemoryMap,
			OUT UINTN *MapKey, OUT UINTN *DescriptorSize, OUT UINT32 *DescriptorVersion);


typedef struct _EFI_BOOT_SERVICES {
    EFI_TABLE_HEADER        Hdr;
	// Task Priority Services
	EFI_RAISE_TPL           RaiseTPL;
	EFI_RESTORE_TPL         RestoreTPL;         
	// Memory Services
	EFI_ALLOCATE_PAGES      AllocatePages;
	EFI_FREE_PAGES          FreePages;
	EFI_GET_MEMORY_MAP      GetMemoryMap;
	unsigned long long _buf3[2];
	//
	// Event & Timer Services
	//
	unsigned long long _buf4[6];
	//
	// Protocol Handler Services
	//
	unsigned long long _buf5[9];
	//
	// Image Services
	//
	unsigned long long _buf6[5];
	//
	// Miscellaneous Services
	//
	unsigned long long _buf7[3];
	//
	// DriverSupport Services
	//
	unsigned long long _buf8[2];
	//
	// Open and Close Protocol Services
	//
	unsigned long long _buf9[3];
	//
	// Library Services
	//
	unsigned long long _buf10[5];
	//
	// 32-bit CRC Services
	//
	unsigned long long _buf11;
	//
	// Miscellaneous Services
	//
	unsigned long long _buf12[3];
} EFI_BOOT_SERVICES;

/////////////////// EFI_FILE_PROTOCOL /////////////////
typedef EFI_STATUS (*EFI_FILE_OPEN)(IN struct _EFI_FILE_PROTOCOL *This, OUT struct _EFI_FILE_PROTOCOL **NewHandle,
		IN CHAR16 *Filename, IN UINT64 OpenMode, IN UINT64 Attributes);
typedef EFI_STATUS (*EFI_FILE_CLOSE)(IN struct _EFI_FILE_PROTOCOL *This);
typedef EFI_STATUS (*EFI_FILE_DELETE)(IN struct _EFI_FILE_PROTOCOL *This);
typedef EFI_STATUS (*EFI_FILE_READ)(IN struct _EFI_FILE_PROTOCOL *This, IN OUT UINTN *BufferSize, OUT VOID *Buffer);
typedef EFI_STATUS (*EFI_FILE_WRITE)(IN struct _EFI_FILE_PROTOCOL *This, IN OUT UINTN *BufferSize, IN VOID *Buffer);
typedef struct _EFI_FILE_PROTOCOL {
	UINT64          Rivision;
	EFI_FILE_OPEN   Open;
	EFI_FILE_CLOSE  Close;
	EFI_FILE_DELETE Delete;
	EFI_FILE_READ   Read;
	EFI_FILE_WRITE  Write;
	unsigned long long _buf[9];
} EFI_FILE_PROTOCOL;


typedef struct {
	EFI_TABLE_HEADER                 Hdr;
	CHAR16                           *FirmwareVendor;
	UINT32                           FirmwareRivision;
	EFI_HANDLE                       ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *ConIn;
    EFI_HANDLE                       ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *ConOut;
    unsigned long long _buf2[3]; //EFI_RUNTIME_SERVICES
    EFI_BOOT_SERVICES                *BootServices;
} EFI_SYSTEM_TABLE;

#endif