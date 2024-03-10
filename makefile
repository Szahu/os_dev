C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c std/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h std/*.h)

OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o}

C_FLAGS = -Wall

all: os_image

run: all
	qemu-system-i386 -fda os_image.bin

os_image: boot/boot_sector.bin kernel.bin
	cat $^ > os_image.bin

debug: os_image kernel.elf
	qemu-system-i386 -s -fda os_image &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

kernel.bin: kernel/kernel_entry.o ${OBJ}
	i686-elf-ld -o kernel.bin -Ttext 0x1000 $^ --oformat binary

kernel.elf: kernel/kernel_entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ 

kernel/kernel_entry.o : kernel/kernel_entry.asm
	nasm $< -f elf -o $@

%.o : %.c ${HEADERS}
	i686-elf-gcc ${C_FLAGS} -ffreestanding -I drivers -I cpu -I std -c $< -o $@

%.bin : %.asm
	nasm $< -f bin -I './boot' -o $@

%.o: %.asm
	nasm $< -f elf -o $@

clean: 
	rm -fr *.bin *.o *.dis *.map *.elf os_image.bin
	rm -fr kernel/*.o drivers/*.o boot/*.bin cpu/*.o std/*.o
