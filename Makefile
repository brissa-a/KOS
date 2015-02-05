CC=clang
CFLAGS =	-Wall \
		-target i386-none-eabi \
		-nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		-mno-mmx -mno-3dnow \

OBJECTS =	bootstrap.o \
		main.o \
		segmentation.o \
		utils.o \
		screen.o \
		interrupt/init.o \
		interrupt/timer.o \
		interrupt/divide.o

KERNEL_OBJ   = k.elf
PWD := $(shell pwd)

all: $(KERNEL_OBJ)

run: $(KERNEL_OBJ)
	qemu-system-i386 -monitor stdio -kernel k.elf

run-debug: $(KERNEL_OBJ)
	qemu-system-i386 -s -S -monitor stdio -kernel k.elf

$(KERNEL_OBJ): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ -T k.lds

%.o: %.c
	$(CC) -I$(PWD) -c $< $(CFLAGS) -o $@

%.o: %.S
	$(CC) -I$(PWD) -c $< $(CFLAGS) -o $@

clean:
	$(RM) *.img *.o mtoolsrc *~ menu.txt *.img *.elf *.bin *.map

re: clean all
