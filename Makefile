build: main.c efi.h
	clang -target x86_64-pc-win32-coff \
		  -fno-stack-protector -fshort-wchar \
		  -mno-red-zone -Wall\
		  -c main.c
	lld-link /subsystem:efi_application /entry:EfiMain /out:main.efi main.o
	mv main.efi fs/EFI/BOOT/BOOTX64.EFI


qemu: OVMF.fd fs/EFI/BOOT/BOOTX64.EFI
	qemu-system-x86_64 -bios OVMF.fd -hda fat:rw:fs

clean:
	rm -f main.efi
