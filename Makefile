CC = clang
LD = lld-link-7

C_FLAGS = -ffreestanding -flto -fno-stack-protector -fshort-wchar -Iinclude/ -MMD -mno-red-zone -std=c17 -target x86_64-pc-win32-coff -Wall -Wextra
LD_FLAGS = -subsystem:efi_application -nodefaultlib -dll -fpic

SOURCES = ${wildcard src/*.c}
OBJECTS = ${SOURCES:.c=.o}

BOOTLOADER = build/hdd/efi/boot/bootx64.efi

${BOOTLOADER}: ${OBJECTS}
	mkdir -p ${dir $@}
	${LD} ${LD_FLAGS} -entry:efi_main $^ -out:$@

%.o: %.c
	${CC} ${C_FLAGS} -c $< -o $@

-include ${OBJECTS:.o=.d}

clean:
	rm -rf ${BOOTLOADER}
	rm -rf ${OBJECTS} ${OBJECTS:.o=.d}

run: ${BOOTLOADER}
	qemu-system-x86_64 -drive if=pflash,format=raw,readonly,file=bin/OVMF.fd -drive format=raw,file=fat:rw:build/hdd -no-reboot -no-shutdown -machine q35 -smp 4 -enable-kvm -cpu host

.PHONY: test clean