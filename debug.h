#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "efi.h"

#define EFI_SUCCESS 	          0x0
#define EFI_LOAD_ERROR 	          0x8000000000000001
#define EFI_INVALID_PARAMETER 	  0x8000000000000002
#define EFI_UNSUPPORTED 	      0x8000000000000003
#define EFI_BAD_BUFFER_SIZE 	  0x8000000000000004
#define EFI_BUFFER_TOO_SMALL 	  0x8000000000000005
#define EFI_NOT_READY 	          0x8000000000000006
#define EFI_DEVICE_ERROR 	      0x8000000000000007
#define EFI_WRITE_PROTECTED 	  0x8000000000000008
#define EFI_OUT_OF_RESOURCES 	  0x8000000000000009
#define EFI_VOLUME_CORRUPTED 	  0x800000000000000a
#define EFI_VOLUME_FULL 	      0x800000000000000b
#define EFI_NO_MEDIA 	          0x800000000000000c
#define EFI_MEDIA_CHANGED 	      0x800000000000000d
#define EFI_NOT_FOUND 	          0x800000000000000e
#define EFI_ACCESS_DENIED 	      0x800000000000000f
#define EFI_NO_RESPONSE 	      0x8000000000000010
#define EFI_NO_MAPPING 	          0x8000000000000011
#define EFI_TIMEOUT 	          0x8000000000000012
#define EFI_NOT_STARTED 	      0x8000000000000013
#define EFI_ALREADY_STARTED 	  0x8000000000000014
#define EFI_ABORTED 	          0x8000000000000015
#define EFI_ICMP_ERROR 	          0x8000000000000016
#define EFI_TFTP_ERROR 	          0x8000000000000017
#define EFI_PROTOCOL_ERROR 	      0x8000000000000018
#define EFI_INCOMPATIBLE_VERSION  0x8000000000000019
#define EFI_SECURITY_VIOLATION 	  0x800000000000001a
#define EFI_CRC_ERROR 	          0x800000000000001b
#define EFI_END_OF_MEDIA 	      0x800000000000001c
#define EFI_END_OF_FILE 	      0x800000000000001f
#define EFI_INVALID_LANGUAGE 	  0x8000000000000020
#define EFI_COMPROMISED_DATA 	  0x8000000000000021
#define EFI_HTTP_ERROR 	          0x8000000000000023
#define EFI_NETWORK_UNREACHABLE   0x8000000000000064
#define EFI_HOST_UNREACHABLE 	  0x8000000000000065
#define EFI_PROTOCOL_UNREACHABLE  0x8000000000000066
#define EFI_PORT_UNREACHABLE 	  0x8000000000000067
#define EFI_CONNECTION_FIN 	      0x8000000000000068
#define EFI_CONNECTION_RESET 	  0x8000000000000069
#define EFI_CONNECTION_REFUSED 	  0x800000000000006a
#define EFI_WARN_UNKNOWN_GLYPH 	  0x1
#define EFI_WARN_DELETE_FAILURE   0x2
#define EFI_WARN_WRITE_FAILURE 	  0x3
#define EFI_WARN_BUFFER_TOO_SMALL 0x4
#define EFI_WARN_STALE_DATA 	  0x5
#define EFI_WARN_FILE_SYSTEM 	  0x6 

void retErrMsg(unsigned long long errCode){
    switch(errCode){
        case 0x0:
            msg = L"SUCCESS";
            break;
        case 0x8000000000000001:
            msg = L"LOAD_ERROR";
            break; 
        case 0x8000000000000002:
            msg = L"INVALID_PARAMETER";
            break;
        case 0x8000000000000003:
            msg = L"UNSUPPORTED";
            break;
        case 0x8000000000000004:
            msg = L"BAD_BUFFER_SIZE";
            break;
        case 0x8000000000000005:
            msg = L"BUFFER_TOO_SMALL";
            break;
        case 0x8000000000000006:
            msg = L"NOT_READY";
            break;
        case 0x8000000000000007:
            msg = L"DEVICE_ERROR";
            break;
        case 0x8000000000000008:
            msg = L"WRITE_PROTECTED";
            break;
        case 0x8000000000000009:
            msg = L"OUT_OF_RESOURCE";
            break;
        case 0x800000000000000a:
            msg = L"VOLUME_CORRUPTED";
            break;
        case 0x800000000000000b:
            msg = L"VOLUME_FULL";
            break;
        case 0x800000000000000c:
            msg = L"NO_MEDIA";
            break;
        case 0x800000000000000d:
            msg = L"MEDIA_CHANGED";
            break;
        case 0x800000000000000e:
            msg = L"NOT_FOUND";
            break;
        case 0x800000000000000f:
            msg = L"ACCESS_DENIED";
            break;
        case 0x8000000000000010:
            msg = L"NO_RESPONSE";
            break;
        case 0x8000000000000011:
            msg = L"NO_MAPPING";
            break;
        case 0x8000000000000012:
            msg = L"TIMEOUT";
            break;
        case 0x8000000000000013:
            msg = L"NOT_STARTED";
            break;
        case 0x8000000000000014:
            msg = L"ALREADY_STARTED";
            break;
        case 0x8000000000000015:
            msg = L"ABORTED";
            break;
        case 0x8000000000000016:
            msg = L"ICMP_ERROR";
            break;
        case 0x8000000000000017:
            msg = L"TFTP_ERROR";
            break;
        case 0x8000000000000018:
            msg = L"PROTOCOL_ERROR";
            break;
        case 0x8000000000000019:
            msg = L"INCOMPATIBLE_VERSION";
            break;
        case 0x800000000000001a:
            msg = L"SECURITY_VIOLATION";
            break;
        case 0x800000000000001b:
            msg = L"CRC_ERROR";
            break;
        case 0x800000000000001c:
            msg = L"END_OF_MEDIA";
            break;
        case 0x800000000000001f:
            msg = L"END_OF_FILE";
            break;
        case 0x8000000000000020:
            msg = L"INVALID_LANGUADE";
            break;
        case 0x8000000000000021:
            msg = L"COMPROMISED_DATA";
            break;
        case 0x8000000000000022:
            msg = L"IP_ADDRESS_CONFLICT";
            break;
        case 0x8000000000000023:
            msg = L"HTTP_ERROR";
            break;
        default:
            msg = L"other error";
    }
}
 

#endif