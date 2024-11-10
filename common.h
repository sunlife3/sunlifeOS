#include "efi.h"

#ifndef _COMMON_H_
#define _COMMON_H_

#define MAX_STRING_BUFFER 100

unsigned int charStrLen (char *String){
  unsigned int len;
  for (len = 0; *String != '\0'; String++) {
      len++;
  }
  return len;
}

void puts(unsigned short *s){
	ST->ConOut->OutputString(ST->ConOut, s);
}

void puth(unsigned long long val, unsigned char num_digits){
	unsigned short unicode_val;
	unsigned short str[MAX_STRING_BUFFER];

	for (int i = num_digits - 1; 0 <= i; i--) {
		unicode_val = (unsigned short)(val & 0x0f);
		if (unicode_val < 0xa)
			str[i] = L'0' + unicode_val;
		else
			str[i] = L'A' + (unicode_val - 0xa);
		val >>= 4;
	}
	str[num_digits] = L'\0';

	puts(str);
}



#endif