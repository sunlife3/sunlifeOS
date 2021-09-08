#ifndef _EFI_H_
#define _EFI_H_

#define IN
#define OUT
#define EFIAPI
//#define EFI_SUCCESS 0
#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL  0x00000001

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
typedef struct {
	UINT32 Data1; UINT16 Data2; UINT16 Data3; UINT8 Data4[8];
} EFI_GUID;

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

/////////////////// EFI_BOOT_SERVICES /////////////////
typedef UINT64  EFI_PHYSICAL_ADDRESS;
typedef UINT64  EFI_VIRTUAL_ADDRESS;
struct EFI_MEMORY_DESCRIPTOR {
	UINT32                Type; 
	EFI_PHYSICAL_ADDRESS  PhysicalStart;
	EFI_VIRTUAL_ADDRESS   VirtualStart;
	UINT64                NumberOfPages;
	UINT64                Attribute;
};

struct EFI_SYSTEM_TABLE{
	EFI_TABLE_HEADER                 Hdr;
	CHAR16                           *FirmwareVendor;
	UINT32                           FirmwareRivision;
	EFI_HANDLE                       ConsoleInHandle;
    struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    	unsigned long long _buf;
    	EFI_STATUS (*ReadKayStroke)(
    		struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
    		struct EFI_INPUT_KEY *ReadKey);
			void *WaitForKey;
	} *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
		unsigned long long _buf1;
		EFI_STATUS (*OutputString) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);
		EFI_STATUS _buf2[4];
		EFI_STATUS (*ClearScreen) (struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This);
	} *ConOut;
    unsigned long long _buf2[3]; //EFI_RUNTIME_SERVICES
    struct EFI_BOOT_SERVICES {
		EFI_TABLE_HEADER        Hdr;
		unsigned long long _buf[4];
		EFI_STATUS (*GetMemoryMap)(UINTN *MemoryMapSize, struct EFI_MEMORY_DESCRIPTOR *MemoryMap,
			UINTN *MapKey, UINTN *DescriptorSize, UINT32 *DescriptorVersion);
		unsigned long long _buf3[21];
		EFI_STATUS (*ExitBootServices)(EFI_HANDLE ImageHandle, UINTN Mapkey);
		unsigned long long _buf5[5];
		EFI_STATUS (*OpenProtocol)(EFI_HANDLE  Handle, EFI_GUID *Protocol,
			VOID **Interface,  EFI_HANDLE AgentHandle,
			EFI_HANDLE ControllerHandle, UINT32 Attributes);
		unsigned long long _buf6[4];
	} *BootServices;
};

/////////////////// EFI_LOADED_IMAGE_PROTOCOL /////////////////
struct EFI_LOADED_IMAGE_PROTOCOL{
	UINT32            Rivision;
	EFI_HANDLE        ParentHandle;
	struct EFI_SYSTEM_TABLE  *SystemTable;
	// Source location of the image
	EFI_HANDLE        DeviceHandle;
};

/////////////////// EFI_FILE_PROTOCOL /////////////////
struct EFI_FILE_PROTOCOL {
	UINT64          Rivision;
	EFI_STATUS (*Open)(struct EFI_FILE_PROTOCOL *This, struct EFI_FILE_PROTOCOL **NewHandle,
		CHAR16 *Filename, UINT64 OpenMode, UINT64 Attributes);
	EFI_STATUS (*Close)(struct EFI_FILE_PROTOCOL *This);
	EFI_STATUS (*Delete)(struct EFI_FILE_PROTOCOL *This);
	EFI_STATUS (*Read)(struct EFI_FILE_PROTOCOL *This,UINTN *BufferSize,VOID *Buffer);
	EFI_STATUS (*Write)(struct EFI_FILE_PROTOCOL *This,UINTN *BufferSize,VOID *Buffer);
	unsigned long long _buf[9];
};

////////////////// EFI_SIMPLE_FILE_SYSTEM_PROTOCOL /////////////////
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
	UINT64  Revision;
	EFI_STATUS (*OpenVolume)(
		struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This, struct EFI_FILE_PROTOCOL **Root);
};

unsigned short *msg;
extern EFI_GUID gEfiBlockIoProtocolGuid;
EFI_GUID gEfiLoadedImageProtocolGuid = {0x5B1B31A1,0x9562,0x11d2,{0x8E,0x3F,0x00,0xA0,0xC9,0x69,0x72,0x3B}};
EFI_GUID gEfiSimpleFileSystemProtocolGuid = {0x0964e5b22,0x6459,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}};
#endif