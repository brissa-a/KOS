CC=clang
CFLAGS =	-Wall \
		-target i386-none-eabi \
		-nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		-mno-mmx -mno-3dnow

LDFLAGS = --warn-common
OBJECTS = bootstrap.o \
	  #main.o

KERNEL_OBJ   = k.elf
PWD := $(shell pwd)

all: $(KERNEL_OBJ)

run: $(KERNEL_OBJ)
	qemu-system-i386 -monitor stdio -kernel k.elf

run-debug: $(KERNEL_OBJ)
	qemu-system-i386 -s -S -monitor stdio -kernel k.elf

$(KERNEL_OBJ): $(OBJECTS)
	$(LD) $(LDFLAGS) -T k.lds -o $@ $^
	-nm -C $@ | cut -d ' ' -f 1,3 > sos.map

%.o: %.c
	$(CC) -I$(PWD) -c $< $(CFLAGS) -o $@

%.o: %.S
	$(CC) -I$(PWD) -c $< $(CFLAGS) -o $@

clean:
	$(RM) *.img *.o mtoolsrc *~ menu.txt *.img *.elf *.bin *.map

re: clean all
