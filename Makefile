build: main.c efi.h
	clang -target x86_64-pc-win32-coff \
		  -fno-stack-protector -fshort-wchar \
		  -nostdlibinc\
		  -mno-red-zone -Wall\
		  -c main.c
	lld-link -subsystem:efi_application -nodefaultlib -dll\
			 -entry:EfiMain -out:main.efi main.o
	mv main.efi fs/EFI/BOOT/BOOTX64.EFI

buildgcc: main.c efi.h
	x86_64-w64-mingw32-gcc -Wall -Wextra -e EfiMain -nostdinc -nostdlib \
    -fno-builtin -fno-common -Wl,--subsystem,10 -o main.efi main.c 
	mv main.efi fs/EFI/BOOT/BOOTX64.EFI

kernel: kernel.cpp
	clang++ -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone \
	        -fno-exceptions -fno-rtti -std=c++17 -c kernel.cpp
	ld.lld --entry KernelMain -z norelro --image-base 0x100000 --static \
	       -o kernel.elf kernel.o
	mv kernel.elf fs/

qemu: OVMF.fd fs/EFI/BOOT/BOOTX64.EFI
	qemu-system-x86_64 -bios OVMF.fd -hda fat:rw:fs

clean:
	rm -f main.efi
