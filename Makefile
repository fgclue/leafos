# $@ = target file
# $< = first dependency
# $^ = all dependencies

# detect all .o files based on their .c source
C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h  drivers/*.h cpu/*.h)
OBJ_FILES32 = ${C_SOURCES:.c=.o} cpu/interrupt.o
OBJ_FILES64 = ${C_SOURCES:.c=.o} cpu/interrupt_x64.o

TARGET32 = leafos-32.iso
TARGET64 = leafos-64.iso


$(TARGET32): boot/mbr.bin kernel-x32.bin
	cat $^ > $@

# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
kernel-x32.bin: boot/kernel_entry.o ${OBJ_FILES32}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

$(TARGET64): boot/mbr.bin kernel-x64.bin
	cat $^ > $@

kernel-x64.bin: boot/kernel_entry_x64.o ${OBJ_FILES64}
	ld -o $@ -Ttext 0x1000 $^ --oformat binary

#os-image.bin: boot/mbr.bin kernel.bin
#	cat $^ > $@

#run: os-image.bin
#	qemu-system-i386 -fda $<

run32: $(TARGET32)
	qemu-system-i386 -fda $<

run64: $(TARGET64)
	qemu-system-x86_64 -fda $<

#echo: os-image.bin
#	xxd $<


echo32: $(TARGET32)
	xxd $<

echo64: $(TARGET64)
	xxd $<

# only for debug
#kernel.elf: boot/kernel_entry.o ${OBJ_FILES}
#	ld -m elf_i386 -o $@ -Ttext 0x1000 $^

#debug: os-image.bin kernel.elf
#	qemu-system-i386 -s -S -fda os-image.bin -d guest_errors,int &
#	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	gcc -g -m32 -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.o: %.asm_x64
	nasm $< -f elf64 -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

%.bin: %.asm_x64
	nasm $< -f bin -o $@

%.dis: %.bin
	ndisasm -b 32 $< > $@

%.dis_x64: %.bin
	ndisasm -b 64 $< > $@



#%.bin: %.asm
#	nasm $< -f bin -o $@

#%.dis: %.bin
#	ndisasm -b 32 $< > $@