build: main.c
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
	ld.lld --entry KernelMain -z norelro --image-base 0x10000 --static \
	       -o kernel.elf kernel.o
	mv kernel.elf fs/

qemu: fs/EFI/BOOT/BOOTX64.EFI
#	qemu-system-x86_64 -bios OVMF.fd -hda fat:rw:fs
#	qemu-system-x86_64 -hda fat:rw:fs
	qemu-system-x86_64 -m 4G -drive dir=./fs,driver=vvfat,rw=on \
	-drive if=pflash,format=raw,readonly=on,file=./ovmf/OVMF_CODE.fd \
	-drive if=pflash,format=raw,file=./ovmf/OVMF_VARS.fd

clean:
	rm -f main.efi
